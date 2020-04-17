#include "lwip/opt.h"
#include "lwip/icmp.h"
#include "lwip/inet_chksum.h"
#include "lwip/sockets.h"
#include "lwip/mem.h"
#include "lwip/inet.h"
#include "netif/etharp.h"
#include "lwip/ip.h"
#include "lwip/tcpip.h"
#include "lwip/dhcp.h"
#include "lwip/netdb.h"
#include "lwip/inet.h"
#include <stdbool.h>  
#ifdef VERBOSE_PRINT
#define printf     vLoggingPrintf    
#else
#define printf(...)
#endif // VERBOSE_PRINT
    
   
/******************************************************
*                      Macros
******************************************************/

/******************************************************
*                    Constants
******************************************************/
#define PING_RCV_TIMEO       (1000)    /* ping receive timeout - in milliseconds */
#define PING_ID              (0xAFAF)
#define PING_MAX_PAYLOAD_SIZE ( 10000 ) /* ping max size */

typedef enum
{
  ERR_CMD_OK           =  0,
  ERR_UNKNOWN          = -1,
  ERR_UNKNOWN_CMD      = -2,
  ERR_INSUFFICENT_ARGS = -3,
  ERR_TOO_MANY_ARGS    = -4,
  ERR_ADDRESS          = -5,
  ERR_NO_CMD           = -6,
  ERR_BAD_FORMAT       = -7,
  ERR_LAST_ERROR       = -8
} cmd_err_t;


static void ping_prepare_echo( struct icmp_echo_hdr *iecho, uint16_t len );
static err_t ping_recv( int socket_hnd, int enable_prints );

char *ping_status_get(err_t val)
{
    if(ERR_OK==val)
        return "Success";
    else
        return "Failure";
}

/******************************************************
*               Variable Definitions
******************************************************/
static uint16_t      ping_seq_num;

/*!
******************************************************************************
* Sends an ICMP ping to the indicated host or IP address
*
* @return  0 for success, otherwise error
*/

int ping_remotehost( char *pingthis, int num, bool continuous, int enable_prints)
{
  struct hostent * host;
  struct sockaddr_in host_addr;
  int socket_hnd;
  int recv_timeout = PING_RCV_TIMEO;  
  int len      = 100;
  int interval = 1000;
  err_t result = -1;
  
  host = gethostbyname( pingthis );
  
  if ( host == NULL )
  {
    if(enable_prints)printf("Could not find host %s\n", pingthis );
    return ERR_UNKNOWN;
  }
  
  host_addr.sin_addr.s_addr = *((uint32_t*) host->h_addr_list[0]);
  host_addr.sin_len = sizeof( host_addr );
  host_addr.sin_family = AF_INET;
  
  /* Open a local socket for pinging */
  if ( ( socket_hnd = lwip_socket( AF_INET, SOCK_RAW, IP_PROTO_ICMP ) ) < 0 )
  {
    if(enable_prints)printf("unable to create socket for Ping\r\n");
    return ERR_UNKNOWN;
  }
  
  /* Set the receive timeout on local socket so pings will time out. */
  lwip_setsockopt( socket_hnd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof( recv_timeout ) );
  
  if(enable_prints)printf ("PING %u.%u.%u.%u\r\n", (unsigned char) ( ( htonl( host_addr.sin_addr.s_addr ) >> 24 ) & 0xff ),
          (unsigned char) ( ( htonl( host_addr.sin_addr.s_addr ) >> 16 ) & 0xff ),
          (unsigned char) ( ( htonl( host_addr.sin_addr.s_addr ) >>  8 ) & 0xff ),
          (unsigned char) ( ( htonl( host_addr.sin_addr.s_addr ) >>  0 ) & 0xff ));
  
  struct icmp_echo_hdr *iecho;
  size_t ping_size = sizeof(struct icmp_echo_hdr) + len;
  
  /* Allocate memory for packet */
  if ( !( iecho = mem_malloc( ping_size ) ) )
  {
    lwip_close( socket_hnd );
    return ERR_MEM;
  }  
  /* Construct ping request */
  ping_prepare_echo( iecho, ping_size );  
  uint32_t send_time;
  uint32_t reply_time;  
  while (( num > 0 ) || ( continuous == true ) )
  {
    /* Send ping and wait for reply */
    //send_time = host_rtos_get_time( );
    send_time =  HAL_GetTick();
    if ( lwip_sendto( socket_hnd, iecho, ping_size, 0, (struct sockaddr*) &host_addr, host_addr.sin_len ) > 0 )
    {
      /* Wait for ping reply */
      result = ping_recv( socket_hnd, enable_prints );
      //reply_time = host_rtos_get_time( );
      reply_time = HAL_GetTick();
      if ( ERR_OK == result )      
      {
        if(enable_prints)printf("\nPing Success...");
        break;    
      }
      else      
      {
        if(enable_prints)printf("Ping timeout\r\n");
      }
    }
    else    
    {
     if(enable_prints)printf("Ping error\r\n");
    }
    num--;
    if ( ( num > 0 ) || ( continuous == true ) )    
      HAL_Delay(interval); // This is simple and should probably wait for a residual period    
  }  
  // Free the packet
  mem_free( iecho );  
  lwip_close( socket_hnd ); 
  return result;
}

