/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_MHD_API_RELEASE_H_
#define INCLUDED_MHD_API_RELEASE_H_

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
#if 0
enum mhd_security {
    MHD_SECURE_OPEN,
    MHD_WPA_PSK_AES,     // WPA-PSK AES
    MHD_WPA2_PSK_AES,    // WPA2-PSK AES
    MHD_WEP_OPEN,        // WEP+OPEN
    MHD_WEP_SHARED,      // WEP+SHARE
    MHD_WPA_PSK_TKIP,    // WPA-PSK TKIP
    MHD_WPA_PSK_MIXED,   // WPA-PSK AES & TKIP MIXED
    MHD_WPA2_PSK_TKIP,   // WPA2-PSK TKIP
    MHD_WPA2_PSK_MIXED,   // WPA2-PSK AES & TKIP MIXED
    MHD_WPS_OPEN, // WPS OPEN
    MHD_WPS_AES, // WPS AES
    MHD_IBSS_OPEN, // ADHOC
    MHD_WPA_ENT_AES,     // WPA-ENT AES
    MHD_WPA_ENT_TKIP,    // WPA-ENT TKIP
    MHD_WPA_ENT_MIXED,   // WPA-ENT AES & TKIP MIXED
    MHD_WPA2_ENT_AES,    // WPA2-ENT AES
    MHD_WPA2_ENT_TKIP,   // WPA2-ENT TKIP
    MHD_WPA2_ENT_MIXED   // WPA2-ENT AES & TKIP MIXED
} mhd_security_info_t;
#endif

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

void cmd_wifi_ver( uint32_t argc, uint8_t **argv );
void cmd_wifi_mac( uint32_t argc, uint8_t **argv );
void cmd_wifi_init( uint32_t argc, uint8_t **argv );
void cmd_start_scan( uint32_t argc, uint8_t **argv );
void cmd_get_scan_results( uint32_t argc, uint8_t **argv );
void cmd_softap_start( uint32_t argc, uint8_t **argv );
void cmd_softap_stop( uint32_t argc, uint8_t **argv );
void cmd_softap_state( uint32_t argc, uint8_t **argv );
void cmd_softap_hidden_enable( uint32_t argc, uint8_t **argv );
void cmd_softap_hidden_disable( uint32_t argc, uint8_t **argv );
void cmd_softap_get_hidden( uint32_t argc, uint8_t **argv );
void cmd_sta_start( uint32_t argc, uint8_t **argv );
void cmd_sta_reassociate( uint32_t argc, uint8_t **argv );
void cmd_sta_stop( uint32_t argc, uint8_t **argv );
void cmd_sta_state( uint32_t argc, uint8_t **argv );
void cmd_sta_linkstate( uint32_t argc, uint8_t **argv );
void cmd_ap_wowl_init( uint32_t argc, uint8_t **argv );
void cmd_ap_wowl( uint32_t argc, uint8_t **argv );
void cmd_sta_wowl_init( uint32_t argc, uint8_t **argv );
void cmd_sta_wowl( uint32_t argc, uint8_t **argv );
void cmd_tcpka_config( uint32_t argc, uint8_t **argv );
void cmd_tcpka_config_ext( uint32_t argc, uint8_t **argv );
void cmd_tcpka_clear( uint32_t argc, uint8_t **argv );

void cmd_easy_setup_start( uint32_t argc, uint8_t **argv );
void cmd_easy_setup_stop( uint32_t argc, uint8_t **argv );
void cmd_easy_setup_task( uint32_t argc, uint8_t **argv );

//HT**
#if 0

//#if defined(__LITEOS_VER__)
struct ether_addr
{
    uint8_t octet[6];
};
#endif

typedef struct {
    uint8_t len;     /**< SSID length */
    uint8_t val[32]; /**< SSID name (AP name)  */
} ssid_t;

typedef struct {
    uint8_t octet[6]; /**< Unique 6-byte MAC address */
} mac_t;

struct ipv4_addr {
    uint8_t   addr[4];
};

typedef struct tcpka_conn_info {
    uint32_t tcpka_sess_ipid;
    uint32_t tcpka_sess_seq;
    uint32_t tcpka_sess_ack;
} tcpka_conn_sess_info_t;

// Used by Hisilicon now
typedef struct tcpka_conn_ext {
    struct ether_addr dst_mac; /* Destinition Mac */
    struct ipv4_addr src_ip;   /* Sorce IP */
    struct ipv4_addr dst_ip;   /* Destinition IP */
    uint16_t ipid;             /* Ip Identification */
    uint16_t srcport;          /* Source Port Address */
    uint16_t dstport;          /* Destination Port Address */
    uint32_t seqnum;           /* TCP Sequence Number */
    uint32_t acknum;           /* TCP Ack Number */
    uint16_t tcpwin;           /* TCP window */
    uint32_t tsval;            /* Timestamp Value */
    uint32_t tsecr;            /* Timestamp Echo Reply */
    uint32_t last_payload_len; /* last packet payload len */ 
    uint32_t ka_payload_len;   /* keep alive payload length */
    char *ka_payload;    /* keep alive payload */
} tcpka_conn_ext_t;

