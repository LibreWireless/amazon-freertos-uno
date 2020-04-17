/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_MHD_KEEP_ALVIE_H_
#define INCLUDED_MHD_KEEP_ALVIE_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define IPV4_ADDR_LEN   4
typedef struct ipv4_addr {
        uint8_t   addr[IPV4_ADDR_LEN];
}ipv4_addr_t;

typedef struct tcpka_conn {
	uint32_t sess_id;          /* Tcp session ID */
	struct ether_addr dst_mac; /* Destinition Mac */
	struct ipv4_addr src_ip;     /* Sorce IP */
	struct ipv4_addr dst_ip;     /* Destinition IP */
	uint16_t ipid;             /* Ip Identification */
	uint16_t srcport;          /* Source Port Address */
	uint16_t dstport;          /* Destination Port Address */
	uint32_t seq;              /* TCP Sequence Number */
	uint32_t ack;              /* TCP Ack Number */
	uint16_t tcpwin;           /* TCP window */
	uint32_t tsval;            /* Timestamp Value */
	uint32_t tsecr;            /* Timestamp Echo Reply */
	uint32_t last_payload_len; /* last packet payload len */ 
	uint32_t ka_payload_len;   /* keep alive payload length */
	uint8_t  ka_payload[1];    /* keep alive payload */
} tcpka_conn_t;

typedef struct wl_mtcpkeep_alive_timers_pkt {
	uint16_t interval;		    /* interval timer */
	uint16_t retry_interval;	/* retry_interval timer */
	uint16_t retry_count;		/* retry_count */
} wl_mtcpkeep_alive_timers_pkt_t;

typedef struct tcpka_conn_sess {
	uint32_t sess_id;   /* session id */
	uint32_t flag;      /* enable/disable flag */
	wl_mtcpkeep_alive_timers_pkt_t  tcp_keepalive_timers;
} tcpka_conn_sess_t;

typedef struct tcpka_conn_info {
    uint32_t tcpka_sess_ipid;
    uint32_t tcpka_sess_seq;
    uint32_t tcpka_sess_ack;
} tcpka_conn_sess_info_t;

mhd_result_t mhd_wifi_tcp_keepalive_add( tcpka_conn_t *packet_info );
mhd_result_t mhd_wifi_tcp_keepalive_enable( tcpka_conn_sess_t *session );
mhd_result_t mhd_wifi_tcp_keepalive_delete( uint32_t session_id );
mhd_result_t mhd_wifi_tcp_keepalive_info( tcpka_conn_sess_info_t *session_info );

mhd_result_t mhd_wifi_get_udpka_timeout( uint32_t *time_sec );
mhd_result_t mhd_wifi_set_udpka_timeout( uint32_t time_sec );


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_KEEP_ALVIE_H_ */