/**
*  Prepare the contents of an echo ICMP request packet
*
*  @param iecho  : Pointer to an icmp_echo_hdr structure in which the ICMP packet will be constructed
*  @param len    : The length in bytes of the packet buffer passed to the iecho parameter
*
*/

static void ping_prepare_echo( struct icmp_echo_hdr *iecho, uint16_t len )
{
  int i, payload_size;  
  payload_size = len - sizeof(struct icmp_echo_hdr);  
  ICMPH_TYPE_SET( iecho, ICMP_ECHO );
  ICMPH_CODE_SET( iecho, 0 );
  iecho->chksum = 0;
  iecho->id = PING_ID;
  iecho->seqno = htons( ++ping_seq_num );  
  /* fill the additional data buffer with some data */
  for ( i = 0; i < payload_size; i++ )
  {
    ( (char*) iecho )[sizeof(struct icmp_echo_hdr) + i] = i;
  }  
  iecho->chksum = inet_chksum( iecho, len );
}


/**
*  Receive a Ping reply
*
*  Waits for a ICMP echo reply (Ping reply) to be received using the specified socket. Compares the
*  sequence number, and ID number to the last ping sent, and if they match, returns ERR_OK, indicating
*  a valid ping response.
*
*  @param socket_hnd : The handle for the local socket through which the ping reply will be received
*
*  @return  ERR_OK if valid reply received, ERR_TIMEOUT otherwise
*/

static err_t ping_recv( int socket_hnd , int enable_prints)
{
  char buf[64];
  int fromlen, len;
  struct sockaddr_in from;
  struct ip_hdr *iphdr;
  struct icmp_echo_hdr *iecho;
  
#if 1
  int rxd;
  {
    rxd=0;
    rxd=is_sock_data_available_for_read(socket_hnd,1,100,0);
    if(enable_prints==1) printf("\nping_recv: rxd=%d",rxd);
    if(rxd==0)
    {
        if(enable_prints==1) printf("\nselect failed... no data... returning..");
        return ERR_TIMEOUT;
    }
  }
#endif

  while ( ( len = lwip_recvfrom( socket_hnd, buf, sizeof( buf ), 0, (struct sockaddr*) &from, (socklen_t*) &fromlen ) ) > 0 )
  {
    if ( len >= (int) ( sizeof(struct ip_hdr) + sizeof(struct icmp_echo_hdr) ) )
    {
      iphdr = (struct ip_hdr *) buf;
      iecho = (struct icmp_echo_hdr *) ( buf + ( IPH_HL( iphdr ) * 4 ) );
      
      if ( ( iecho->id == PING_ID ) &&
          ( iecho->seqno == htons( ping_seq_num ) ) &&
            ( ICMPH_TYPE( iecho ) == ICMP_ER ) )
      {
        return ERR_OK; /* Echo reply received - return success */
      }
      else
      {
          if(enable_prints==1) printf("\nseq num mismatch.");
          if(enable_prints==1) printf("\ngot id=0x%x, got seq=0x%x, got type=0x%x",iecho->id,iecho->seqno,  ICMPH_TYPE( iecho ));
          if(enable_prints==1) printf("\nexpected id=0x%x, expected seq=0x%x, expected type=0x%x",PING_ID,iecho->seqno, htons( ping_seq_num  ) ,ICMP_ER);
          break;
      }
    }
  }  
  return ERR_TIMEOUT; /* No valid echo reply received before timeout */
}
