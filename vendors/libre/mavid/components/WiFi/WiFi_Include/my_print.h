#ifndef _MY_PRINT_H_
#define _MY_PRINT_H_

//#include "BrcmHal.h"

#ifdef __cplusplus
extern "C" {
#endif
extern void vLoggingPrintf( const char * pcFormatString,
                            ... );
//HT**
//#define PRINTF BrcmConsolePrintf
//#define PRINTF printf
#define PRINTF vLoggingPrintf
#ifdef __cplusplus
}
#endif

#endif // #ifndef _MY_PRINT_H_
