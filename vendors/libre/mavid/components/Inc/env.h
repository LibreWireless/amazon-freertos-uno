/**
  ******************************************************************************
  * @file    /Inc/env.h
  * @author  Mavid Firmware Team
  * @version V1.0
  * @date    27-Oct-2017
  * @brief   This file contains all the functions prototypes for the env.c
  *          file.
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ENV_H
#define __ENV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "semphr.h"        
#include "env_uid.h"

typedef struct {
  uint8_t Name[4];
  uint32_t MaxUID;
  uint32_t EntryStart;
} env_header_t;

typedef struct uid_entry_header {
  struct uid_entry_header * pNext;
  uint16_t valid;
  uint16_t len;
} uid_entry_header_t;

typedef struct {
  uint32_t uid;
  uid_entry_header_t *pEntry;
} uid_ptr_list_t;

typedef enum env_state {
  ENV_UNINITIALIZED,
  ENV_READY,
  ENV_CORRUPT
} env_state_t;

typedef struct {
  uint32_t MaxUID;
  uid_entry_header_t * NexFreeAddr;
  uid_entry_header_t ** pList;
  SemaphoreHandle_t xMutex;
  env_state_t state;
} env_obj_t;

  
int32_t env_init();
int32_t env_reinit();
int32_t env_read(int32_t id, uint8_t * pValue);
int32_t env_write(int32_t id, uint8_t * pValue);
int32_t env_swap();
int32_t choose_env_partition();
  
#ifdef __cplusplus
}
#endif

#endif /* __ENV_H */


/************************ (C) COPYRIGHT Libre Wireless *****END OF FILE****/