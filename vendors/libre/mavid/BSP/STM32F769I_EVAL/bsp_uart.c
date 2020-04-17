#include "bsp_uart.h"
        
#define bsp_status HAL_StatusTypeDef        
UART_HandleTypeDef uart_handles[1];       
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
    GPIO_InitTypeDef  GPIO_InitStruct;
    if(huart->Instance==UART4)
    {
        /* USER CODE BEGIN UART4_MspInit 0 */
        
        /* USER CODE END UART4_MspInit 0 */
        /* Peripheral clock enable */
        __HAL_RCC_UART4_CLK_ENABLE();
        
        /**UART4 GPIO Configuration    
        PH13     ------> UART4_TX
        PH14     ------> UART4_RX 
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF8_UART4;
        HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);
        
        /* UART4 interrupt Init */
        HAL_NVIC_SetPriority(UART4_IRQn, 5, 0);
        HAL_NVIC_EnableIRQ(UART4_IRQn);
        /* USER CODE BEGIN UART4_MspInit 1 */
        
        
        /* USER CODE END UART4_MspInit 1 */
    }
    
#ifdef LIBRE_USE_USART2_EXT
    
    if(huart->Instance == USART2)
    {
        // This is the TRANS (HCI) UART	
        //RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;
        
        /* Peripheral clock enable */
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_GPIOD_CLK_ENABLE();
        
        
        /* Select SysClk as source of USART2 clocks */
        //RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
        //RCC_PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_SYSCLK;
        //HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);
        
        /* Enable USARTx clock */
        
        
        /**USART2 GPIO Configuration
        PA2      ------> USART2_TX
        PA3      ------> USART2_RX
        PD3     ------> USART2_CTS
        PD4      ------> USART2_RTS
        */
        
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        
        //PA2 TX  
        
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        //PA3 RX  
        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        
        // PD3 CTS, IN, low to send data 
        GPIO_InitStruct.Pin = GPIO_PIN_3;               
        GPIO_InitStruct.Pull = GPIO_PULLDOWN; 
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
        
        // PD4 RTS ,OUT, low to receive data  
        GPIO_InitStruct.Pin = GPIO_PIN_4;               
        GPIO_InitStruct.Pull = GPIO_PULLUP;  
        
        //GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);               
        // force low all the time
        //HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_RESET);
        
        
        
        //#if ((defined PF_TRANS_IT)&&(PF_TRANS_IT == TRUE))
        HAL_NVIC_SetPriority(USART2_IRQn, 2, 0);                
        HAL_NVIC_EnableIRQ(USART2_IRQn);
        //#endif
        
#if ((defined PF_TRANS_DMA)&&(PF_TRANS_DMA == TRUE))
        __DMA1_CLK_ENABLE();
	// USART2 TX DMA
        /* Configure the hdma_trans_uartTx handle parameters */   
        hdma_trans_uartTx.Init.Channel             = DMA_CHANNEL_4;
        hdma_trans_uartTx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        hdma_trans_uartTx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_trans_uartTx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_trans_uartTx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartTx.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartTx.Init.Mode                = DMA_NORMAL;
        hdma_trans_uartTx.Init.Priority            = DMA_PRIORITY_HIGH;
        hdma_trans_uartTx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
        hdma_trans_uartTx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        hdma_trans_uartTx.Init.MemBurst            = DMA_MBURST_SINGLE;
        hdma_trans_uartTx.Init.PeriphBurst         = DMA_MBURST_SINGLE; 
        hdma_trans_uartTx.Instance                 = DMA1_Stream6;
        
        /* Associate the DMA handle */
        __HAL_LINKDMA(huart, hdmatx, hdma_trans_uartTx);
        
        /* Deinitialize the Stream for new transfer */
        HAL_DMA_DeInit(&hdma_trans_uartTx);
        
        /* Configure the DMA Stream */
        HAL_DMA_Init(&hdma_trans_uartTx);  
        
        /* UART DMA IRQ Channel configuration */
        //HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 2, 0);
        HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 6, 0);
        //HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 8, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn); 
        
        
        /* Configure the hdma_trans_uartRx handle parameters */   
        hdma_trans_uartRx.Init.Channel             = DMA_CHANNEL_4;
        hdma_trans_uartRx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        hdma_trans_uartRx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_trans_uartRx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_trans_uartRx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartRx.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartRx.Init.Mode                = DMA_NORMAL;
        hdma_trans_uartRx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
        hdma_trans_uartRx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
        hdma_trans_uartRx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        hdma_trans_uartRx.Init.MemBurst            = DMA_MBURST_SINGLE;
        hdma_trans_uartRx.Init.PeriphBurst         = DMA_MBURST_SINGLE; 
        hdma_trans_uartRx.Instance                = DMA1_Stream5;
        
        /* Associate the DMA handle */
        __HAL_LINKDMA(huart, hdmarx, hdma_trans_uartRx);
        
        /* Deinitialize the Stream for new transfer */
        HAL_DMA_DeInit(&hdma_trans_uartRx);
        
        /* Configure the DMA Stream */
        HAL_DMA_Init(&hdma_trans_uartRx);  
        
        /* UART DMA IRQ Channel configuration */
        //HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 2, 0);
        
        //HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 6, 0);
        //HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn); 
        
        HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn); 
        
