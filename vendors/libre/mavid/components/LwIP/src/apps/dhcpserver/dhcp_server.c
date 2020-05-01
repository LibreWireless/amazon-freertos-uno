/* Light Weight DHCP Server for SAC */
//***********************************

#include <stdlib.h>
#include <string.h>
#include "lwip/inet.h"
#include "lwip/err.h"
#include "lwip/pbuf.h"
#include "lwip/udp.h"
#include "lwip/mem.h"
#include "lwip/ip_addr.h"
#include "lwip/dhcp_server.h"
#include "lwip/dhcpserver_options.h"

typedef enum
{
  MHD_STA_INTERFACE = 0, /**< STA or Client Interface  */
  MHD_AP_INTERFACE  = 1,  /**< softAP Interface         */
  MHD_P2P_INTERFACE = 2, /**< P2P Interface         */
} mhd_interface_t;

#define ESP_DHCP 1

#if DHCPS_DEBUG
#define DHCPS_LOG   vLoggingPrintf   
#else
#define DHCPS_LOG
#endif

#define printf 		DHCPS_LOG

#if ESP_DHCP

#define BOOTP_BROADCAST 0x8000

#define DHCP_REQUEST        1
#define DHCP_REPLY          2
#define DHCP_HTYPE_ETHERNET 1
#define DHCP_HLEN_ETHERNET  6
#define DHCP_MSG_LEN      236

#define DHCPS_SERVER_PORT  67
#define DHCPS_CLIENT_PORT  68

#define DHCPDISCOVER  1
#define DHCPOFFER     2
#define DHCPREQUEST   3
#define DHCPDECLINE   4
#define DHCPACK       5
#define DHCPNAK       6
#define DHCPRELEASE   7

#define DHCP_OPTION_SUBNET_MASK   1
#define DHCP_OPTION_ROUTER        3
#define DHCP_OPTION_DNS_SERVER    6
#define DHCP_OPTION_REQ_IPADDR   50
#define DHCP_OPTION_LEASE_TIME   51
#define DHCP_OPTION_MSG_TYPE     53
#define DHCP_OPTION_SERVER_ID    54
#define DHCP_OPTION_INTERFACE_MTU 26
#define DHCP_OPTION_PERFORM_ROUTER_DISCOVERY 31
#define DHCP_OPTION_BROADCAST_ADDRESS 28
#define DHCP_OPTION_REQ_LIST     55
#define DHCP_OPTION_END         255

//#define USE_CLASS_B_NET 1
#define DHCPS_DEBUG          0




#define MAX_STATION_NUM 10
#define DHCPS_STATE_OFFER 1
#define DHCPS_STATE_DECLINE 2
#define DHCPS_STATE_ACK 3
#define DHCPS_STATE_NAK 4
#define DHCPS_STATE_IDLE 5
#define DHCPS_STATE_RELEASE 6

#define MAKE_IPV4_ADDRESS(a, b, c, d)  ((((uint32_t) a) << 24) | (((uint32_t) b) << 16) | (((uint32_t) c) << 8) | ((uint32_t) d))

typedef struct _list_node {
  void *pnode;
  struct _list_node *pnext;
} list_node;


typedef struct {
  ip_addr_t ip_addr;
  ip_addr_t netmask;
  ip_addr_t gw;
} tcpip_adapter_ip_info_t;


static const u32_t magic_cookie  = 0x63538263;
static list_node *plistHead = NULL;
static bool renew = false;

static dhcps_lease_t dhcps_poll;
static dhcps_time_t dhcps_lease_time = DHCPS_LEASE_TIME_DEF;  //minute
static dhcps_offer_t dhcps_offer = 0xFF;
static dhcps_offer_t dhcps_dns = 0x00;

struct dhcp_data 
{
  struct netif *netif;
  struct udp_pcb *pcb_dhcps;
  ip4_addr_t  broadcast_dhcps;
  ip4_addr_t server_address;
  ip4_addr_t dns_server;
  ip4_addr_t client_address;        //added
  ip4_addr_t client_address_plus;  
};

struct dhcp_data *pdhcpinst;



/******************************************************************************
* FunctionName : dhcps_option_info
* Description  : get the DHCP message option info
* Parameters   : op_id -- DHCP message option id
*                opt_len -- DHCP message option length
* Returns      : DHCP message option addr
*******************************************************************************/
void *dhcps_option_info(u8_t op_id, u32_t opt_len)
{
  void *option_arg = NULL;
  
  switch (op_id) {
  case IP_ADDRESS_LEASE_TIME:
    if (opt_len == sizeof(dhcps_time_t)) {
      option_arg = &dhcps_lease_time;
    }
    
    break;
    
  case REQUESTED_IP_ADDRESS:
    if (opt_len == sizeof(dhcps_lease_t)) {
      option_arg = &dhcps_poll;
    }
    
    break;
    
  case ROUTER_SOLICITATION_ADDRESS:
    if (opt_len == sizeof(dhcps_offer_t)) {
      option_arg = &dhcps_offer;
    }
    
    break;
    
  case DOMAIN_NAME_SERVER:
    if (opt_len == sizeof(dhcps_offer_t)) {
      option_arg = &dhcps_dns;
    }
    
    break;
    
  default:
    break;
  }
  
  return option_arg;
}

