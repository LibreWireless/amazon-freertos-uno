/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_MHD_WIFI_EXT_H_
#define INCLUDED_MHD_WIFI_EXT_H_

#ifdef __cplusplus
extern "C"
{
#endif

mhd_result_t mhd_wifi_set_host_sleep( host_bool_t enable );
mhd_result_t mhd_wifi_get_host_sleep( uint32_t *state );

mhd_result_t mhd_wifi_set_deep_sleep( host_bool_t enable );
mhd_result_t mhd_wifi_get_deep_sleep( uint32_t *state );

mhd_result_t mhd_wifi_get_bss_up( host_bool_t *enabled, mhd_interface_t interface  );

mhd_result_t mhd_wifi_get_pm2_ret_time( uint32_t *time );
mhd_result_t mhd_wifi_get_powersave( uint32_t *mode );

mhd_result_t mhd_wifi_set_mpc( host_bool_t enable );
mhd_result_t mhd_wifi_get_mpc( uint32_t *state );

mhd_result_t mhd_wifi_get_nmode( uint32_t *mode, mhd_interface_t interface);

mhd_result_t mhd_wifi_enable_ampdu( host_bool_t enable, mhd_interface_t interface );
mhd_result_t mhd_wifi_get_ampdu_ext( uint32_t *state, uint32_t *ba_win_size, uint32_t *mpdu_num, uint32_t *ampdu_rx_size );
mhd_result_t mhd_wifi_set_ampdu_ext( uint32_t ba_win_size, uint32_t mpdu_num );

mhd_result_t mhd_wifi_set_bus_params_ext( uint32_t maxtxpktglom, uint32_t txlazydelay, uint32_t txglom );
mhd_result_t mhd_wifi_get_bus_ext( uint32_t *maxtxpktglom, uint32_t *txlazydelay, uint32_t *txglom );
mhd_result_t mhd_wifi_set_bus_params_def( void );


mhd_result_t mhd_wifi_set_arpoe( host_bool_t enable );
mhd_result_t mhd_wifi_get_arpoe( uint32_t *status );

mhd_result_t mhd_wifi_set_ht20( void );
mhd_result_t mhd_wifi_set_ht40( void );
mhd_result_t mhd_wifi_set_ht_coex( void );

mhd_result_t mhd_wifi_get_scansuppress( uint32_t *status );
mhd_result_t mhd_wifi_set_scansuppress( host_bool_t enable );

// wifi_ext.c
extern mhd_result_t mhd_join_ap( char *ssid, char *password, char bfastconnect );
extern mhd_result_t mhd_leave_ap( void );
extern mhd_result_t mhd_join_ap_with_detail( char *ssid, char *password, uint8_t security, char *bssid, uint8_t channel );
extern mhd_result_t mhd_reassociate_ap( void );

// mhd_wifi.c
extern mhd_result_t mhd_wifi_is_ready_to_transceive( mhd_interface_t interface );

// APIs from 3.5.1 ++
/** Gets the current EAPOL key timeout for the given interface
 *
 * @param interface         : the interface for which we want the EAPOL key timeout
 *        eapol_key_timeout : pointer to store the EAPOL key timeout value
 *
 * @return  HOST_SUCCESS : if success
 *          Error code    : error code to indicate the type of error
 */
extern mhd_result_t mhd_wifi_get_supplicant_eapol_key_timeout( mhd_interface_t interface, int32_t* eapol_key_timeout );

/** Sets the current EAPOL key timeout for the given interface
 *
 * @param interface         : the interface for which we want to set the EAPOL key timeout
 *        eapol_key_timeout : EAPOL key timeout value
 *
 * @return  HOST_SUCCESS : if success
 *          Error code    : error code to indicate the type of error
 */
extern mhd_result_t mhd_wifi_set_supplicant_eapol_key_timeout( mhd_interface_t interface, int32_t eapol_key_timeout );

/** Sets HT mode for the given interface
 *
 *  NOTE:
 *     Ensure WiFi core and network is down before invoking this function.
 *     Refer host_wifi_down() API for more details.
 *
 * @param interface       : the interface for which HT mode to be changed.
 *        ht_mode         : enumeration value which indicates the HT mode
 *
 * @return  HOST_SUCCESS : if success
 *          Error code    : error code to indicate the type of error, if HT mode could not be successfully set
 */
extern mhd_result_t mhd_wifi_set_ht_mode( mhd_interface_t interface, host_ht_mode_t ht_mode );

/** Gets the current HT mode of the given interface
 *
 * @param interface       : the interface for which current HT mode to be identified
 *        ht_mode         : pointers to store the results (i.e., currently configured HT mode)
 *
 * @return  HOST_SUCCESS : if success
 *          Error code    : error code to indicate the type of error, if HT mode could not be successfully get
 */
extern mhd_result_t mhd_wifi_get_ht_mode( mhd_interface_t interface, host_ht_mode_t* ht_mode );

extern mhd_result_t mhd_wifi_set_passphrase( const uint8_t* security_key, uint8_t key_length, mhd_interface_t interface );

/* Set and get IOVAR parameters */
extern mhd_result_t mhd_wifi_set_iovar_value( const char* iovar, uint32_t  value, mhd_interface_t interface );
extern mhd_result_t mhd_wifi_get_iovar_value( const char* iovar, uint32_t* value, mhd_interface_t interface );
extern mhd_result_t mhd_wifi_set_ioctl_value( uint32_t ioctl, uint32_t  value, mhd_interface_t interface );
extern mhd_result_t mhd_wifi_get_ioctl_value( uint32_t ioctl, uint32_t* value, mhd_interface_t interface );

/** Gets the BSS index that the given interface is mapped to in Host
 *
 * @param interface       : the interface for which to get the BSS index
 *
 * @return  BSS index
 */
extern uint32_t     mhd_get_bss_index( mhd_interface_t interface );
// APIs from 3.5.1 --

extern void mhd_before_join(void);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_WIFI_EXT_H_ */
