/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

#ifndef INCLUDED_MHD_BUS_PROTOCOL_INTERFACE_H_
#define INCLUDED_MHD_BUS_PROTOCOL_INTERFACE_H_

#include "mhd_constants.h"
#include "mhd_buffer.h"
#include "mhd_bus_protocol.h"

#ifdef __cplusplus
extern "C"
{
#endif

/******************************************************
 *             Constants
 ******************************************************/

typedef enum
{
    BUS_FUNCTION       = 0,
    BACKPLANE_FUNCTION = 1,
    WLAN_FUNCTION      = 2
} mhd_bus_function_t;

#define BUS_FUNCTION_MASK (0x3)  /* Update this if adding functions */

/******************************************************
 *             Structures
 ******************************************************/

#pragma pack(1)

typedef struct
{
#ifdef MHD_BUS_HAS_HEADER
                 mhd_bus_header_t  bus_header;
#endif /* ifdef MHD_BUS_HAS_HEADER */
                 uint32_t data[1];
} mhd_transfer_bytes_packet_t;

#pragma pack()

/******************************************************
 *             Function declarations
 ******************************************************/

/* Initialisation functions */
extern mhd_result_t mhd_bus_init                       ( void );
extern mhd_result_t mhd_bus_deinit                     ( void );
#ifdef MHD_FAST_BOOT_SUPPORT
extern mhd_result_t mhd_bus_resume                  ( void );
#endif

/* Device register access functions */
extern mhd_result_t mhd_bus_write_backplane_value      ( uint32_t address, uint8_t register_length, uint32_t value );
extern mhd_result_t mhd_bus_read_backplane_value       ( uint32_t address, uint8_t register_length, /*@out@*/ uint8_t* value );
extern mhd_result_t mhd_bus_write_register_value       ( mhd_bus_function_t function, uint32_t address, uint8_t value_length, uint32_t value );
extern mhd_result_t mhd_bus_read_register_value        ( mhd_bus_function_t function, uint32_t address, uint8_t value_length, /*@out@*/ uint8_t* value );

/* Device data transfer functions */
extern mhd_result_t mhd_bus_send_buffer                ( host_buffer_t buffer );
extern mhd_result_t mhd_bus_transfer_bytes             ( mhd_bus_transfer_direction_t direction, mhd_bus_function_t function, uint32_t address, uint16_t size, /*@in@*/ /*@out@*/ mhd_transfer_bytes_packet_t* data );

/* Frame transfer function */
extern mhd_result_t mhd_bus_read_frame( /*@out@*/  host_buffer_t* buffer );

/* Bus energy saving functions */
extern mhd_result_t mhd_bus_poke_wlan                  ( void );
extern mhd_result_t mhd_bus_set_flow_control           ( uint8_t value );
extern host_bool_t mhd_bus_is_flow_controlled         ( void );

extern uint32_t     mhd_bus_packet_available_to_read   ( void );
//HT** Clear SDIO interrupt
extern uint32_t mhd_OOB_SDIO_Status_Pending_Read_And_CLear(void);
void  mhd_OOB_SDIO_Status_Pending_CLear(void);

extern mhd_result_t mhd_bus_ack_interrupt              ( uint32_t intstatus );
extern mhd_result_t mhd_bus_write_wifi_firmware_image  ( void );
extern mhd_result_t mhd_bus_write_wifi_nvram_image     ( void );
extern void         mhd_bus_init_backplane_window      ( void );
extern mhd_result_t mhd_bus_set_backplane_window       ( uint32_t addr );

extern mhd_result_t mhd_bus_specific_wakeup( void );
extern mhd_result_t mhd_bus_specific_sleep( void );

#ifdef MFG_TEST_ALTERNATE_WLAN_DOWNLOAD
extern mhd_result_t external_write_wifi_firmware_and_nvram_image  ( void );
#endif /* ifdef MFG_TEST_ALTERNATE_WLAN_DOWNLOAD */

/******************************************************
 *             Global variables
 ******************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_BUS_PROTOCOL_INTERFACE_H_ */