#endif
    }
    
    
#else    
    if(huart->Instance == USART1)
    {
        // This is the TRANS (HCI) UART	
        //RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;
        
        /* Peripheral clock enable */
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        
        /* Select SysClk as source of USART1 clocks */
        //RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
        //RCC_PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_SYSCLK;
        //HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);
        
        /* Enable USARTx clock */
        
        
        /**USART1 GPIO Configuration
        PA12      ------> USART1_RTS
        PA11      ------> USART1_CTS
        PA9     ------> USART1_TX
        PA10      ------> USART1_RX
        */
        
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        
        //PA9 TX  
        GPIO_InitStruct.Pin = GPIO_PIN_9;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        //PA10 RX  
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        // PA11 CTS, IN, high to send data
        GPIO_InitStruct.Pin = GPIO_PIN_11;               
        GPIO_InitStruct.Pull = GPIO_PULLDOWN ;//GPIO_PULLDOWN;       
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        
        // PA12 RTS ,OUT, low to receive  data
        GPIO_InitStruct.Pin = GPIO_PIN_12;                      
        //GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_PULLUP    ;//GPIO_PULLUP; 
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        // force low all the time
        //HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
        
        
        //#if ((defined PF_TRANS_IT)&&(PF_TRANS_IT == TRUE))
        HAL_NVIC_SetPriority(USART1_IRQn, 2, 0);                
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        //#endif
        
#if ((defined PF_TRANS_DMA)&&(PF_TRANS_DMA == TRUE))
        __DMA2_CLK_ENABLE();
        // USART1 TX DMA
        /* Configure the hdma_trans_uartTx handle parameters */   
        hdma_trans_uartTx.Init.Channel             = DMA_CHANNEL_4;
        hdma_trans_uartTx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        hdma_trans_uartTx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_trans_uartTx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_trans_uartTx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartTx.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartTx.Init.Mode                = DMA_NORMAL;
        hdma_trans_uartTx.Init.Priority            = DMA_PRIORITY_HIGH;
        hdma_trans_uartTx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
        hdma_trans_uartTx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        hdma_trans_uartTx.Init.MemBurst            = DMA_MBURST_SINGLE;
        hdma_trans_uartTx.Init.PeriphBurst         = DMA_MBURST_SINGLE; 
        hdma_trans_uartTx.Instance                 = DMA2_Stream7;
        
        /* Associate the DMA handle */
        __HAL_LINKDMA(huart, hdmatx, hdma_trans_uartTx);
        
        /* Deinitialize the Stream for new transfer */
        HAL_DMA_DeInit(&hdma_trans_uartTx);
        
        /* Configure the DMA Stream */
        HAL_DMA_Init(&hdma_trans_uartTx);  
        
        /* UART DMA IRQ Channel configuration */
        //HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 2, 0);
        HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 6, 0);
        //HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 8, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn); 
        
        
        /* Configure the hdma_trans_uartRx handle parameters */   
        hdma_trans_uartRx.Init.Channel             = DMA_CHANNEL_4;
        hdma_trans_uartRx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        hdma_trans_uartRx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_trans_uartRx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_trans_uartRx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartRx.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
        hdma_trans_uartRx.Init.Mode                = DMA_NORMAL;
        hdma_trans_uartRx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
        hdma_trans_uartRx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
        hdma_trans_uartRx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        hdma_trans_uartRx.Init.MemBurst            = DMA_MBURST_SINGLE;
        hdma_trans_uartRx.Init.PeriphBurst         = DMA_MBURST_SINGLE; 
        //hdma_trans_uartRx.Instance                 = DMA2_Stream5;
        hdma_trans_uartRx.Instance                 = DMA2_Stream2;
        
        /* Associate the DMA handle */
        __HAL_LINKDMA(huart, hdmarx, hdma_trans_uartRx);
        
        /* Deinitialize the Stream for new transfer */
        HAL_DMA_DeInit(&hdma_trans_uartRx);
        
        /* Configure the DMA Stream */
        HAL_DMA_Init(&hdma_trans_uartRx);  
        
        /* UART DMA IRQ Channel configuration */
        //HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 2, 0);
        
        //HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 6, 0);
        //HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn); 
        
        HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn); 
        
