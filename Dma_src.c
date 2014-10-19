#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "../driverlib/gpio.h"
#include "../driverlib/sysctl.h"
#include "../driverlib/interrupt.h"
#include "../driverlib/timer.h"
#include "../driverlib/rom.h"
#include "../driverlib/pin_map.h"
#include "../driverlib/udma.h"


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

