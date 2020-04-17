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
 *  Defines functions to communicate over the IP network
 */

#pragma once

#include "host_utilities.h"
#include "mhd_network_interface.h"
#include "host_network_ext.h"
#include <limits.h>
#include "host_resource.h"
#include "host_wifi.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 * @cond                Macros
 ******************************************************/

#define INITIALISER_IPV4_ADDRESS( addr_var, addr_val )  addr_var = { HOST_IPV4, { .v4 = (uint32_t)(addr_val) } }
#define SET_IPV4_ADDRESS( addr_var, addr_val )          (((addr_var).version = HOST_IPV4),((addr_var).ip.v4 = (uint32_t)(addr_val)))
#define GET_IPV4_ADDRESS( addr_var )                    ((addr_var).ip.v4)
#define HOST_IP_BROADCAST                              (&host_ip_broadcast)
#define MAKE_IPV4_ADDRESS(a, b, c, d)                   ((((uint32_t) a) << 24) | (((uint32_t) b) << 16) | (((uint32_t) c) << 8) | ((uint32_t) d))
#define GET_IPV6_ADDRESS( addr_var )                    ((uint32_t*)((addr_var).ip.v6))
#define SET_IPV6_ADDRESS( addr_var, addr_val )          { \
                                                            uint32_t _value[4] = addr_val; \
                                                            (addr_var).version = HOST_IPV6; \
                                                            (addr_var).ip.v6[0] = _value[0];  \
                                                            (addr_var).ip.v6[1] = _value[1];  \
                                                            (addr_var).ip.v6[2] = _value[2];  \
                                                            (addr_var).ip.v6[3] = _value[3];  \
                                                        }
#define MAKE_IPV6_ADDRESS(a, b, c, d, e, f, g, h)       { \
                                                            (((((uint32_t) (a)) << 16) & 0xFFFF0000UL) | ((uint32_t)(b) &0x0000FFFFUL)), \
                                                            (((((uint32_t) (c)) << 16) & 0xFFFF0000UL) | ((uint32_t)(d) &0x0000FFFFUL)), \
                                                            (((((uint32_t) (e)) << 16) & 0xFFFF0000UL) | ((uint32_t)(f) &0x0000FFFFUL)), \
                                                            (((((uint32_t) (g)) << 16) & 0xFFFF0000UL) | ((uint32_t)(h) &0x0000FFFFUL))  \
                                                        }


/******************************************************
 *                 Type Definitions
 ******************************************************/

typedef void (*host_ip_address_change_callback_t)( void* arg );
typedef host_result_t (*host_tcp_stream_write_callback_t)( void* tcp_stream, const void* data, uint32_t data_length );

/******************************************************
 *            Enumerations
 ******************************************************/

/**
 * IP Version
 */
typedef enum
{
    HOST_IPV4 = 4,
    HOST_IPV6 = 6,
    HOST_INVALID_IP = INT_MAX
} host_ip_version_t;

/******************************************************
 *             Structures
 ******************************************************/

/**
 * IP Address Structure
 */
typedef struct
{
    host_ip_version_t version;

    union
    {
        uint32_t v4;
        uint32_t v6[4];
    } ip;
} host_ip_address_t;

/******************************************************
 *                 Global Variables
 ******************************************************/

extern const host_ip_address_t host_ip_broadcast;

/******************************************************
 *               Function Declarations
 * @endcond
 ******************************************************/

/** @} */

/*****************************************************************************/
/** @addtogroup icmp       ICMP ping
 *  @ingroup ipcoms
 *
 * Functions for ICMP echo requests (Internet Control Message Protocol)
 * This is commonly known as ping
 *
 *  @{
 */
/*****************************************************************************/

/** Sends a ping (ICMP echo request)
 *
 *  Sends a ICMP echo request (a ping) and waits for the response.
 *  Supports both IPv4 and IPv6
 *
 * @param[in]  interface  : The interface (AP or STA) on which to send the ping
 * @param[in]  address    : The IP address to which the ping should be sent
 * @param[in]  timeout_ms : Timeout value in milliseconds
 * @param[out] elapsed_ms : Pointer to a uint32_t which will receive the elapsed response time in milliseconds
 *
 * @return @ref host_result_t
 */
host_result_t host_ping( host_interface_t interface, const host_ip_address_t* address, uint32_t timeout_ms, uint32_t* elapsed_ms );

/** @} */

/*****************************************************************************/
/** @addtogroup dns       DNS lookup
 *  @ingroup ipcoms
 *
 * Functions for DNS (Domain Name System) lookups
 *
 *  @{
 */
/*****************************************************************************/

/** Looks up a hostname via DNS
 *
 *  Sends a DNS query to find an IP address for a given hostname string.
 *
 *  @note :  hostname is permitted to be in dotted quad form
 *  @note :  The returned IP may be IPv4 or IPv6
 *
 * @param[in]  hostname   : A null-terminated string containing the hostname to be looked-up
 * @param[out] address    : A pointer to an IP address that will receive the resolved address
 * @param[in]  timeout_ms : Timeout value in milliseconds
 *
 * @return @ref host_result_t
 */
host_result_t host_hostname_lookup( const char* hostname, host_ip_address_t* address, uint32_t timeout_ms );

/** @} */

/*****************************************************************************/
/** @addtogroup igmp       IGMP multicast
 *  @ingroup ipcoms
 *
 * Functions for joining/leaving IGMP (Internet Group Management Protocol) groups
 *
 *  @{
 */
/*****************************************************************************/

/** @} */

/*****************************************************************************/
/** @addtogroup pktmgmt       Packet management
 *  @ingroup ipcoms
 *
 * Functions for allocating/releasing/processing packets from the HOST packet pool
 *
 *  @{
 */
/*****************************************************************************/

/** @} */

/*****************************************************************************/
/** @addtogroup rawip       Raw IP
 *  @ingroup ipcoms
 *
 * Functions to access IP information from network interfaces
 *
 *  @{
 */
/*****************************************************************************/

/** Retrieves the IPv4 gateway address for an interface
 *
 * Retrieves the gateway IPv4 address for an interface (AP or STA) if it
 * exists.
 *
 * @param[in]   interface    : the interface (AP or STA)
 * @param[out]  ipv4_address : the address structure to be filled with the
 *                             gateway IP
 *
 * @return @ref host_result_t
 */
extern host_result_t host_ip_get_gateway_address( host_interface_t interface, host_ip_address_t* ipv4_address );


/** Registers a callback function that gets called when the IP address has changed
 *
 * Registers a callback function that gets called when the IP address has changed
 *
 * @param[in] callback : callback function to register
 * @param[in] arg      : pointer to the argument to pass to the callback
 *
 * @return @ref host_result_t
 */
host_result_t host_ip_register_address_change_callback( host_ip_address_change_callback_t callback, void* arg );


/** De-registers a callback function that gets called when the IP address has changed
 *
 * De-registers a callback function that gets called when the IP address has changed
 *
 * @param[in] callback : callback function to de-register
 *
 * @return @ref host_result_t
 */
host_result_t host_ip_deregister_address_change_callback( host_ip_address_change_callback_t callback );

/** @} */

#ifdef __cplusplus
} /*extern "C" */
#endif
