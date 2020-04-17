/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

#ifndef INCLUDED_MHD_NETWORK_H_
#define INCLUDED_MHD_NETWORK_H_

#include "lwip/err.h"
#include "mhd_buffer.h"

#ifdef __cplusplus
extern "C"
{
#endif

struct pbuf;
struct netif;

/******************************************************
 *             Constants
 ******************************************************/

/******************************************************
 *             Structures
 ******************************************************/

/******************************************************
 *             Function declarations
 ******************************************************/

#if 1 //!defined(__LITEOS_VER__)
extern err_t ethernetif_init( /*@partial@*/ struct netif *netif );
#endif
err_t wifidrv_output( struct netif *netif, /*@only@*/ struct pbuf *p );

//extern err_t wifidrv_output( struct netif *netif, /*@only@*/ host_buffer_t p );
#ifdef LWIP_NETIF_PROMISC
void wifidrv_config(struct netif *netif, uint32_t config_flags, u8_t setBit);
#endif

/******************************************************
 *             Global variables
 ******************************************************/

#ifdef __cplusplus
}
#endif

#endif /* define INCLUDED_MHD_NETWORK_H_ */