typedef struct tcpka_timer {
    uint16_t interval;   //保活间隔
    uint16_t retry_interval;        //重传间隔
    uint16_t retry_count;           //重传次数
} tcpka_timer_t;

typedef struct udpka_packet_info
{
    uint8_t     keep_alive_id;  /**< Unique identifier for the keep alive packet */
    uint32_t    period_msec;    /**< Repeat interval in milliseconds             */
    uint16_t    packet_length;  /**< Length of the keep alive packet             */
    uint8_t*    packet;         /**< Pointer to the keep alive packet            */
} udpka_packet_info_t;

typedef struct udpka_conn
{
    uint16_t interval_sec;
    uint16_t timeout_sec;
    int sock;
    char *server_ip;
    uint16_t server_port;
    char *ka_payload;
    int ka_payload_len;
} udpka_conn_t;

typedef struct mhd_ap_info {
    char ssid[32];
    char bssid[6];
    uint32_t channel;
    uint32_t security;
    uint32_t rssi;
} mhd_ap_info_t;

typedef struct
{
    ssid_t SSID;
    uint8_t security;
    uint8_t channel;
    uint8_t security_key_length;
    char security_key[ 64 ];
    mac_t BSSID;
} mhd_es_ap_info_t;

typedef struct
{
    ssid_t SSID;
    uint8_t security;
    uint8_t channel;
    uint8_t security_key_length;
    char security_key[ 64 ];
    mac_t BSSID;
} mhd_ap_connect_info_t;


// Release APIs
///////////////////////////////////////////////////////////////////////

// get fw version. 0: success, 1: failed
int mhd_get_fw_version( void );
// get MAC address. 0: success, 1: failed
int mhd_get_mac_address(char addr[6]);
int mhd_set_mac_address(char addr[], int iface );


// download fw/nvram image, driver init. 0: success, 1: failed
int mhd_module_init(void);
// driver deinit. 0: success, 1: failed
int mhd_module_exit(void);

// scan in station mode
int mhd_start_scan(void);
// get scan result in station mode
int mhd_get_scan_results(mhd_ap_info_t *results, int *num);

// ssid:  less than 32 bytes
// password: less than 32 bytes
// security: 0-open, 1-wpa_psk_aes, 2-wpa2_psk_aes
// channel: 1~13
// ip_address: 0x0100a8c0 means 192.168.0.1
int mhd_softap_start(char *ssid, char *password, uint8_t security, uint8_t channel);
// stop softap. 
// input 0:not force, 1:force to stop
// return 0:success, 1:failed
int mhd_softap_stop(uint8_t force);
// get softap state. 0:disabled, 1:enabled, -1:error
int mhd_softap_get_state( void );
// start dhcpd. 0: success, 1: failed
int mhd_softap_start_dhcpd(uint32_t ip_address);
// stop dhcpd. 0: success, 1: failed
int mhd_softap_stop_dhcpd( void );

// set softap hidden. 0:disabled, 1:enabled
int mhd_softap_set_hidden( int enable );
// get softap hidden. 0:disabled, 1:enabled, -1:error
int mhd_softap_get_hidden( void );

// station connects to ap. 0:success, 1:failed
// security: 0-open, 1-wpa_psk_aes, 2-wpa2_psk_aes
int mhd_sta_connect( char *ssid, char *bssid, uint8_t security, char *password, uint8_t channel );
// station reassociate with ap. 0:success, 1:failed
int mhd_sta_reassociate( void );
// station leaves ap and network down
// input 0:not force, 1:force to disconnect
// return 0:success, 1:failed
int mhd_sta_disconnect( uint8_t force );
// get station state. 0:disabled, 1:enabled, -1:error
int mhd_sta_get_state( void );
// station get connection state. 0:disconnected, 1:connected
int mhd_sta_get_connection( void );
// set station interface up, and config static ip if necessary
int mhd_sta_network_up( uint32_t ip, uint32_t gateway, uint32_t netmask );
// set station interface down
int mhd_sta_network_down( void );

// init wowl in softap mode
int mhd_ap_wowl_init( void );
// enable wowl in softap mode
int mhd_ap_wowl_enable( void );
// clear wowl settings in softap mode
int mhd_ap_wowl_disable( void );
// check wowl status in softap mode
int mhd_ap_wowl_status( void );