#endif
    }
    
    
#endif    //#ifdef LIBRE_USE_USART2_EXT
    
    else if (huart->Instance == UART5) 
        
    {
        
        RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit;
        /* Select SysClk as source of UART5 clocks */
        RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_UART5;
        RCC_PeriphClkInit.Uart5ClockSelection = RCC_UART5CLKSOURCE_SYSCLK;
        HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit);
        
        
        /*##-1- Enable peripherals and GPIO Clocks #################################*/
        /* Enable GPIO TX/RX clock */
        
        __GPIOB_CLK_ENABLE();
        
        /* Enable USARTx clock */
        __UART5_CLK_ENABLE();
        
        /*##-2- Configure peripheral GPIO ##########################################*/
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin 	  = GPIO_PIN_9;
        GPIO_InitStruct.Mode	  = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull	  = GPIO_PULLUP;
        GPIO_InitStruct.Speed	  = GPIO_SPEED_FREQ_VERY_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_UART5;
        
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        
        /* UART RX GPIO pin configuration  */
        GPIO_InitStruct.Pin = GPIO_PIN_5;
        GPIO_InitStruct.Alternate = GPIO_AF1_UART5;
        
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        /*##-3- Configure the NVIC for UART ########################################*/
        /* NVIC for USARTx */
        //HAL_NVIC_SetPriority(USARTx_IRQn, 0, 1);
        HAL_NVIC_SetPriority(UART5_IRQn, 15, 0);
        //HAL_NVIC_SetPriority(USARTx_IRQn, 2, 1);
        HAL_NVIC_EnableIRQ(UART5_IRQn);
        
