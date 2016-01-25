#include "driverlib/hw_ints.h"
#include "driverlib/hw_gpio.h"
#include "driverlib/hw_memmap.h"
#include "driverlib/hw_sysctl.h"
#include "driverlib/hw_types.h"
#include "driverlib/hw_timer.h"
#include "../driverlib/gpio.h"
#include "../driverlib/sysctl.h"
#include "../driverlib/interrupt.h"
#include "../driverlib/timer.h"
#include "../driverlib/rom.h"
#include "../driverlib/pin_map.h"
#include "../driverlib/udma.h"

unsigned char ucControlTable[1024] __attribute__ ((aligned(1024)));
static unsigned long g_ulBadISR = 0;


void DMA_init(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UDMA);
	ROM_SysCtlPeripheralSleepEnable(SYSCTL_PERIPH_UDMA);
	ROM_IntEnable(INT_UDMAERR);
	ROM_IntEnable(INT_UDMA);
	ROM_uDMAEnable();
	ROM_uDMAControlBaseSet(ucControlTable);
}

void uDMAIntHandler(void)
{
	unsigned long ulMode;
	    //
	    // Check for the primary control structure to indicate complete.
	    //
	    ulMode = ROM_uDMAChannelModeGet(UDMA_CHANNEL_SW);
	    if(ulMode == UDMA_MODE_STOP)
	    {

	    }
	    else
	    {
	        g_ulBadISR++;
	    }
}

void uDMAErrorHandler(void)
{
  unsigned long ulStatus;
  //
  // Check for uDMA error bit
  //
  ulStatus = ROM_uDMAErrorStatusGet();
    if(ulStatus) ROM_uDMAErrorStatusClear();
}