/******************************************************************************
* FunctionName : dhcps_set_option_info
* Description  : set the DHCP message option info
* Parameters   : op_id -- DHCP message option id
*                opt_info -- DHCP message option info
*                opt_len -- DHCP message option length
* Returns      : none
*******************************************************************************/
void dhcps_set_option_info(u8_t op_id, void *opt_info, u32_t opt_len)
{
  if (opt_info == NULL) {
    return;
  }
  switch (op_id) {
  case IP_ADDRESS_LEASE_TIME:
    if (opt_len == sizeof(dhcps_time_t)) {
      dhcps_lease_time = *(dhcps_time_t *)opt_info;
    }
    
    break;
    
  case REQUESTED_IP_ADDRESS:
    if (opt_len == sizeof(dhcps_lease_t)) {
      dhcps_poll = *(dhcps_lease_t *)opt_info;
    }
    
    break;
    
  case ROUTER_SOLICITATION_ADDRESS:
    if (opt_len == sizeof(dhcps_offer_t)) {
      dhcps_offer = *(dhcps_offer_t *)opt_info;
    }
    
    break;
    
  case DOMAIN_NAME_SERVER:
    if (opt_len == sizeof(dhcps_offer_t)) {
      dhcps_dns = *(dhcps_offer_t *)opt_info;
    }
    break;
    
  default:
    break;
  }
  return;
}

/******************************************************************************
* FunctionName : node_insert_to_list
* Description  : insert the node to the list
* Parameters   : phead -- the head node of the list
*                pinsert -- the insert node of the list
* Returns      : none
*******************************************************************************/
static void node_insert_to_list(list_node **phead, list_node *pinsert)
{
  list_node *plist = NULL;
  struct dhcps_pool *pdhcps_pool = NULL;
  struct dhcps_pool *pdhcps_node = NULL;
  
  if (*phead == NULL) {
    *phead = pinsert;
  } else {
    plist = *phead;
    pdhcps_node = pinsert->pnode;
    pdhcps_pool = plist->pnode;
    
    if (pdhcps_node->ip.addr < pdhcps_pool->ip.addr) {
      pinsert->pnext = plist;
      *phead = pinsert;
    } else {
      while (plist->pnext != NULL) {
        pdhcps_pool = plist->pnext->pnode;
        
        if (pdhcps_node->ip.addr < pdhcps_pool->ip.addr) {
          pinsert->pnext = plist->pnext;
          plist->pnext = pinsert;
          break;
        }
        
        plist = plist->pnext;
      }
      
      if (plist->pnext == NULL) {
        plist->pnext = pinsert;
      }
    }
  }
  
  //	pinsert->pnext = NULL;
}

/******************************************************************************
* FunctionName : node_delete_from_list
* Description  : remove the node from list
* Parameters   : phead -- the head node of the list
*                pdelete -- the remove node of the list
* Returns      : none
*******************************************************************************/
void node_remove_from_list(list_node **phead, list_node *pdelete)
{
  list_node *plist = NULL;
  
  plist = *phead;
  
  if (plist == NULL) {
    *phead = NULL;
  } else {
    if (plist == pdelete) {
      *phead = plist->pnext;
      pdelete->pnext = NULL;
    } else {
      while (plist != NULL) {
        if (plist->pnext == pdelete) {
          plist->pnext = pdelete->pnext;
          pdelete->pnext = NULL;
        }
        
        plist = plist->pnext;
      }
    }
  }
}

/******************************************************************************
* FunctionName : add_msg_type
* Description  : add TYPE option of DHCP message
* Parameters   : optptr -- the addr of DHCP message option
* Returns      : the addr of DHCP message option
*******************************************************************************/
static u8_t *add_msg_type(u8_t *optptr, u8_t type)
{
  *optptr++ = DHCP_OPTION_MSG_TYPE;
  *optptr++ = 1;
  *optptr++ = type;
  return optptr;
}