#if ((defined PF_TRACE_DMA)&&(PF_TRACE_DMA == TRUE))
        
        __DMA1_CLK_ENABLE();
        // UART5 TX DMA
        /* Configure the hdma_trans_uartTx handle parameters */   
        hdma_trace_uartTx.Init.Channel             = DMA_CHANNEL_4;
        hdma_trace_uartTx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        hdma_trace_uartTx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_trace_uartTx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_trace_uartTx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_trace_uartTx.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
        hdma_trace_uartTx.Init.Mode                = DMA_NORMAL;
        hdma_trace_uartTx.Init.Priority            = DMA_PRIORITY_HIGH;
        hdma_trace_uartTx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
        hdma_trace_uartTx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        hdma_trace_uartTx.Init.MemBurst            = DMA_MBURST_SINGLE;
        hdma_trace_uartTx.Init.PeriphBurst         = DMA_MBURST_SINGLE; 
        hdma_trace_uartTx.Instance                 = DMA1_Stream7;
        
        /* Associate the DMA handle */
        __HAL_LINKDMA(huart, hdmatx, hdma_trace_uartTx);
        
        /* Deinitialize the Stream for new transfer */
        HAL_DMA_DeInit(&hdma_trace_uartTx);
        
        /* Configure the DMA Stream */
        HAL_DMA_Init(&hdma_trace_uartTx);  
        
        /* UART DMA IRQ Channel configuration */
        HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn); 
        
        /* Configure the hdma_trans_uartRx handle parameters */   
        hdma_trace_uartRx.Init.Channel             = DMA_CHANNEL_4;
        hdma_trace_uartRx.Init.Direction           = DMA_PERIPH_TO_MEMORY;
        hdma_trace_uartRx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_trace_uartRx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_trace_uartRx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_trace_uartRx.Init.MemDataAlignment    = DMA_PDATAALIGN_BYTE;
        hdma_trace_uartRx.Init.Mode                = DMA_NORMAL;
        hdma_trace_uartRx.Init.Priority            = DMA_PRIORITY_VERY_HIGH;
        hdma_trace_uartRx.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;         
        hdma_trace_uartRx.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
        hdma_trace_uartRx.Init.MemBurst            = DMA_MBURST_SINGLE;
        hdma_trace_uartRx.Init.PeriphBurst         = DMA_MBURST_SINGLE; 
        hdma_trace_uartRx.Instance                 = DMA1_Stream0;
        
        /* Associate the DMA handle */
        __HAL_LINKDMA(huart, hdmarx, hdma_trace_uartRx);
        
        /* Deinitialize the Stream for new transfer */
        HAL_DMA_DeInit(&hdma_trace_uartRx);
        
        /* Configure the DMA Stream */
        HAL_DMA_Init(&hdma_trace_uartRx);  
        
        /* UART DMA IRQ Channel configuration */
        HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 2, 0);
        HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn); 
        
        //HAL_NVIC_SetPriority(UART5_IRQn, 5, 0);
        //HAL_NVIC_EnableIRQ(UART5_IRQn);
        
#endif
        
        
    }
    
    
}
int uart_init(struct uart_configuration uartconf)
{
    UART_HandleTypeDef *huart;        
    huart=&uart_handles[uartconf.i];        
            
    huart->Instance 			= uart_instance[uartconf.i];
    huart->Init.BaudRate 	        = uartconf.baudrate ;        
    huart->Init.WordLength 	        = UART_WORDLENGTH_8B;
    huart->Init.StopBits	        = UART_STOPBITS_1;
    huart->Init.Parity                  = UART_PARITY_NONE;
    huart->Init.Mode 	                = UART_MODE_TX_RX;        
    huart->Init.HwFlowCtl               = UART_HWCONTROL_NONE;
    if (HAL_UART_Init(huart) != HAL_OK)
    {        
    }        
        
}        
        
bsp_status uart_send(enum uart_list uart, uint8_t *data, uint16_t length){        
    UART_HandleTypeDef *huart;        
    huart=&uart_handles[uart];        
    return HAL_UART_Transmit(huart, data, length, 0xFFFFFFFF);        
}                
bsp_status uart_receive(enum uart_list uart, uint8_t *data, uint16_t length){        
    UART_HandleTypeDef *huart;        
    huart=&uart_handles[uart];        
    return HAL_UART_Receive(huart, data, length, 0xFFFFFFFF);        
}                
        
        