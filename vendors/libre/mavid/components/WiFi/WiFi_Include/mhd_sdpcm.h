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
 *  Provides Host with function prototypes for IOCTL commands,
 *  and for communicating with the SDPCM module
 *
 */

#ifndef INCLUDED_MHD_SDPCM_H
#define INCLUDED_MHD_SDPCM_H

#include "mhd_buffer.h"
#include "mhd_constants.h"
#include "mhd_bus_protocol.h"
#include "chip_constants.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *             Constants
 ******************************************************/

/* CDC flag definition taken from bcmcdc.h */
#ifndef CDCF_IOC_SET
#define CDCF_IOC_SET                (0x02)      /** 0=get, 1=set cmd */
#endif /* ifndef CDCF_IOC_SET */

#define SDPCM_LOG_SIZE 30 //512
#define SDPCM_LOG_HEADER_SIZE (0x60)

typedef enum { UNUSED, LOG_TX, LOG_RX } sdpcm_log_direction_t;
typedef enum { IOCTL, DATA, EVENT } sdpcm_log_type_t;

typedef struct SDPCM_log_entry_struct
{
    sdpcm_log_direction_t direction;
    sdpcm_log_type_t      type;
    unsigned long         time;
    unsigned long         length;
    unsigned char         header[SDPCM_LOG_HEADER_SIZE];
}sdpcm_log_entry_t;


typedef enum sdpcm_command_type_enum
{
    SDPCM_GET = 0x00,
    SDPCM_SET = CDCF_IOC_SET
} sdpcm_command_type_t;


/* IOCTL swapping mode for Big Endian host with Little Endian wlan.  Default to off */
#ifdef IL_BIGENDIAN
host_bool_t swap = HOST_FALSE;
#define htod32(i) (swap?bcmswap32(i):i)
#define htod16(i) (swap?bcmswap16(i):i)
#define dtoh32(i) (swap?bcmswap32(i):i)
#define dtoh16(i) (swap?bcmswap16(i):i)
#else /* IL_BIGENDIAN */
#define htod32(i) ((uint32_t)(i))
#define htod16(i) ((uint16_t)(i))
#define dtoh32(i) ((uint32_t)(i))
#define dtoh16(i) ((uint16_t)(i))
#endif /* IL_BIGENDIAN */

/******************************************************
 *             Structures
 ******************************************************/

#define IOCTL_OFFSET ( sizeof(mhd_buffer_header_t) + 12 + 16 )

/******************************************************
 *             Function declarations
 ******************************************************/

extern /*@null@*/ /*@exposed@*/ void* mhd_sdpcm_get_iovar_buffer      ( /*@special@*/ /*@out@*/ host_buffer_t* buffer, uint16_t data_length, const char* name )  /*@allocates *buffer@*/ /*@defines **buffer@*/;
extern /*@null@*/ /*@exposed@*/ void* mhd_sdpcm_get_ioctl_buffer      ( /*@special@*/ /*@out@*/ host_buffer_t* buffer, uint16_t data_length ) /*@allocates *buffer@*/  /*@defines **buffer@*/;
extern mhd_result_t                   mhd_sdpcm_send_ioctl            ( sdpcm_command_type_t type, uint32_t command, host_buffer_t send_buffer_hnd, /*@null@*/ /*@out@*/ host_buffer_t* response_buffer_hnd, mhd_interface_t interface ) /*@releases send_buffer_hnd@*/ ;
extern mhd_result_t                   mhd_sdpcm_send_iovar            ( sdpcm_command_type_t type, /*@only@*/ host_buffer_t send_buffer_hnd, /*@special@*/ /*@out@*/ /*@null@*/ host_buffer_t* response_buffer_hnd, mhd_interface_t interface )  /*@allocates *response_buffer_hnd@*/  /*@defines **response_buffer_hnd@*/;
extern void                           mhd_sdpcm_process_rx_packet     ( /*@only@*/ host_buffer_t buffer );
extern mhd_result_t                   mhd_sdpcm_init                  ( void );
extern void                           mhd_sdpcm_quit                  ( void ) /*@modifies internalState@*/;
extern mhd_result_t                   mhd_sdpcm_get_packet_to_send    ( /*@out@*/ host_buffer_t* buffer );
extern void                           mhd_sdpcm_update_credit         ( uint8_t* data );
extern uint8_t                        mhd_sdpcm_get_available_credits ( void );

extern void print_sdpcm_log_entry(void);
void add_sdpcm_log_entry( sdpcm_log_direction_t dir, sdpcm_log_type_t type, unsigned long length, char* eth_data );


/******************************************************
 *             Global variables
 ******************************************************/

void mhd_set_flow_control( uint32_t on_off );



#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_SDPCM_H */