/******************************************************************************
* FunctionName : add_offer_options
* Description  : add OFFER option of DHCP message
* Parameters   : optptr -- the addr of DHCP message option
* Returns      : the addr of DHCP message option
*******************************************************************************/
static u8_t *add_offer_options(u8_t *optptr)
{
  ip4_addr_t ipadd;
  
  ipadd.addr = *((u32_t *) &pdhcpinst->server_address );
  
#ifdef USE_CLASS_B_NET
  *optptr++ = DHCP_OPTION_SUBNET_MASK;
  *optptr++ = 4;  //length
  *optptr++ = 255;
  *optptr++ = 240;
  *optptr++ = 0;
  *optptr++ = 0;
#else
  *optptr++ = DHCP_OPTION_SUBNET_MASK;
  *optptr++ = 4;
  *optptr++ = 255;
  *optptr++ = 255;
  *optptr++ = 255;
  *optptr++ = 0;
#endif
  
  *optptr++ = DHCP_OPTION_LEASE_TIME;
  *optptr++ = 4;
  *optptr++ = ((dhcps_lease_time * DHCPS_LEASE_UNIT) >> 24) & 0xFF;
  *optptr++ = ((dhcps_lease_time * DHCPS_LEASE_UNIT) >> 16) & 0xFF;
  *optptr++ = ((dhcps_lease_time * DHCPS_LEASE_UNIT) >> 8) & 0xFF;
  *optptr++ = ((dhcps_lease_time * DHCPS_LEASE_UNIT) >> 0) & 0xFF;
  
  *optptr++ = DHCP_OPTION_SERVER_ID;
  *optptr++ = 4;
  *optptr++ = ip4_addr1(&ipadd);
  *optptr++ = ip4_addr2(&ipadd);
  *optptr++ = ip4_addr3(&ipadd);
  *optptr++ = ip4_addr4(&ipadd);
  
  if (dhcps_router_enabled(dhcps_offer)) {
    tcpip_adapter_ip_info_t if_ip;
    //bzero(&if_ip, sizeof(struct ip_info));
    memset(&if_ip , 0x00, sizeof(tcpip_adapter_ip_info_t));
    
    // tcpip_adapter_get_ip_info(MHD_AP_INTERFACE, &if_ip);
    
    if (!ip4_addr_isany_val(if_ip.gw)) {
      *optptr++ = DHCP_OPTION_ROUTER;
      *optptr++ = 4;
      *optptr++ = ip4_addr1(&if_ip.gw);
      *optptr++ = ip4_addr2(&if_ip.gw);
      *optptr++ = ip4_addr3(&if_ip.gw);
      *optptr++ = ip4_addr4(&if_ip.gw);
    }
  }
  
  *optptr++ = DHCP_OPTION_DNS_SERVER;
  *optptr++ = 4;
  if (dhcps_dns_enabled(dhcps_dns)) {
    *optptr++ = ip4_addr1(&pdhcpinst->dns_server);
    *optptr++ = ip4_addr2(&pdhcpinst->dns_server);
    *optptr++ = ip4_addr3(&pdhcpinst->dns_server);
    *optptr++ = ip4_addr4(&pdhcpinst->dns_server);
  }else {
    *optptr++ = ip4_addr1(&ipadd);
    *optptr++ = ip4_addr2(&ipadd);
    *optptr++ = ip4_addr3(&ipadd);
    *optptr++ = ip4_addr4(&ipadd);
  }
  
#ifdef CLASS_B_NET
  *optptr++ = DHCP_OPTION_BROADCAST_ADDRESS;
  *optptr++ = 4;
  *optptr++ = ip4_addr1(&ipadd);
  *optptr++ = 255;
  *optptr++ = 255;
  *optptr++ = 255;
#else
  *optptr++ = DHCP_OPTION_BROADCAST_ADDRESS;
  *optptr++ = 4;
  *optptr++ = ip4_addr1(&ipadd);
  *optptr++ = ip4_addr2(&ipadd);
  *optptr++ = ip4_addr3(&ipadd);
  *optptr++ = 255;
#endif
  
  *optptr++ = DHCP_OPTION_INTERFACE_MTU;
  *optptr++ = 2;
#ifdef CLASS_B_NET
  *optptr++ = 0x05;
  *optptr++ = 0xdc;
#else
  *optptr++ = 0x02;
  *optptr++ = 0x40;
#endif
  
  *optptr++ = DHCP_OPTION_PERFORM_ROUTER_DISCOVERY;
  *optptr++ = 1;
  *optptr++ = 0x00;
  
  *optptr++ = 43;
  *optptr++ = 6;
  
  *optptr++ = 0x01;
  *optptr++ = 4;
  *optptr++ = 0x00;
  *optptr++ = 0x00;
  *optptr++ = 0x00;
  *optptr++ = 0x02;
  
  return optptr;
}

/******************************************************************************
* FunctionName : add_end
* Description  : add end option of DHCP message
* Parameters   : optptr -- the addr of DHCP message option
* Returns      : the addr of DHCP message option
*******************************************************************************/
static u8_t *add_end(u8_t *optptr)
{
  *optptr++ = DHCP_OPTION_END;
  return optptr;
}

/******************************************************************************
* FunctionName : create_msg
* Description  : create response message
* Parameters   : m -- DHCP message info
* Returns      : none
*******************************************************************************/
static void create_msg(struct dhcps_msg *m)
{
  ip4_addr_t client;
  
  
  client.addr = *((uint32_t *) &pdhcpinst->client_address);
  
  m->op = DHCP_REPLY;
  
  m->htype = DHCP_HTYPE_ETHERNET;
  
  m->hlen = 6;
  
  m->hops = 0;
  //        os_memcpy((char *) xid, (char *) m->xid, sizeof(m->xid));
  m->secs = 0;
  m->flags = htons(BOOTP_BROADCAST);
  
  memcpy((char *) m->yiaddr, (char *) &client.addr, sizeof(m->yiaddr));
  
  memset((char *) m->ciaddr, 0, sizeof(m->ciaddr));
  
  memset((char *) m->siaddr, 0, sizeof(m->siaddr));
  
  memset((char *) m->giaddr, 0, sizeof(m->giaddr));
  
  memset((char *) m->sname, 0, sizeof(m->sname));
  
  memset((char *) m->file, 0, sizeof(m->file));
  
  memset((char *) m->options, 0, sizeof(m->options));
  
  u32_t magic_cookie_temp = magic_cookie;
  
  memcpy((char *) m->options, &magic_cookie_temp, sizeof(magic_cookie_temp));
}

struct pbuf * dhcps_pbuf_alloc(u16_t len)
{
  u16_t mlen = sizeof(struct dhcps_msg);
  
  if (len > mlen) {
    DHCPS_LOG("dhcps: len=%d mlen=%d", len, mlen);
    mlen = len;
  }
  
  return pbuf_alloc(PBUF_TRANSPORT, mlen, PBUF_RAM);
}

