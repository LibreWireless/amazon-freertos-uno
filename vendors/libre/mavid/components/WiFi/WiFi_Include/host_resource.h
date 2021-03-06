/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#ifndef INCLUDED_RESOURCE_H_
#define INCLUDED_RESOURCE_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/******************************************************
 *                      Macros
 ******************************************************/

#ifndef MIN
#define MIN( x, y ) ((x) < (y) ? (x) : (y))
#endif /* ifndef MIN */

/* Suppress unused parameter warning */
#ifndef UNUSED_PARAMETER
#define UNUSED_PARAMETER( x ) ( (void)(x) )
#endif

#ifndef RESULT_ENUM
#define RESULT_ENUM( prefix, name, value )  prefix ## name = (value)
#endif /* ifndef RESULT_ENUM */

/* These Enum result values are for Resource errors
 * Values: 4000 - 4999
 */
#define RESOURCE_RESULT_LIST( prefix )  \
    RESULT_ENUM(  prefix, SUCCESS,                         0 ),   /**< Success */                           \
    RESULT_ENUM(  prefix, UNSUPPORTED,                     7 ),   /**< Unsupported function */              \
    RESULT_ENUM(  prefix, OFFSET_TOO_BIG,               4001 ),   /**< Offset past end of resource */       \
    RESULT_ENUM(  prefix, FILE_OPEN_FAIL,               4002 ),   /**< Failed to open resource file */      \
    RESULT_ENUM(  prefix, FILE_SEEK_FAIL,               4003 ),   /**< Failed to seek to requested offset in resource file */ \
    RESULT_ENUM(  prefix, FILE_READ_FAIL,               4004 ),   /**< Failed to read resource file */

#define resource_get_size( resource ) ((resource)->size)

/******************************************************
 *                    Constants
 ******************************************************/

#define RESOURCE_ENUM_OFFSET  ( 1300 )

/******************************************************
 *                   Enumerations
 ******************************************************/

/**
 * Result type for HOST Resource function
 */
typedef enum
{
    RESOURCE_RESULT_LIST( RESOURCE_ )
} resource_result_t;

/******************************************************
 *                 Type Definitions
 ******************************************************/

typedef const void*   resource_data_t;
typedef unsigned long resource_size_t;

/******************************************************
 *                    Structures
 ******************************************************/

/**
 * Memory handle
 */
typedef struct
{
    /*@shared@*/ const char* data;
} memory_resource_handle_t;

/**
 * Filesystem handle
 */
typedef struct
{
    unsigned long offset;
    /*@shared@*/ const char* filename;
} filesystem_resource_handle_t;


typedef enum
{
    RESOURCE_IN_MEMORY,
    RESOURCE_IN_FILESYSTEM,
} resource_location_t;

/**
 * Resource handle structure
 */
typedef struct
{
    resource_location_t location;

    unsigned long size;
    union
    {
        filesystem_resource_handle_t fs;
        memory_resource_handle_t     mem;
    } val;
} resource_hnd_t;

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

/** Read resource using the handle specified
 *
 * @param[in]  resource : handle of the resource to read
 * @param[in]  offset   : offset from the beginning of the resource block
 * @param[in]  maxsize  : size of the buffer
 * @param[out] size     : size of the data successfully read
 * @param[in]  buffer   : pointer to a buffer to contain the read data
 *
 * @return @ref resource_result_t
 */
extern resource_result_t resource_read( const resource_hnd_t* resource, uint32_t offset, uint32_t maxsize, uint32_t* size, void* buffer );

#ifdef __cplusplus
} /*extern "C" */
#endif

#endif /* ifndef INCLUDED_RESOURCE_H_ */
