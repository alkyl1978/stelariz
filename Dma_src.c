#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/gpio.h"
#include "inc/sysctl.h"
#include "inc/interrupt.h"
#include "inc/timer.h"
#include "inc/rom.h"
#include "inc/pin_map.h"
#include "inc/udma.h"


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