/******************************************************************************
* FunctionName : send_offer
* Description  : DHCP message OFFER Response
* Parameters   : m -- DHCP message info
* Returns      : none
*******************************************************************************/
static void send_offer(struct dhcps_msg *m, u16_t len)
{
  u8_t *end;
  struct pbuf *p, *q;
  u8_t *data;
  u16_t cnt = 0;
  u16_t i;
  err_t SendOffer_err_t;
  create_msg(m);
  
  end = add_msg_type(&m->options[4], DHCPOFFER);
  end = add_offer_options(end);
  end = add_end(end);
  
  p = dhcps_pbuf_alloc(len); 

  
  if (p != NULL) {
    

    DHCPS_LOG("dhcps: send_offer>>pbuf_alloc succeed\n");
    DHCPS_LOG("dhcps: send_offer>>p->tot_len = %d\n", p->tot_len);
    DHCPS_LOG("dhcps: send_offer>>p->len = %d\n", p->len);

    q = p;
    
    while (q != NULL) {
      data = (u8_t *)q->payload;
      
      for (i = 0; i < q->len; i++) {
        data[i] = ((u8_t *) m)[cnt++];
        DHCPS_LOG("%02x ", data[i]);        
        if ((i + 1) % 16 == 0) {
          DHCPS_LOG("\n");
        }
        

      }
      
      q = q->next;
    }
  } else {
  
    DHCPS_LOG("dhcps: send_offer>>pbuf_alloc failed\n");
    return;
  }
  
  ip_addr_t ip_temp = IPADDR4_INIT(0x0);
  ip4_addr_set(ip_2_ip4(&ip_temp), &pdhcpinst->broadcast_dhcps);
  
  SendOffer_err_t = udp_sendto_if(pdhcpinst->pcb_dhcps, p, &ip_temp, DHCPS_CLIENT_PORT, pdhcpinst->netif);

  printf("Offer done\n");

  DHCPS_LOG("dhcps: send_offer>>udp_sendto result %d\n", SendOffer_err_t);

  
  if (p->ref != 0) {
    DHCPS_LOG("udhcp: send_offer>>free pbuf\n");
    pbuf_free(p);
  }
}

/******************************************************************************
* FunctionName : send_nak
* Description  : DHCP message NACK Response
* Parameters   : m -- DHCP message info
* Returns      : none
*******************************************************************************/
static void send_nak(struct dhcps_msg *m, u16_t len)
{
  u8_t *end;
  struct pbuf *p, *q;
  u8_t *data;
  u16_t cnt = 0;
  u16_t i;
  err_t SendNak_err_t;
  create_msg(m);
  
  end = add_msg_type(&m->options[4], DHCPNAK);
  end = add_end(end);
  
  p = dhcps_pbuf_alloc(len);

  DHCPS_LOG("udhcp: send_nak>>p->ref = %d\n", p->ref);

  
  if (p != NULL) {

    DHCPS_LOG("dhcps: send_nak>>pbuf_alloc succeed\n");
    DHCPS_LOG("dhcps: send_nak>>p->tot_len = %d\n", p->tot_len);
    DHCPS_LOG("dhcps: send_nak>>p->len = %d\n", p->len);
    q = p;
    
    while (q != NULL) {
      data = (u8_t *)q->payload;
      
      for (i = 0; i < q->len; i++) {
        data[i] = ((u8_t *) m)[cnt++];

        DHCPS_LOG("%02x ", data[i]);
        
        if ((i + 1) % 16 == 0) {
          DHCPS_LOG("\n");
        }
        

      }
      
      q = q->next;
    }
  } else {    

    DHCPS_LOG("dhcps: send_nak>>pbuf_alloc failed\n");
    return;
  }
  
  ip_addr_t ip_temp = IPADDR4_INIT(0x0);
  ip4_addr_set(ip_2_ip4(&ip_temp), &pdhcpinst->broadcast_dhcps);
  SendNak_err_t = udp_sendto_if(pdhcpinst->pcb_dhcps, p, &ip_temp, DHCPS_CLIENT_PORT, pdhcpinst->netif);
  DHCPS_LOG("dhcps: send_nak>>udp_sendto result %d\n", SendNak_err_t);

  
  if (p->ref != 0) {
    DHCPS_LOG("udhcp: send_nak>>free pbuf\n");
    pbuf_free(p);
  }
}

/******************************************************************************
* FunctionName : send_ack
* Description  : DHCP message ACK Response
* Parameters   : m -- DHCP message info
* Returns      : none
*******************************************************************************/
static void send_ack(struct dhcps_msg *m, u16_t len)
{
  u8_t *end;
  struct pbuf *p, *q;
  u8_t *data;
  u16_t cnt = 0;
  u16_t i;
  err_t SendAck_err_t;
  create_msg(m);
  
  end = add_msg_type(&m->options[4], DHCPACK);
  end = add_offer_options(end);
  end = add_end(end);
  
  p = dhcps_pbuf_alloc(len);

  DHCPS_LOG("udhcp: send_ack>>p->ref = %d\n", p->ref);

  
  if (p != NULL) {
    

    DHCPS_LOG("dhcps: send_ack>>pbuf_alloc succeed\n");
    DHCPS_LOG("dhcps: send_ack>>p->tot_len = %d\n", p->tot_len);
    DHCPS_LOG("dhcps: send_ack>>p->len = %d\n", p->len);

    q = p;
    
    while (q != NULL) {
      data = (u8_t *)q->payload;
      
      for (i = 0; i < q->len; i++) {
        data[i] = ((u8_t *) m)[cnt++];

        DHCPS_LOG("%02x ", data[i]);
        
        if ((i + 1) % 16 == 0) {
          DHCPS_LOG("\n");
        }
        

      }
      
      q = q->next;
    }
  } else {    

    DHCPS_LOG("dhcps: send_ack>>pbuf_alloc failed\n");

    return;
  }
  
  ip_addr_t ip_temp = IPADDR4_INIT(0x0);
  ip4_addr_set(ip_2_ip4(&ip_temp), &pdhcpinst->broadcast_dhcps);
  SendAck_err_t = udp_sendto_if(pdhcpinst->pcb_dhcps, p, &ip_temp, DHCPS_CLIENT_PORT, pdhcpinst->netif);
  DHCPS_LOG("dhcps: send_ack>>udp_sendto result %x\n", SendAck_err_t);  
  if (p->ref != 0) {
    DHCPS_LOG("udhcp: send_ack>>free pbuf\n");
    pbuf_free(p);
  }
}

