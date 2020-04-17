#ifndef PF_CONFIG_H
#define PF_CONFIG_H

//#include "data_types.h"


#ifdef LIBRE_PORT

//#define LIBRE_USE_USART2_EXT
#define TRUE 1        
#define FALSE 0        

#ifndef PF_TRANS_DMA
#define PF_TRANS_DMA    TRUE
#endif

#ifndef PF_TRANS_IT
#define PF_TRANS_IT     FALSE
#endif

//HT** use DMA for trace port

#ifndef PF_TRACE_DMA
#define PF_TRACE_DMA    FALSE
#endif

#ifndef PF_TRACE_IT
#define PF_TRACE_IT     TRUE
#endif


#else

#ifndef PF_TRANS_DMA
#define PF_TRANS_DMA    TRUE
#endif

#ifndef PF_TRANS_IT
#define PF_TRANS_IT     FALSE
#endif

#endif

#if(PF_TRANS_DMA == TRUE && PF_TRANS_IT == TRUE)
#error "PF_TRANS_DMA and PF_TRANS_IT should only one mode!!!"
#endif

#if(PF_TRACE_DMA == TRUE && PF_TRACE_IT == TRUE)
#error "PF_TRACE_DMA and PF_TRACE_IT should only one mode!!!"
#endif


#endif

