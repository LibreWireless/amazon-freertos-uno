/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_MHD_API_TEST_H_
#define INCLUDED_MHD_API_TEST_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                     Macros
 ******************************************************/
    
/******************************************************
 *                    Constants
 ******************************************************/

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

typedef struct tcpka_conn {
	uint32_t sess_id;          /* Tcp session ID */
	struct ether_addr dst_mac; /* Destinition Mac */
//	struct ipv4_addr src_ip;     /* Sorce IP */
//	struct ipv4_addr dst_ip;     /* Destinition IP */
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

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

void cmd_iperf_send( uint32_t argc, uint8_t **argv );
void cmd_test_ping( uint32_t argc, uint8_t **argv );
void cmd_sta_test_start( uint32_t argc, uint8_t **argv );
void cmd_sta_test_stop( uint32_t argc, uint8_t **argv );
void cmd_ap_test_start( uint32_t argc, uint8_t **argv );
void cmd_ap_test_stop( uint32_t argc, uint8_t **argv );

void cmd_scan_test( uint32_t argc, uint8_t **argv );

void cmd_wifi_deepsleep( uint32_t argc, uint8_t **argv );
void cmd_wifi_hostsleep( uint32_t argc, uint8_t **argv );
void cmd_wifi_sta_mpc( uint32_t argc, uint8_t **argv );
void cmd_wifi_sta_pm( uint32_t argc, uint8_t **argv );

void cmd_wifi_get_sta_rssi( uint32_t argc, uint8_t **argv );
void cmd_wifi_get_ap_rssi( uint32_t argc, uint8_t **argv );
void cmd_wifi_get_sta_noise( uint32_t argc, uint8_t **argv );

void cmd_wifi_get_client_list2( uint32_t argc, uint8_t **argv );
void cmd_wifi_get_client_list( uint32_t argc, uint8_t **argv );
void cmd_wifi_get_mac_list( uint32_t argc, uint8_t **argv );

void cmd_wifi_ampdu( uint32_t argc, uint8_t **argv );
void cmd_wifi_ampdu_ex( uint32_t argc, uint8_t **argv );

void cmd_wifi_sdio_bus( uint32_t argc, uint8_t **argv );

void cmd_wifi_get_nmode( uint32_t argc, uint8_t **argv );
void cmd_wifi_set_rate( uint32_t argc, uint8_t **argv );

void cmd_wifi_ap_dhcpd_option( uint32_t argc, uint8_t **argv );
void cmd_wifi_link_reg( uint32_t argc, uint8_t **argv );
void cmd_wifi_link_dereg( uint32_t argc, uint8_t **argv );

void cmd_wifi_wl_cmd(int argc, char *argv[]);
void cmd_wifi_check_fw_log( uint32_t argc, uint8_t **argv );

void cmd_wifi_link_reg( uint32_t argc, uint8_t **argv );
void cmd_wifi_link_dereg( uint32_t argc, uint8_t **argv );

void cmd_wifi_sta_bcn_li_dtim( uint32_t argc, uint8_t **argv );
void cmd_wifi_scansuppress( uint32_t argc, uint8_t **argv );
void cmd_sta_aoe_refresh_ip( uint32_t argc, uint8_t **argv );

void cmd_wifi_iovar_int( uint32_t argc, uint8_t **argv );

void cmd_ap_monitor( uint32_t argc, uint8_t **argv );
void cmd_sta_monitor( uint32_t argc, uint8_t **argv );

void cmd_ap_custom_ie( uint32_t argc, uint8_t **argv );
void cmd_set_tx_queue_length( uint32_t argc, uint8_t **argv );
void cmd_get_data_packet_number( uint32_t argc, uint8_t **argv );
void cmd_sup_wpa( uint32_t argc, uint8_t **argv );
void cmd_passphrase( uint32_t argc, uint8_t **argv );
void cmd_packet_filter( uint32_t argc, uint8_t **argv );

void cmd_queue_test( uint32_t argc, uint8_t **argv );

int cmd_wifi_test( uint32_t argc, uint8_t **argv );
int cmd_wifi_wlcmd( uint32_t argc, uint8_t **argv );
int cmd_wifi_wps( uint32_t argc, uint8_t **argv );
int cmd_wifi_p2p( uint32_t argc, uint8_t **argv );

// Test APIs
///////////////////////////////////////////////////////////////////////
void mhd_ping(char *ip_addr);

void mhd_test_softap_start(void);
void mhd_test_softap_start_0103( void );

void mhd_test_softap_stop(void);

void mhd_test_sta_start(void);
void mhd_test_sta_stop(void);

void mhd_scan_test( int retry_count, uint32_t time_ms );

// set fw host sleep state. 1: enter host sleep, 0: exit host sleep
void mhd_set_host_sleep( int state );
// get fw host sleep state. 0:disabled, 1:enabled, -1:error
int mhd_get_host_sleep( void );

// set fw deep sleep state. 1: enter deep sleep, 0: exit deep sleep
void mhd_set_deep_sleep( int state );
// get fw deep sleep state. 0:disabled, 1:enabled, -1:error
int mhd_get_deep_sleep( void );

// set fw mpc state. 1: enter mpc, 0: exit mpc
void mhd_set_mpc( int state );
// get fw mpc state. 0:disabled, 1:enabled, -1:error
int mhd_get_mpc( void );

// set wifi powersave mode. 0:disable, 1:pm1, 2:pm2. 
// if set to pm2, you should set the time return to sleep. default is 200ms.
int mhd_sta_set_powersave( uint8_t mode, uint8_t time_ms );
// get wifi powersave mode. mode 0:disable, 1:pm1, 2:pm2.
// if mode is pm2, the time parameter is valid, means return to sleep time (ms).
int mhd_sta_get_powersave( uint32_t *mode, uint32_t *time_ms ); 

// get rssi in sta mode
int mhd_sta_get_rssi( void );
// get rssi in ap mode
int mhd_ap_get_rssi( char *mac_addr );
// get noise in sta mode
int mhd_sta_get_noise( void );

// get softap's client list (AUTHE)
int mhd_ap_get_client_list2( char *mac_list, uint32_t *count );
// get softap's client list (AUTHO)
int mhd_ap_get_client_list( char *mac_list, uint32_t *count );
// get softap's client mac list (MAC)
int mhd_ap_get_mac_list( char *mac_list, uint32_t *count );

int mhd_enable_ampdu( int enable );
int mhd_get_ampdu_ext( uint32_t *state, uint32_t *ba_win_size, uint32_t *mpdu_num, uint32_t *ampdu_rx_size );
int mhd_set_ampdu_ext( uint32_t ba_win_size, uint32_t mpdu_num );

int mhd_get_bus_params_ext( uint32_t *maxtxpktglom, uint32_t *txlazydelay, uint32_t *txglom );
int mhd_set_bus_params_def( void );
int mhd_set_bus_params_ext( uint32_t maxtxpktglom, uint32_t txlazydelay, uint32_t txglom );

int mhd_get_nmode( void );

int mhd_ap_get_rate( void );
int mhd_ap_set_rate( int32_t rate );

extern int mhd_wl_cmd( int argc, char **argv );

// get fw internal dhcpd option for ap mode
int mhd_ap_get_dhcpd_option( void );
// set fw internal dhcpd option for ap mode
int mhd_ap_set_dhcpd_option( uint32_t option );

// polling firmware log
int mhd_check_fwlog( void );
// config firmware log
int mhd_config_fwlog( uint8_t enable, uint32_t interval );

// get scan suppress setting
int mhd_get_scansuppress( void );
// set scan scan suppress setting
void mhd_set_scansuppress( int state );

// function type for network link up/down callback.
typedef void (*mhd_link_callback_t)(void);
// register callback function for network link up and link down. 1: failed, 0: successful
int mhd_sta_register_link_callback( mhd_link_callback_t link_up_cb, mhd_link_callback_t link_down_cb );
// deregister callback function for network link up and link down. 1: failed, 0: successful
int mhd_sta_deregister_link_callback( mhd_link_callback_t link_up_cb, mhd_link_callback_t link_down_cb );

// set beacon li dtim parameter
int mhd_sta_set_bcn_li_dtim( uint8_t dtim );
// get beacon li dtim parameter
int mhd_sta_get_bcn_li_dtim( void );
// set dtim interval
int mhd_sta_set_dtim_interval( int dtim_interval_ms );
	
// set beacon timeout parameter
int mhd_sta_set_bcn_timeout( uint8_t timeout );
// get beacon timeout parameter
int mhd_sta_get_bcn_timeout( void );

// set iovar
int mhd_iovar_setint( char *iovar_str, int value );
// get iovar
int mhd_iovar_getint( char *iovar_str, int *value );

// refresh ip address into dongle host ip table for sta mode
int mhd_sta_aoe_refresh_host_ipv4_table( void );


// Enable monitor mode, 0:success, 1:failed
int mhd_enable_monitor_mode( void );
// Disable monitor mode, 0:success, 1:failed
int mhd_disable_monitor_mode( void );
// Check if monitor mode is enabled, 1:enabled, 0:disabled
int mhd_monitor_mode_is_enabled( void );

typedef void (*mhd_wifi_recv_cb)( unsigned char* pFrame, int iFramLen );
// Register call back function to receive raw packet from wifi fw
void mhd_raw_packet_recv_cb_register( mhd_wifi_recv_cb recv_callback );
// Deregister the call back function
void mhd_raw_packet_recv_cb_deregister( void );

// Change channel in ap mode, if country code set to CHINA(default), you can use channel 1~13
int mhd_ap_set_channel( int channel );
// Change channel in sta mode, if country code set to CHINA(default), you can use channel 1~13
int mhd_sta_set_channel( int channel );
// Set beacon interval, default is 100ms, you can set to 40ms, then it will send out at least 2 beacon in 100ms
int mhd_ap_set_beacon_interval( uint16_t beacon_interval );

// Add packet filer for certain mac address. 0: success, others: failed
int mhd_add_mac_addr_filter( uint8_t *filter_mac_addr, uint16_t filter_bytes, uint32_t filter_id );
// Remove packet filter for certain mac address. 0: success, others: failed
int mhd_remove_mac_addr_filter( uint32_t filter_id );
// Add packet filter for any offset. 0: success, others: failed
int mhd_add_raw_data_filter( uint8_t *pattern, uint16_t pattern_len, uint16_t offset, uint32_t filter_id );
int mhd_add_raw_data_filter_ext( uint8_t *pattern, uint8_t *mask, uint16_t pattern_len, uint16_t offset, uint32_t filter_id );
// Remove packet filter for any offset. 0: success, others: failed
int mhd_remove_raw_data_filter( uint32_t filter_id );


// add custom ie
int mhd_softap_add_custom_ie( const uint8_t* oui, uint8_t sub_type, void* data, uint16_t data_length, uint16_t which_packets );
// remove custom ie
int mhd_softap_remove_custom_ie( const uint8_t* oui, uint8_t sub_type, void* data, uint16_t data_length, uint16_t which_packets );

// set tx packet queue length
extern void mhd_set_packet_tx_queue_length( uint32_t length );
// get tx packet queue length
extern void mhd_get_packet_tx_queue_length( uint32_t *length );
// get tx packet number
extern void mhd_get_data_packet_number( uint32_t *length );
// check if flow control is on
extern uint32_t mhd_is_flow_control_on( void );

// set contry code
extern void mhd_set_country_code(uint32_t country);

// platform dependent ++
// set wl regon pin
extern void mhd_set_wlregon_pin(uint8_t pin);
// set oob pin
extern void mhd_set_oob_pin(uint8_t pin);
// platform dependent --


extern int mhd_set_nmode(  uint32_t mode );
extern int mhd_enable_packet_filter( uint8_t filter_id );
extern int mhd_disable_packet_filter( uint8_t filter_id );
extern int mhd_list_packet_filter( uint32_t filter_id, uint8_t* mask, uint8_t* pattern, uint32_t *offset, uint32_t* size_out );


extern int mhd_sta_add_custom_ie( const uint8_t* oui, uint8_t type, void* data, uint16_t data_length, uint32_t packet_mask );
extern int mhd_sta_del_custom_ie( const uint8_t* oui, uint8_t type, void* data, uint16_t data_length, uint32_t packet_mask );
extern int mhd_sta_set_scansuppress( uint8_t enable );


extern void cmd_wifi_wlutil( uint32_t argc, uint8_t **argv );

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_API_TEST_H_ */