/******************************************************************************
* FunctionName : parse_options
* Description  : parse DHCP message options
* Parameters   : optptr -- DHCP message option info
*                len -- DHCP message option length
* Returns      : none
*******************************************************************************/
static u8_t parse_options(u8_t *optptr, s16_t len)
{
  ip4_addr_t client;
  bool is_dhcp_parse_end = false;
  struct dhcps_state s;
  
  client.addr = *((uint32_t *) &pdhcpinst->client_address);
  
  u8_t *end = optptr + len;
  u16_t type = 0;
  
  s.state = DHCPS_STATE_IDLE;
  
  while (optptr < end) {
    DHCPS_LOG("dhcps: (s16_t)*optptr = %d\n", (s16_t)*optptr);    
    switch ((s16_t) *optptr) {
      
    case DHCP_OPTION_MSG_TYPE:	//53
      type = *(optptr + 2);
      break;
      
    case DHCP_OPTION_REQ_IPADDR://50
      if (memcmp((char *) &client.addr, (char *) optptr + 2, 4) == 0) {
        DHCPS_LOG("dhcps: DHCP_OPTION_REQ_IPADDR = 0 ok\n");
        s.state = DHCPS_STATE_ACK;
      } else {
        DHCPS_LOG("dhcps: DHCP_OPTION_REQ_IPADDR != 0 err\n");
        s.state = DHCPS_STATE_NAK;
      }
      
      break;
      
    case DHCP_OPTION_END: {
      is_dhcp_parse_end = true;
    }
    break;
    }
    
    if (is_dhcp_parse_end) {
      break;
    }
    
    optptr += optptr[1] + 2;
  }
  
  switch (type) {
    
  case DHCPDISCOVER://1
    s.state = DHCPS_STATE_OFFER;
    DHCPS_LOG("dhcps: DHCPD_STATE_OFFER\n");
    break;
    
  case DHCPREQUEST://3
    if (!(s.state == DHCPS_STATE_ACK || s.state == DHCPS_STATE_NAK)) {
      if (renew == true) {
        s.state = DHCPS_STATE_ACK;
      } else {
        s.state = DHCPS_STATE_NAK;
      }
      DHCPS_LOG("dhcps: DHCPD_STATE_NAK\n");

    }
    
    break;
    
  case DHCPDECLINE://4
    s.state = DHCPS_STATE_IDLE;
    DHCPS_LOG("dhcps: DHCPD_STATE_IDLE\n");
    break;
    
  case DHCPRELEASE://7
    s.state = DHCPS_STATE_RELEASE;
    DHCPS_LOG("dhcps: DHCPD_STATE_IDLE\n");

    break;
  }
  
  DHCPS_LOG("dhcps: return s.state = %d\n", s.state);
  return s.state;
}

