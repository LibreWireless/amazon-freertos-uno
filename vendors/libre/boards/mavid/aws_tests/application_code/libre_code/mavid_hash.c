#include "mavid_hash.h"
#include "lib.h"
#include "sha256.h"
#ifdef VERBOSE_PRINT
#define printf     vLoggingPrintf    
#else
#define printf(...)
#endif // VERBOSE_PRINT
    
HASH_HandleTypeDef     HashHandle;
__ALIGN_BEGIN const uint8_t aInput[] __ALIGN_END = "The STM32 F7 series is the result of a perfect symbiosis of the real-time control capabilities of an MCU and the signal processing performance of a DSP, and thus complements the STM32 portfolio with a new class of devices, digital signal controllers (DSC).";
__ALIGN_BEGIN static uint8_t aSHA256Digest[32] __ALIGN_END;
__ALIGN_BEGIN static uint8_t aExpectSHA256Digest[32] __ALIGN_END = {0x24, 0xac, 0xe1, 0x6a, 0x7d, 0x41, 0x59, 0xdc, 
                                                                    0x60, 0x4d, 0x1d, 0x96, 0x6a, 0x3b, 0x27, 0xf4, 
                                                                    0x86, 0x44, 0x60, 0xf8, 0xe5, 0x68, 0x26, 0x25,
                                                                    0x1a, 0x53, 0x9d, 0x08, 0x36, 0x74, 0x9c, 0x06};

__ALIGN_BEGIN static uint8_t aMD5Digest[16] __ALIGN_END;
__ALIGN_BEGIN static uint8_t aExpectMD5Digest[16] __ALIGN_END = {0x1a, 0x96, 0xb7, 0x6f, 0x38, 0x53, 0xa1, 0xd9,
                                                                 0x83, 0x63, 0x93, 0x32, 0x99, 0x34, 0x62, 0x1a};
__ALIGN_BEGIN static uint8_t aSHA1Digest[20] __ALIGN_END;
__ALIGN_BEGIN static uint8_t aExpectSHA1Digest[20] __ALIGN_END = {0x66, 0x76, 0xaa, 0xf9, 0x2f, 0x8a, 0xb4, 0x55,
                                                                  0xea, 0xb6, 0xef, 0xb1, 0x2e, 0x53, 0x4a, 0x9f,
                                                                  0x5b, 0x3d, 0xb0, 0x3e};

/**
  * @brief  Initializes the HASH MSP.
  *        This function configures the hardware resources used in this example:
  *           - HASH's clock enable
  *           - DMA's clocks enable
  * @param  hhash: HASH handle pointer
  * @retval None
  */
void HAL_HASH_MspInit(HASH_HandleTypeDef *hhash)
{
  
    /* Enable HASH clock */
  __HAL_RCC_HASH_CLK_ENABLE();
  
#if 0
   static DMA_HandleTypeDef  hdma_hash;

  /* Enable HASH clock */
  __HAL_RCC_HASH_CLK_ENABLE();

  /* Enable DMA clocks */
  __HAL_RCC_DMA2_CLK_ENABLE();

  /***************** Configure common DMA In parameters ***********************/
  hdma_hash.Init.Channel             = DMA_CHANNEL_2;
  hdma_hash.Init.Direction           = DMA_MEMORY_TO_PERIPH;
  hdma_hash.Init.PeriphInc           = DMA_PINC_DISABLE;
  hdma_hash.Init.MemInc              = DMA_MINC_ENABLE;
  hdma_hash.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
  hdma_hash.Init.MemDataAlignment    = DMA_MDATAALIGN_WORD;
  hdma_hash.Init.Mode                = DMA_NORMAL;
  hdma_hash.Init.Priority            = DMA_PRIORITY_HIGH;
  hdma_hash.Init.FIFOMode            = DMA_FIFOMODE_ENABLE;
  hdma_hash.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_HALFFULL;
  hdma_hash.Init.MemBurst            = DMA_MBURST_SINGLE;
  hdma_hash.Init.PeriphBurst         = DMA_PBURST_SINGLE;
  hdma_hash.Instance = DMA2_Stream7;

  /* Associate the DMA handle */
  __HAL_LINKDMA(hhash, hdmain, hdma_hash);

  /* Deinitialize the Stream for new transfer */
  HAL_DMA_DeInit(hhash->hdmain);

  /* Configure the DMA Stream */
  HAL_DMA_Init(hhash->hdmain);

  /* NVIC configuration for DMA Input data interrupt */
  HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0x0F, 0x0f);
  HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
#endif
}

/**
  * @brief  DeInitializes the HASH MSP.
  * @param  None  
  * @retval None
  */
void HAL_HASH_MspDeInit(HASH_HandleTypeDef *hhash)
{
  /* Force the HASH Periheral Clock Reset */  
  __HAL_RCC_HASH_FORCE_RESET(); 
  
  /* Release the HASH Periheral Clock Reset */  
  __HAL_RCC_HASH_RELEASE_RESET();
}

void init_Hash(void)
{
  HAL_HASH_DeInit(&HashHandle);
  HashHandle.Init.DataType = HASH_DATATYPE_8B;

  if (HAL_HASH_Init(&HashHandle) != HAL_OK)
  {
    fatal("Hash Init failed");
  }
}


