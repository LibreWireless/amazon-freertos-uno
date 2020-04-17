/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_MHD_STA_H_
#define INCLUDED_MHD_STA_H_

#ifdef __cplusplus
extern "C"
{
#endif

mhd_result_t mhd_wifi_get_bssid( wl_ether_addr_t* bssid );
mhd_result_t mhd_wifi_set_bcn_li_dtim( uint8_t dtim );
mhd_result_t mhd_wifi_get_bcn_li_dtim( uint8_t *dtim );

mhd_result_t mhd_wifi_set_sup_wpa( host_bool_t enable );
mhd_result_t mhd_wifi_get_sup_wpa( host_bool_t *enable );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_STA_H_ */