/******************************************************************************
* FunctionName : parse_msg
* Description  : parse DHCP message from netif
* Parameters   : m -- DHCP message info
*                len -- DHCP message length
* Returns      : DHCP message type
*******************************************************************************/
static s16_t parse_msg(struct dhcps_msg *m, u16_t len)
{
  u32_t lease_timer = (dhcps_lease_time * DHCPS_LEASE_UNIT)/DHCPS_COARSE_TIMER_SECS;
  
  if (memcmp((char *)m->options, &magic_cookie, sizeof(magic_cookie)) == 0) {
    DHCPS_LOG("dhcps: len = %d\n", len);
    ip4_addr_t addr_tmp;
    
    struct dhcps_pool *pdhcps_pool = NULL;
    list_node *pnode = NULL;
    list_node *pback_node = NULL;
    ip4_addr_t first_address;
    bool flag = false;
    
    first_address.addr = dhcps_poll.start_ip.addr;
    pdhcpinst->client_address.addr = pdhcpinst->client_address_plus.addr;
    renew = false;
    
    if (plistHead != NULL) {
      for (pback_node = plistHead; pback_node != NULL; pback_node = pback_node->pnext) {
        pdhcps_pool = pback_node->pnode;
        
        if (memcmp(pdhcps_pool->mac, m->chaddr, sizeof(pdhcps_pool->mac)) == 0) {
          if (memcmp(&pdhcps_pool->ip.addr, m->ciaddr, sizeof(pdhcps_pool->ip.addr)) == 0) {
            renew = true;
          }
          
          pdhcpinst->client_address.addr = pdhcps_pool->ip.addr;
          pdhcps_pool->lease_timer = lease_timer;
          pnode = pback_node;
          goto POOL_CHECK;
        } else if (pdhcps_pool->ip.addr == pdhcpinst->client_address_plus.addr) {
          addr_tmp.addr = htonl(pdhcpinst->client_address_plus.addr);
          addr_tmp.addr++;
          pdhcpinst->client_address_plus.addr = htonl(addr_tmp.addr);
          pdhcpinst->client_address.addr = pdhcpinst->client_address_plus.addr;
        }
        
        if (flag == false) { // search the fisrt unused ip
          if (first_address.addr < pdhcps_pool->ip.addr) {
            flag = true;
          } else {
            addr_tmp.addr = htonl(first_address.addr);
            addr_tmp.addr++;
            first_address.addr = htonl(addr_tmp.addr);
          }
        }
      }
    } else {
      pdhcpinst->client_address.addr = dhcps_poll.start_ip.addr;
    }
    
    if (pdhcpinst->client_address_plus.addr > dhcps_poll.end_ip.addr) {
      pdhcpinst->client_address.addr = first_address.addr;
    }
    
    if (pdhcpinst->client_address.addr > dhcps_poll.end_ip.addr) {
      pdhcpinst->client_address_plus.addr = dhcps_poll.start_ip.addr;
      pdhcps_pool = NULL;
      pnode = NULL;
    } else {
      pdhcps_pool = (struct dhcps_pool *)mem_malloc(sizeof(struct dhcps_pool));
      memset(pdhcps_pool , 0x00 , sizeof(struct dhcps_pool));
      
      pdhcps_pool->ip.addr = pdhcpinst->client_address.addr;
      memcpy(pdhcps_pool->mac, m->chaddr, sizeof(pdhcps_pool->mac));
      pdhcps_pool->lease_timer = lease_timer;
      pnode = (list_node *)mem_malloc(sizeof(list_node));
      memset(pnode , 0x00 , sizeof(list_node));
      
      pnode->pnode = pdhcps_pool;
      pnode->pnext = NULL;
      node_insert_to_list(&plistHead, pnode);
      
      if (pdhcpinst->client_address.addr == dhcps_poll.end_ip.addr) {
        pdhcpinst->client_address_plus.addr = dhcps_poll.start_ip.addr;
      } else {
        addr_tmp.addr = htonl(pdhcpinst->client_address.addr);
        addr_tmp.addr++;
        pdhcpinst->client_address_plus.addr = htonl(addr_tmp.addr);
      }
    }
    
  POOL_CHECK:
    
    if ((pdhcpinst->client_address.addr > dhcps_poll.end_ip.addr) || (ip4_addr_isany(&pdhcpinst->client_address))) {
      if (pnode != NULL) {
        node_remove_from_list(&plistHead, pnode);
        mem_free(pnode);
        pnode = NULL;
      }
      
      if (pdhcps_pool != NULL) {
        mem_free(pdhcps_pool);
        pdhcps_pool = NULL;
      }
      
      return 4;
    }
    
    s16_t ret = parse_options(&m->options[4], len);;
    
    if (ret == DHCPS_STATE_RELEASE) {
      if (pnode != NULL) {
        node_remove_from_list(&plistHead, pnode);
        mem_free(pnode);
        pnode = NULL;
      }
      
      if (pdhcps_pool != NULL) {
        free(pdhcps_pool);
        pdhcps_pool = NULL;
      }
      
      memset(&pdhcpinst->client_address, 0x0, sizeof(pdhcpinst->client_address));
    }
    
    DHCPS_LOG("dhcps: xid changed\n");
    DHCPS_LOG("dhcps: pdhcpinst->client_address.addr = %x\n", pdhcpinst->client_address.addr);
    return ret;
  }
  
  return 0;
}

