/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lwip/ip_addr.h"
#include "lwip/netif.h"
#include "host_result.h"
#include "host_wifi.h"
#include "host_rtos_common.h"

#include "mhd_network_constants.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *                      Macros
 ******************************************************/

/******************************************************
 *                    Constants
 ******************************************************/

#define IP_HANDLE(interface)   (host_ip_handle[(interface)&3])

extern host_result_t lwip_to_host_err[];
#define LWIP_TO_HOST_ERR( lwip_err )  ((lwip_err >= ERR_ISCONN)? lwip_to_host_err[ -lwip_err ] : HOST_UNKNOWN_NETWORK_STACK_ERROR )

/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

/******************************************************
 *                 Global Variables
 ******************************************************/

/* Note: These objects are for internal use only! */
///extern xTaskHandle     host_thread_handle;
extern struct netif   host_ip_handle[3];
#if LWIP_DHCP
extern struct dhcp     host_dhcp_handle;
#endif

/******************************************************
 *               Function Declarations
 ******************************************************/

// flag: 1 stop queue, 0 wakeup queue
int mhd_wifi_notify_tcpip_queue( uint32_t sleep );

#ifdef __cplusplus
} /*extern "C" */
#endif