// enable wowl in station mode. input net pattern string and offset, should be called once
// pattern_string: wakeup packet payload
// offset: payload offset in wakeup packet, eg: TCP - 54, UDP - 42
// eg: mhd_sta_wowl_init("0x983B16F8F39C", 54);
int mhd_sta_wowl_init( char *pattern_string, int offset );
// enable wowl in station mode. input net pattern string and offset, should be called once
// pattern_string: wakeup packet payload
// offset: payload offset in wakeup packet, eg: TCP - 54, UDP - 42, UDP_HEADER - 34
// eg: mhd_wowl_sta_add_ext(0x22B7000000000000983B16F8F39C, 0xffff000000000000ffffffffffff, 34);
int mhd_sta_wowl_init_ext( char *pattern_string, char *mask_string, int offset );
// enable wowl in station mode
int mhd_sta_wowl_enable( void );
// disable wowl in station mode
int mhd_sta_wowl_disable( void );
// check wowl status in station mode
int mhd_sta_wowl_status( void );
// check wowl wake up reason
int mhd_sta_wowl_wakeind( uint32_t *wakeind );

// config tcpka extention. 0:success, 1:failed
int mhd_tcpka_config_ext( tcpka_conn_ext_t *session, tcpka_timer_t *timer );
// delete tcpka config extention. 0:success, 1:failed
int mhd_tcpka_clear_ext( uint32_t sess_id );
int mhd_tcpka_clear_all( void );
// get tcpka info. 0:success, 1:failed
int mhd_tcpka_get_info( tcpka_conn_sess_info_t *session_info );
// test tcpka. 0:success, 1:failed
int mhd_tcpka_config_ext_test( char *server_ip, uint16_t server_port, char *ka_payload, int ka_payload_len );

#ifdef MHD_UDPKA_SUPPORTED
// config udpka. 0:success, 1:failed
int mhd_udpka_config( udpka_conn_t *udpka_conn );
// clear the udpka keepalive settings
// input: if we enabled N udpka servers, we should input N to clear all the server settings
// return 0:success, 1:failed
int mhd_udpka_clear_all( uint8_t servers_count );

// test udpka. 0:success, 1:failed
int mhd_udpka_config_ext_test( udpka_conn_t *udpka_conn );
// config udpka extention. 0:success, 1:failed
int mhd_udpka_config_ext( udpka_conn_t *udpka_conn );
// get udpka info. 0:success, 1:failed
int mhd_udpka_get_info( udpka_packet_info_t *packet_info );
// get udpka timeout. 0:success, 1:failed
int mhd_get_udpka_timeout( uint32_t *time_sec );
// set udpka timeout. 0:success, 1:failed
int mhd_set_udpka_timeout( uint32_t time_sec );
#endif

#ifdef MHD_ES_COOEE
// enable cooee protocol
void mhd_es_enable_cooee(void);
#endif
#ifdef MHD_ES_NEEZE
// enable neeze protocol
void mhd_es_enable_neeze(void);
#endif
#ifdef MHD_ES_AKISS
// enable airkiss protocol
void mhd_es_enable_akiss(void);
#endif
#ifdef MHD_ES_CHANGHONG
// enable changhong protocol
void mhd_es_enable_changhong(void);
#endif
#ifdef MHD_ES_JINGDONG
// enable jingdong protocol
void mhd_es_enable_jingdong(void);
#endif
#ifdef MHD_ES_JD
// enable jd protocol
void mhd_es_enable_jd(void);
#endif

#ifdef MHD_EASY_SETUP
// start easy setup
int mhd_easy_setup_start(mhd_es_ap_info_t *ap_info);
// stop easy setup
int mhd_easy_setup_stop(void);
#endif

extern void mhd_set_country_code(uint32_t country);
extern int mhd_suspend( void );
extern int mhd_resume( void );



extern int mhd_ap_get_client_list2( char *mac_list, uint32_t *count );
extern int mhd_ap_get_client_list( char *mac_list, uint32_t *count );
extern int mhd_ap_get_mac_list( char *mac_list, uint32_t *count );
extern int mhd_ap_get_rssi( char *mac_list );
extern int mhd_softap_add_custom_ie( const uint8_t* oui, uint8_t sub_type, void* data, uint16_t data_length, uint16_t which_packets );
extern int mhd_softap_remove_custom_ie( const uint8_t* oui, uint8_t sub_type, void* data, uint16_t data_length, uint16_t which_packets );
extern int mhd_ap_get_rate( void );
extern int mhd_ap_set_rate( int32_t rate );
extern int mhd_ap_get_dhcpd_option( void );
extern int mhd_ap_set_dhcpd_option( uint32_t option );
extern int mhd_ap_get_beacon_interval( uint16_t *beacon_interval );
extern int mhd_ap_set_beacon_interval( uint16_t beacon_interval );

extern void cmd_tcpka_config_ext_test( uint32_t argc, uint8_t **argv );
extern void cmd_tcpka_info( uint32_t argc, uint8_t **argv );
extern void cmd_tcpka_all_info( uint32_t argc, uint8_t **argv );
extern int cmd_wifi_release(uint32_t argc, uint8_t **argv);
extern void cmd_wifi_commands(uint32_t argc, uint8_t **argv);



#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_API_RELEASE_H_ */