/******************************************************************************
* FunctionName : handle_dhcp
* Description  : If an incoming DHCP message is in response to us, then trigger the state machine
* Parameters   : arg -- arg user supplied argument (udp_pcb.recv_arg)
* 				  pcb -- the udp_pcb which received data
* 			      p -- the packet buffer that was received
* 				  addr -- the remote IP address from which the packet was received
* 				  port -- the remote port from which the packet was received
* Returns      : none
*******************************************************************************/
static void handle_dhcp(void *arg,
                        struct udp_pcb *pcb,
                        struct pbuf *p,
                        const ip_addr_t *addr,
                        u16_t port)
{
  struct dhcps_msg *pmsg_dhcps = NULL;
  s16_t tlen, malloc_len;
  u16_t i;
  u16_t dhcps_msg_cnt = 0;
  u8_t *p_dhcps_msg = NULL;
  u8_t *data;
  
  DHCPS_LOG("dhcps: handle_dhcp-> receive a packet\n");
  
  if (p == NULL) {
    return;
  }
  
  malloc_len = sizeof(struct dhcps_msg);
  DHCPS_LOG("dhcps: handle_dhcp malloc_len=%d rx_len=%d", malloc_len, p->tot_len);

  if (malloc_len < p->tot_len) {
    malloc_len = p->tot_len;
  }
  
  pmsg_dhcps = (struct dhcps_msg *)mem_malloc(malloc_len);
  if (NULL == pmsg_dhcps) {
    pbuf_free(p);
    return;
  }
  
  memset(pmsg_dhcps , 0x00 , malloc_len);
  p_dhcps_msg = (u8_t *)pmsg_dhcps;
  tlen = p->tot_len;
  data = p->payload;
  
  DHCPS_LOG("dhcps: handle_dhcp-> p->tot_len = %d\n", tlen);
  DHCPS_LOG("dhcps: handle_dhcp-> p->len = %d\n", p->len);
  
  for (i = 0; i < p->len; i++) {
    p_dhcps_msg[dhcps_msg_cnt++] = data[i];
    DHCPS_LOG("%02x ", data[i]);
    
    if ((i + 1) % 16 == 0) {
      DHCPS_LOG("\n");
    }
    
  }
  
  if (p->next != NULL) {
    DHCPS_LOG("dhcps: handle_dhcp-> p->next != NULL\n");
    DHCPS_LOG("dhcps: handle_dhcp-> p->next->tot_len = %d\n", p->next->tot_len);
    DHCPS_LOG("dhcps: handle_dhcp-> p->next->len = %d\n", p->next->len);
    
    data = p->next->payload;
    
    for (i = 0; i < p->next->len; i++) {
      p_dhcps_msg[dhcps_msg_cnt++] = data[i];
      DHCPS_LOG("%02x ", data[i]);
      
      if ((i + 1) % 16 == 0) {
        DHCPS_LOG("\n");
      }
      
    }
  }
  
  DHCPS_LOG("dhcps: handle_dhcp-> parse_msg(p)\n");
  
  switch (parse_msg(pmsg_dhcps, tlen - 240)) {
  case DHCPS_STATE_OFFER://1
    DHCPS_LOG("dhcps: handle_dhcp-> DHCPD_STATE_OFFER\n");
    send_offer(pmsg_dhcps, malloc_len);
    break;
    
  case DHCPS_STATE_ACK://3
    DHCPS_LOG("dhcps: handle_dhcp-> DHCPD_STATE_ACK\n");
    send_ack(pmsg_dhcps, malloc_len);
    break;
    
  case DHCPS_STATE_NAK://4
    DHCPS_LOG("dhcps: handle_dhcp-> DHCPD_STATE_NAK\n");
    send_nak(pmsg_dhcps, malloc_len);
    break;
    
  default :
    break;
  }  
  DHCPS_LOG("dhcps: handle_dhcp-> pbuf_free(p)\n");
  pbuf_free(p);
  mem_free(pmsg_dhcps);
  pmsg_dhcps = NULL;
}

/******************************************************************************
* FunctionName : dhcps_poll_set
* Description  : set ip poll from start to end for station
* Parameters   : ip -- The current ip addr
* Returns      : none
*******************************************************************************/
static void dhcps_poll_set(u32_t ip)
{
  u32_t softap_ip = 0, local_ip = 0;
  u32_t start_ip = 0;
  u32_t end_ip = 0;
  
  if (dhcps_poll.enable == true) {
    softap_ip = htonl(ip);
    start_ip = htonl(dhcps_poll.start_ip.addr);
    end_ip = htonl(dhcps_poll.end_ip.addr);
    
    /*config ip information can't contain local ip*/
    if ((start_ip <= softap_ip) && (softap_ip <= end_ip)) {
      dhcps_poll.enable = false;
    } else {
      /*config ip information must be in the same segment as the local ip*/
      softap_ip >>= 8;
      
      if (((start_ip >> 8 != softap_ip) || (end_ip >> 8 != softap_ip))
          || (end_ip - start_ip > DHCPS_MAX_LEASE)) {
            dhcps_poll.enable = false;
          }
    }
  }
  
  if (dhcps_poll.enable == false) {
    local_ip = softap_ip = htonl(ip);
    softap_ip &= 0xFFFFFF00;
    local_ip &= 0xFF;
    
    if (local_ip >= 0x80) {
      local_ip -= DHCPS_MAX_LEASE;
    } else {
      local_ip ++;
    }
    
    //bzero(&dhcps_poll, sizeof(dhcps_poll));
    memset(&dhcps_poll , 0x00, sizeof(dhcps_poll));
    dhcps_poll.start_ip.addr = softap_ip | local_ip;
    dhcps_poll.end_ip.addr = softap_ip | (local_ip + DHCPS_MAX_LEASE - 1);
    dhcps_poll.start_ip.addr = htonl(dhcps_poll.start_ip.addr);
    dhcps_poll.end_ip.addr = htonl(dhcps_poll.end_ip.addr);
  }
  
}

/******************************************************************************
* FunctionName : dhcps_start
* Description  : start dhcp server function
* Parameters   : netif -- The current netif addr
*              : info  -- The current ip info
* Returns      : none
*******************************************************************************/
void dhcps_start(struct netif *netif, ip4_addr_t ip)
{
  struct netif *apnetif = netif;
  struct udp_pcb *pcb_dhcps;
  
  if (pdhcpinst->pcb_dhcps != NULL) {
    udp_remove(pdhcpinst->pcb_dhcps);
  }
  
  pcb_dhcps = udp_new();
  
  if (pcb_dhcps == NULL || ip4_addr_isany_val(ip)) {
    printf("dhcps_start(): could not obtain pcb\n");
  }
  
  pdhcpinst->pcb_dhcps = pcb_dhcps;
  
  IP4_ADDR(&pdhcpinst->broadcast_dhcps, 255, 255, 255, 255);
  
  pdhcpinst->server_address.addr = ip.addr;
  dhcps_poll_set(pdhcpinst->server_address.addr);
  
  pdhcpinst->client_address_plus.addr = dhcps_poll.start_ip.addr;
  
  udp_bind(pcb_dhcps, &netif->ip_addr, DHCPS_SERVER_PORT);
  udp_recv(pcb_dhcps, handle_dhcp, NULL);
  printf("dhcps:dhcps_start\n");
  
}

