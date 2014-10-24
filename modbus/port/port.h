#ifndef _PORT_H
#define _PORT_H

#include "../../inc/hw_memmap.h"

/* ----------------------- Defines ------------------------------------------*/
#define	INLINE
#define PR_BEGIN_EXTERN_C           extern "C" {
#define	PR_END_EXTERN_C             }

#define ENTER_CRITICAL_SECTION( )   EnterCriticalSection( )
#define EXIT_CRITICAL_SECTION( )    ExitCriticalSection( )
#define assert( expr )


typedef char    BOOL;

typedef unsigned char UCHAR;

typedef char    CHAR;

typedef unsigned short USHORT;
typedef short   SHORT;

typedef unsigned long ULONG;
typedef long    LONG;

#ifndef TRUE
#define TRUE            1
#endif

#ifndef FALSE
#define FALSE           0
#endif

#define MODBUS_UART_BASE UART0_BASE
#define MODBUS_UART_PERIPH SYSCTL_PERIPH_UART0


#endif
