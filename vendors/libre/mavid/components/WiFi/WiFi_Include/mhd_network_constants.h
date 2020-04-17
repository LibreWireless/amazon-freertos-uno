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
 *  Provides packet size constants which are useful for implementations of the
 *  network interface and buffer interface.
 */


#ifndef INCLUDED_MHD_NETWORK_CONSTANTS_H_
#define INCLUDED_MHD_NETWORK_CONSTANTS_H_

#include "mhd_buffer_interface.h"
#include "mhd_bus_protocol.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 * @cond       Constants
 ******************************************************/

/**
 * The maximum size of the mhd_buffer_header_t structure (i.e. largest bus implementation)
 */
#define MAX_BUS_HEADER_LENGTH (12)

/**
 * The maximum size of the SDPCM + BDC header, including offsets and reserved space
 * 12 bytes - SDPCM header
 * 2 bytes  - Extra offset for SDPCM headers that come as 14 bytes
 * 4 bytes  - BDC header
 * 4 bytes  - offset for one extra BDC reserved long int.
 */
#define MAX_SDPCM_HEADER_LENGTH (22)

/**
 * The space in bytes required for headers in front of the Ethernet header.
 */
#define HOST_LINK_OVERHEAD_BELOW_ETHERNET_FRAME ( sizeof(mhd_buffer_header_t) + MHD_SDPCM_HEADER_RESERVED_LENGTH )

#define HOST_LINK_DATA_PAD_THRESHOLD 1400
#define HOST_LINK_SDIO_BLOCK_SZ   512

/**
 * The maximum space in bytes required for headers in front of the Ethernet header.
 * This definition allows HOST to use a pre-built bus-generic network stack library regardless of choice of bus.
 * Note: adjust accordingly if a new bus is added.
 */
#define HOST_LINK_OVERHEAD_BELOW_ETHERNET_FRAME_MAX ( MAX_BUS_HEADER_LENGTH + MAX_SDPCM_HEADER_LENGTH )

/**
 * The space in bytes required after the end of an Ethernet packet
 */
#define HOST_LINK_TAIL_AFTER_ETHERNET_FRAME     ( 0 )

/**
 * The size of an Ethernet header
 */
#define HOST_ETHERNET_SIZE         (14)

/**
 * The size in bytes of the Link layer header i.e. the Host specific headers and the Ethernet header
 */
#define HOST_PHYSICAL_HEADER       (HOST_LINK_OVERHEAD_BELOW_ETHERNET_FRAME_MAX + HOST_ETHERNET_SIZE)

/**
 * The size in bytes of the data after Link layer packet
 */
#define HOST_PHYSICAL_TRAILER      (HOST_LINK_TAIL_AFTER_ETHERNET_FRAME)

/**
 * The maximum size in bytes of the data part of an Ethernet frame
 */
#ifndef HOST_PAYLOAD_MTU
#define HOST_PAYLOAD_MTU           (1500)
#endif

/**
 * The maximum size in bytes of a packet used within Host
 */
#define HOST_LINK_MTU              (HOST_PAYLOAD_MTU + HOST_PHYSICAL_HEADER + HOST_PHYSICAL_TRAILER)


/**
 * Ethernet Ethertypes
 */
#define HOST_ETHERTYPE_IPv4    0x0800
#define HOST_ETHERTYPE_IPv6    0x86DD
#define HOST_ETHERTYPE_ARP     0x0806
#define HOST_ETHERTYPE_RARP    0x8035
#define HOST_ETHERTYPE_EAPOL   0x888E
#define HOST_ETHERTYPE_8021Q   0x8100

/** @endcond */

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ifndef INCLUDED_MHD_NETWORK_CONSTANTS_H_ */