/******************************************************************************
* FunctionName : dhcps_stop
* Description  : stop dhcp server function
* Parameters   : netif -- The current netif addr
* Returns      : none
*******************************************************************************/
void dhcps_stop(void) 
{
  if (pdhcpinst->pcb_dhcps != NULL) {
    udp_disconnect(pdhcpinst->pcb_dhcps);
    udp_remove(pdhcpinst->pcb_dhcps);
  }
  
  list_node *pnode = NULL;
  list_node *pback_node = NULL;
  pnode = plistHead;
  
  while (pnode != NULL) {
    pback_node = pnode;
    pnode = pback_node->pnext;
    node_remove_from_list(&plistHead, pback_node);
    mem_free(pback_node->pnode);
    pback_node->pnode = NULL;
    mem_free(pback_node);
    pback_node = NULL;
  }
  free(pdhcpinst);
}

/******************************************************************************
* FunctionName : kill_oldest_dhcps_pool
* Description  : remove the oldest node from list
* Parameters   : none
* Returns      : none
*******************************************************************************/
static void kill_oldest_dhcps_pool(void)
{
  list_node *pre = NULL, *p = NULL;
  list_node *minpre = NULL, *minp = NULL;
  struct dhcps_pool *pdhcps_pool = NULL, *pmin_pool = NULL;
  pre = plistHead;
  p = pre->pnext;
  minpre = pre;
  minp = p;
  
  while (p != NULL) {
    pdhcps_pool = p->pnode;
    pmin_pool = minp->pnode;
    
    if (pdhcps_pool->lease_timer < pmin_pool->lease_timer) {
      minp = p;
      minpre = pre;
    }
    
    pre = p;
    p = p->pnext;
  }
  
  minpre->pnext = minp->pnext;
  free(minp->pnode);
  minp->pnode = NULL;
  free(minp);
  minp = NULL;
}

/******************************************************************************
* FunctionName : dhcps_coarse_tmr
* Description  : the lease time count
* Parameters   : none
* Returns      : none
*******************************************************************************/
void dhcps_coarse_tmr(void)
{
  u8_t num_dhcps_pool = 0;
  list_node *pback_node = NULL;
  list_node *pnode = NULL;
  struct dhcps_pool *pdhcps_pool = NULL;
  pnode = plistHead;
  
  while (pnode != NULL) {
    pdhcps_pool = pnode->pnode;
    pdhcps_pool->lease_timer --;
    
    if (pdhcps_pool->lease_timer == 0) {
      pback_node = pnode;
      pnode = pback_node->pnext;
      node_remove_from_list(&plistHead, pback_node);
      free(pback_node->pnode);
      pback_node->pnode = NULL;
      free(pback_node);
      pback_node = NULL;
    } else {
      pnode = pnode ->pnext;
      num_dhcps_pool ++;
    }
  }
  
  if (num_dhcps_pool >= MAX_STATION_NUM) {
    kill_oldest_dhcps_pool();
  }
}

/******************************************************************************
* FunctionName : dhcp_search_ip_on_mac
* Description  : Search ip address based on mac address
* Parameters   : mac -- The MAC addr
*				  ip  -- The IP info
* Returns      : true or false
*******************************************************************************/
bool dhcp_search_ip_on_mac(u8_t *mac, ip4_addr_t *ip)
{
  struct dhcps_pool *pdhcps_pool = NULL;
  list_node *pback_node = NULL;
  bool ret = false;
  
  for (pback_node = plistHead; pback_node != NULL; pback_node = pback_node->pnext) {
    pdhcps_pool = pback_node->pnode;
    
    if (memcmp(pdhcps_pool->mac, mac, sizeof(pdhcps_pool->mac)) == 0) {
      memcpy(&ip->addr, &pdhcps_pool->ip.addr, sizeof(pdhcps_pool->ip.addr));
      ret = true;
      break;
    }
  }
  
  return ret;
}

/******************************************************************************
* FunctionName : dhcps_dns_setserver
* Description  : set DNS server address for dhcpserver
* Parameters   : dnsserver -- The DNS server address
* Returns      : none
*******************************************************************************/
void
dhcps_dns_setserver(const ip_addr_t *dnsserver)
{
  if (dnsserver != NULL) {
    pdhcpinst->dns_server = *(ip_2_ip4(dnsserver));
  } else {
    pdhcpinst->dns_server = *(ip_2_ip4(IP_ADDR_ANY));
  } 
}

/******************************************************************************
* FunctionName : dhcps_dns_getserver
* Description  : get DNS server address for dhcpserver
* Parameters   : none
* Returns      : ip4_addr_t
*******************************************************************************/
ip4_addr_t 
dhcps_dns_getserver()
{
  return pdhcpinst->dns_server;
}


u8_t dhcp_server_init(struct netif *pnetif)
{
  pdhcpinst = malloc(sizeof(struct dhcp_data));
  if(pdhcpinst)
  {
    ip4_addr_t ipaddr;
    memset(pdhcpinst, 0, sizeof(*pdhcpinst));
    ipaddr.addr  = htonl(MAKE_IPV4_ADDRESS( 192,168,  10,  1 ));
    pdhcpinst->netif = pnetif;
    dhcps_start(pnetif, ipaddr);
  }
}
#endif
