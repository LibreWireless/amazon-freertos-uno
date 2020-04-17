/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/** @file
 */

#ifndef INCLUDED_MHD_AP_EXT_H_
#define INCLUDED_MHD_AP_EXT_H_

#include <stdint.h>
#include "mhd_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

mhd_result_t mhd_wifi_ap_start_dhcpd( uint32_t ip_address );
mhd_result_t mhd_wifi_ap_stop_dhcpd( void );
mhd_result_t mhd_wifi_ap_set_dhcpd_option( uint32_t option );
mhd_result_t mhd_wifi_ap_get_dhcpd_option( uint32_t *option );

mhd_result_t mhd_wifi_get_ap( uint32_t *state );
mhd_result_t mhd_wifi_set_ap( host_bool_t enable );
mhd_result_t mhd_wifi_ap_down( void );

mhd_result_t mhd_wifi_ap_auth( uint32_t auth );
mhd_result_t mhd_wifi_ap_pmk( const uint8_t* security_key, uint8_t key_length );
mhd_result_t mhd_wifi_ap_wpa( uint32_t wpa_auth );
mhd_result_t mhd_wifi_ap_wsec( uint32_t wsec );
mhd_result_t mhd_wifi_ap_ssid( wlc_ssid_t ssid );

mhd_result_t mhd_wifi_ap_set_hidden( host_bool_t enable );
mhd_result_t mhd_wifi_ap_get_hidden( uint32_t *state );

mhd_result_t mhd_wifi_ap_get_authe_list( char *mac_list, uint32_t *count );
mhd_result_t mhd_wifi_ap_get_autho_list( char *mac_list, uint32_t *count );
mhd_result_t mhd_wifi_ap_get_mac_list( char *mac_list, uint32_t *count );

mhd_result_t mhd_wifi_set_apsta( host_bool_t enable );
mhd_result_t mhd_wifi_get_apsta( uint32_t *state );

mhd_result_t mhd_wifi_ap_set_beacon_interval( uint16_t beacon_interval );
mhd_result_t mhd_wifi_ap_get_beacon_interval( uint16_t *beacon_interval );
mhd_result_t mhd_wifi_ap_get_dtim( uint16_t *dtim );

extern host_bool_t mhd_wifi_ap_is_up;

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_AP_EXT_H_ */
