/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_MHD_WOWL_H_
#define INCLUDED_MHD_WOWL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define WOWL_PATTERN_ARG_ADD                 "add"
#define WOWL_PATTERN_ARG_DEL                 "del"
#define WOWL_PATTERN_ARG_CLR                 "clr"


typedef enum 
{
    wowl_pattern_type_bitmap = 0,
    wowl_pattern_type_arp,
    wowl_pattern_type_na
} wowl_pattern_type_t;

typedef struct 
{
    uint32_t		    masksize;		/* Size of the mask in #of bytes */
    uint32_t		    offset;		        /* Pattern byte offset in packet */
    uint32_t		    patternoffset;	/* Offset of start of pattern in the structure */
    uint32_t		    patternsize;	/* Size of the pattern itself in #of bytes */
    uint32_t		    id;			/* id */
    uint32_t		    reasonsize;		/* Size of the wakeup reason code */
    wowl_pattern_type_t type;		/* Type of pattern */
    /* Mask follows the structure above */
    /* Pattern follows the mask is at 'patternoffset' from the start */
} wowl_pattern_t;

typedef struct
{
    uint32_t count;
    wowl_pattern_t pattern[1];
} wowl_pattern_list_t;

typedef struct 
{
    uint32_t	pci_wakeind;	        /* Whether PCI PMECSR PMEStatus bit was set */
    uint32_t	ucode_wakeind;	/* What wakeup-event indication was set by ucode */
} wowl_wakeind_t;

mhd_result_t mhd_wifi_wowl_event( uint32_t event_bitmap, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_activate( host_bool_t enable, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_clear( host_bool_t enable, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_clear_wakeind( mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_wakeind( wowl_wakeind_t *wakeind, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_pattern( mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_event( uint32_t *event_bitmap, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_activate( uint32_t *status, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_status( uint32_t *status, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_gpio( uint32_t *gpio_status, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_extgpio( uint32_t *gpio_status, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_check_gpiopol( uint32_t *gpio_status, mhd_interface_t interface );


mhd_result_t mhd_wifi_wowl_pattern_config( char *ops, int offset, char *msk, char *patt, mhd_interface_t interface );
mhd_result_t mhd_wifi_wowl_pattern( mhd_interface_t interface );

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_WOWL_H_ */