int get_SHA256(uint8_t* pInBuf, uint8_t* pOutBuff, uint32_t len)
{
  int retval = 0;
  init_Hash();

  if ((NULL != pInBuf) && (0 != len))
  {

    /* Start HASH computation using DMA transfer */
    if (HAL_HASHEx_SHA256_Start(&HashHandle, (uint8_t*)pInBuf, len, pOutBuff, 0xFF) != HAL_OK)
    {
      fatal("Error in Hash computation");
    }

#if 0
      /* Get the computed digest value */
    if (HAL_HASHEx_SHA256_Finish(&HashHandle, pOutBuff, 0xFF) != HAL_OK)
    {
      fatal("Error in Hash computation finish");
    }
#endif
  }
  else
  {
    retval = -1;
  }

  return retval;
}

int get_SHA224(uint8_t* pInBuf, uint8_t* pOutBuff, uint32_t len)
{
  int retval = 0;
  init_Hash();
  if ((NULL != pInBuf) && (0 != len))
  {

    /* Start HASH computation using DMA transfer */
    if (HAL_HASHEx_SHA224_Start(&HashHandle, (uint8_t*)pInBuf, len, pOutBuff, 0xFF) != HAL_OK)
    {
      fatal("Error in Hash computation");
    }

#if 0
      /* Get the computed digest value */
    if (HAL_HASHEx_SHA224_Finish(&HashHandle, pOutBuff, 0xFF) != HAL_OK)
    {
      fatal("Error in Hash computation finish");
    }
#endif
  }
  else
  {
    retval = -1;
  }

  return retval;
}

int get_SHA1(uint8_t* pInBuf, uint8_t* pOutBuff, uint32_t size)
{
  int retval = 0;
  init_Hash();
  printf("get_SHA1");
  if ((NULL != pInBuf) && (0 != size))
  {

    /* Start HASH computation using DMA transfer */
    if (HAL_HASH_SHA1_Start(&HashHandle, (uint8_t*)pInBuf, size, pOutBuff, 0xFF) != HAL_OK)        
    {
      fatal("Error in Hash computation");
    }
#if 0
      /* Get the computed digest value */
    if (HAL_HASH_SHA1_Finish(&HashHandle, pOutBuff, 0xFF) != HAL_OK)
    {
      fatal("Error in Hash computation finish");
    }
#endif

  }
  else
  {
    retval = -1;
  }

  return retval;
}

int get_MD5(uint8_t* data, uint8_t* aMD5Digest, uint32_t len)
{
  int retval = 0;
  init_Hash();
  printf("get_MD5");
  if ((NULL != data))
  {
    if (HAL_HASH_MD5_Start(&HashHandle, (uint8_t *)data, len, aMD5Digest, 0xFF) != HAL_OK)
    {
      fatal("Error in Hash computation");
    }
  }
  else
  {
    retval = -1;
  }
  
  return retval;
}

int get_MD5_DMA(uint8_t* data, uint8_t* aMD5Digest,  uint32_t len)
{
  int retval = 0;
  init_Hash();
  printf("get_MD5_DMA");
  if ((NULL != data) && (0 != len))
  {
    /* Start HASH computation using DMA transfer */
    if (HAL_HASH_MD5_Start_DMA(&HashHandle, (uint8_t *)data, len) != HAL_OK)
    {
      fatal("Error in Hash computation");
    }

    /* Get the computed digest value */
    if (HAL_HASH_MD5_Finish(&HashHandle, aMD5Digest, 0xFF) != HAL_OK)
    {
      fatal("Error in Hash computation");
    }
  }
  else
  {
    retval = -1;
  }
  
  return retval;
}

void unitTest_sha256(void)
{
  init_Hash();
  /* Start HASH computation using DMA transfer */
  /*if (HAL_HASHEx_SHA256_Start_DMA(&HashHandle, (uint8_t*)aInput, strlen((char const*)aInput)) != HAL_OK)
  {
    printf("Start SHA256 failed\n");
  }*/

    /* Get the computed digest value */
  /*if (HAL_HASHEx_SHA256_Finish(&HashHandle, aSHA256Digest, 0xFF) != HAL_OK)
  {
    printf("Finish SHA256 failed\n");
  }*/
  
  get_SHA256((uint8_t*)aInput, aSHA256Digest, strlen(aInput));
  

  if(memcmp(aSHA256Digest, aExpectSHA256Digest, sizeof(aExpectSHA256Digest)/sizeof(aExpectSHA256Digest[0])) != 0)
  {
    printf("Hash SHA256 do not matches\n");
  }
  else
  {
    printf("Hash SHA256 matches\n");
  }
  
  init_Hash();
  get_SHA1((uint8_t*)aInput, aSHA1Digest, strlen(aInput));
  if(memcmp(aSHA1Digest, aExpectSHA1Digest, sizeof(aExpectSHA1Digest)/sizeof(aExpectSHA1Digest[0])) != 0)
  {
    printf("Hash SHA1 do not matches\n");
  }
  else
  {
    printf("Hash SHA1 matches\n");
  }
    
  init_Hash();
  get_MD5_DMA((uint8_t*)aInput, aMD5Digest, strlen(aInput));
  
  if (memcmp(aMD5Digest, aExpectMD5Digest, sizeof(aExpectMD5Digest) / sizeof(aExpectMD5Digest[0])) != 0)
  {
    printf("Hash MD5 do not matches\n");
  }
  else
  {
    printf("Hash MD5 matches\n");
  }

}
