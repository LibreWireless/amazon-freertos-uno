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
 *  Defines the HOST Network Interface.
 *
 *  Provides prototypes for functions that allow HOST to communicate
 *  with a network stack in an abstract way.
 */

#ifndef HEADER_MHD_NETWORK_INTERFACE_H_INCLUDED
#define HEADER_MHD_NETWORK_INTERFACE_H_INCLUDED

#include "mhd_buffer.h"
#include "mhd_constants.h"

#ifdef __cplusplus
extern "C"
{
#endif



/* @addtogroup netif Network Interface
 * Allows HOST to communicate with a network stack in an abstract way.
 *  @{
 */

/******************************************************
 *       Enumerations
 ******************************************************/

/******************************************************
 *             Function declarations
 ******************************************************/

/*
 * Called by HOST to pass received data to the network stack
 *
 * Implemented in 'network adapter driver' which is specific to the
 * network stack in use.
 * Packets received from the Wi-Fi network by HOST are forwarded to this function which
 * must be implemented in the network interface. Ethernet headers
 * are present at the start of these packet buffers.
 *
 * This function is called asynchronously in the context of the
 * HOST thread whenever new data has arrived.
 * Packet buffers are allocated within HOST, and ownership is transferred
 * to the network stack. The network stack or application is thus
 * responsible for releasing the packet buffers.
 * Most packet buffering systems have a pointer to the 'current point' within
 * the packet buffer. When this function is called, the pointer points
 * to the start of the Ethernet header. There is other inconsequential data
 * before the Ethernet header.
 *
 * It is preferable that the @ref host_network_process_ethernet_data function simply puts
 * the received packet on a queue for processing by another thread. This avoids the
 * HOST thread being unnecessarily tied up which would delay other packets
 * being transmitted or received.
 *
 * @param buffer : Handle of the packet which has just been received. Responsibility for
 *                 releasing this buffer is transferred from HOST at this point.
 * @param interface : The interface (AP or STA) on which the packet was received.
 *
 */
/*@external@*/ extern void host_network_process_ethernet_data( /*@only@*/ host_buffer_t buffer, mhd_interface_t interface ); /* Network stack assumes responsibility for freeing buffer */

/* Functions provided by HOST that may be called by Network Stack */

/*
 * Called by the Network Stack to send an ethernet frame
 *
 * Implemented in 'network adapter driver' which is specific to the
 * network stack in use.
 * This function takes Ethernet data from the network stack and queues it for transmission over the wireless network.
 * The function can be called from any thread context as it is thread safe, however
 * it must not be called from interrupt context since it can block while waiting
 * for a lock on the transmit queue.
 *
 * This function returns immediately after the packet has been queued for transmit,
 * NOT after it has been transmitted.  Packet buffers passed to the HOST core
 * are released inside the HOST core once they have been transmitted.
 *
 * Some network stacks assume the driver send function blocks until the packet has been physically sent. This
 * type of stack typically releases the packet buffer immediately after the driver send function returns.
 * In this case, and assuming the buffering system can count references to packet buffers, the driver send function
 * can take an additional reference to the packet buffer. This enables the network stack and the HOST core driver
 * to independently release their own packet buffer references.
 *
 * @param buffer : Handle of the packet buffer to be sent.
 * @param interface : the interface over which to send the packet (AP or STA)
 *
 */
extern void mhd_network_send_ethernet_data( /*@only@*/ host_buffer_t buffer, mhd_interface_t interface,uint16_t padd ); /* Returns immediately - Host_buffer_tx_completed will be called once the transmission has finished */

/*  @} */

typedef void (*mhd_wifi_packet_sniffer_processor_t)( host_buffer_t buffer, mhd_interface_t interface );
extern mhd_result_t mhd_wifi_set_packet_sniffer_processor( mhd_wifi_packet_sniffer_processor_t function );
extern int mhd_wifi_is_packet_sniffer_processor_null( void );

#ifdef __cplusplus
} /* extern "C" */
#endif
#endif /* ifndef HEADER_MHD_NETWORK_INTERFACE_H_INCLUDED */
