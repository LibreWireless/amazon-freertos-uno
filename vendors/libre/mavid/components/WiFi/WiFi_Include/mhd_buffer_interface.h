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
 *  Defines the HOST Buffer Interface.
 *
 *  Provides prototypes for functions that allow HOST to use packet
 *  buffers in an abstract way.
 *
 */

#ifndef INCLUDED_MHD_BUFFER_INTERFACE_H_
#define INCLUDED_MHD_BUFFER_INTERFACE_H_

#include "mhd_buffer.h"
#include "mhd_constants.h"
#include "mhd_bus_protocol.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 * @cond       Constants
 ******************************************************/

typedef enum
{
    MHD_NETWORK_TX,
    MHD_NETWORK_RX
} mhd_buffer_dir_t;


typedef host_buffer_t  mhd_buffer_queue_ptr_t;

#pragma pack(1)

typedef struct
{
    /*@owned@*/  mhd_buffer_queue_ptr_t  queue_next;
#ifdef MHD_BUS_HAS_HEADER
                 mhd_bus_header_t        bus_header;
#endif /* ifdef MHD_BUS_HAS_HEADER */
} mhd_buffer_header_t;

#pragma pack()

/** @endcond */

/** @addtogroup buffif Buffer Interface
 * Allows HOST to use packet buffers in an abstract way.
 *  @{
 */

/******************************************************
 *             Function declarations
 ******************************************************/

/**
 * Initialize the packet buffer interface
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * Some implementations of the packet buffer interface may need additional
 * information for initialization, especially the location of packet buffer
 * pool(s). These can be passed via the 'native_arg' parameter. The @ref mhd_management_init
 * function passes the value directly from it's parameters.
 *
 * @param native_arg  An implementation specific argument passed from @ref mhd_management_init
 *
 * @return MHD_SUCCESS = Success, Error code = Failure
 */

extern mhd_result_t host_buffer_init( /*@null@*/ void* native_arg );

/**
 * @brief Allocates a packet buffer
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * Attempts to allocate a packet buffer of the size requested. It can do this
 * by allocating a pre-existing packet from a pool, using a static buffer,
 * or by dynamically allocating memory. The method of allocation does not
 * concern HOST, however it must match the way the network stack expects packet
 * buffers to be allocated.
 *
 * @param buffer     A pointer which receives the allocated packet buffer handle
 * @param direction : Indicates transmit/receive direction that the packet buffer is
 *                    used for. This may be needed if tx/rx pools are separate.
 * @param size      : The number of bytes to allocate.
 * @param wait      : Whether to wait for a packet buffer to be available
 *
 * @return MHD_SUCCESS = Success, Error code = Failure
 *
 */

extern mhd_result_t host_buffer_get( /*@special@*/ /*@out@*/ host_buffer_t* buffer, mhd_buffer_dir_t direction, unsigned short size, host_bool_t wait ) /*@allocates *buffer@*/  /*@defines **buffer@*/;

/**
 * Releases a packet buffer
 *
 * Implemented in the Host buffer interface, which will be specific to the
 * buffering scheme in use.
 * This function is used by HOST to indicate that it no longer requires
 * a packet buffer. The buffer can then be released back into a pool for
 * reuse, or the dynamically allocated memory can be freed, according to
 * how the packet was allocated.
 * Returns void since HOST cannot do anything about failures
 *
 * @param buffer    : the handle of the packet buffer to be released
 * @param direction : indicates transmit/receive direction that the packet buffer has
 *                    been used for. This might be needed if tx/rx pools are separate.
 *
 */
extern void host_buffer_release( /*@only@*/ host_buffer_t buffer, mhd_buffer_dir_t direction );

/**
 * Retrieves the current pointer of a packet buffer
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * Since packet buffers usually need to be created with space at the
 * front for additional headers, this function allows HOST to get
 * the current 'front' location pointer.
 *
 * @param buffer : The handle of the packet buffer whose pointer is to be retrieved
 *
 * @return The packet buffer's current pointer.
 */
extern /*@exposed@*/ uint8_t* host_buffer_get_current_piece_data_pointer( /*@temp@*/ host_buffer_t buffer );

/**
 * Retrieves the size of a packet buffer
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * Since packet buffers usually need to be created with space at the
 * front for additional headers, the memory block used to contain a packet buffer
 * will often be larger than the current size of the packet buffer data.
 * This function allows HOST to retrieve the current size of a packet buffer's data.
 *
 * @param buffer : The handle of the packet buffer whose size is to be retrieved
 *
 * @return The size of the packet buffer.
 */
extern uint16_t host_buffer_get_current_piece_size( /*@temp@*/ host_buffer_t buffer );

/**
 * Sets the current size of a Host packet
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * This function sets the current length of a HOST packet buffer
 *
 * @param buffer : The packet to be modified
 * @param size   : The new size of the packet buffer
 *
 * @return MHD_SUCCESS = Success, Error code = Failure
 */
extern mhd_result_t host_buffer_set_size( /*@temp@*/ host_buffer_t buffer, unsigned short size );

/**
 * Retrieves the next piece of a set of daisy chained packet buffers
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * Some buffering schemes allow buffers to be daisy chained into linked lists.
 * This allows more flexibility with packet buffers and avoids memory copies.
 * It does however require scatter-gather DMA for the hardware bus.
 * This function retrieves the next buffer in a daisy chain of packet buffers.
 *
 * @param buffer : The handle of the packet buffer whose next buffer is to be retrieved
 *
 * @return The handle of the next buffer, or NULL if there is none.
 */
extern /*@exposed@*/ /*@dependent@*/ /*@null@*/ host_buffer_t host_buffer_get_next_piece( /*@dependent@*/ host_buffer_t buffer );

/**
 * Moves the current pointer of a packet buffer
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * Since packet buffers usually need to be created with space at the
 * front for additional headers, this function allows HOST to move
 * the current 'front' location pointer so that it has space to add headers
 * to transmit packets, and so that the network stack does not see the
 * internal HOST headers on received packets.
 *
 * @param buffer    : A pointer to the handle of the current packet buffer
 *                    for which the current pointer will be moved. On return
 *                    this may contain a pointer to a newly allocated packet
 *                    buffer which has been daisy chained to the front of the
 *                    given one. This would be the case if the given packet buffer
 *                    didn't have enough space at the front.
 * @param add_remove_amount : This is the number of bytes to move the current pointer
 *                            of the packet buffer - a negative value increases the space
 *                            for headers at the front of the packet, a positive value
 *                            decreases the space.
 * @return MHD_SUCCESS = Success, Error code = Failure
 */
extern mhd_result_t host_buffer_add_remove_at_front( host_buffer_t* buffer, int32_t add_remove_amount ); /* Adds or removes buffer parts as needed (and returns new handle) - new bytes must be contiguous with each other, but not necessarily with original bytes */


/**
 * Checks for buffers that have been leaked
 *
 * Implemented in the HOST buffer interface which is specific to the
 * buffering scheme in use.
 * This function must only be used when all buffers are expected to have been
 * released. Function triggers an assertion if any buffers are in use.
 *
 * @return MHD_SUCCESS = Success, Error code = Failure
 */
extern mhd_result_t host_buffer_check_leaked( void );

mhd_result_t host_buffer_add_application_defined_pool( void* pool_in, mhd_buffer_dir_t direction );


/** @} */

#ifdef __cplusplus
} /*extern "C" */
#endif
#endif /* ifndef INCLUDED_MHD_BUFFER_INTERFACE_H_ */
