#pragma once                
        
#include "stm32f7xx_hal.h"
#include "cmsis_os.h"
   
enum uart_list{log_uart=0};        
USART_TypeDef *uart_instance[]={UART5};        
struct uart_configuration{        
    enum uart_list i;        
    uint32_t baudrate;        
    uint32_t flowcontrol;        
    osEvent tx_event;        
    osEvent rx_event;        
};        