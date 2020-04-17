/* LzmaUtil.h -- Satish Kumar Anbazhagan- Libre Wireless Technologies */

#include "Precomp.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "CpuArch.h"

#include "Alloc.h"
#include "7zFile.h"
#include "7zVersion.h"
#include "LzmaDec.h"
#include "LzmaEnc.h"

#ifdef __cplusplus
extern "C" {
#endif
  
// ==== Enumeration, structures, defines ==== //
  
/* header: 5 bytes of LZMA properties and 8 bytes of uncompressed size */
#define LZMA_HEADER_SIZE      LZMA_PROPS_SIZE + 8

#define IN_BUF_SIZE (1 << 9)
#define OUT_BUF_SIZE (1 << 9)

typedef enum {
  e_DECOMP_CTRL_START = 0,
  e_DECOMP_CTRL_CONFIG,
  e_DECOMP_CTRL_STOP
} e_CtrlMsgId;

typedef enum {
  e_Service_Free = -1,
  e_Wifi_Firmware = 0,
  e_DSPG_Firmware,
  e_BT_Firmware
} e_binaryId;


typedef struct{
  uint16_t dataSize;
  uint8_t data[OUT_BUF_SIZE];
} DecompDataMsg_t;

typedef struct{
  e_binaryId FirmwareId;
  e_CtrlMsgId ctrlId;
  void * payload;
} DecompCtrlMsg_t;

typedef enum {
  e_STATE_DECOMP_INIT = 0,
  e_STATE_DECOMP_CONFIGURED,
  e_STATE_DECOMP_RUNNING,
  e_STATE_DECOMP_STOP  
} e_decompState;

typedef struct {
  e_binaryId FirmwareId;
  Bool DecompressionDone;
} decompressionConfig_t;

typedef struct {
  decompressionConfig_t * pConfig;
  UInt32 NumofBinaries;
  e_decompState state;
  e_binaryId CurrentFWId;
  Byte * pInData;
  UInt32 DecompSize;
  Byte Header[LZMA_HEADER_SIZE];
  CLzmaDec Dstate;
} lzmaObj_t;
  
/******************************************************
 *               Function Declarations
 ******************************************************/
int decompression_init(decompressionConfig_t * pConfig, int numOfId);

int releaseDecompService(e_binaryId FwId);

int claimDecompService(void *pData,e_binaryId FwId);

int ReadDecompData(void * buffer, uint32_t* size_out);
#ifdef __cplusplus
} /*extern "C" */
#endif
