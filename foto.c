#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "include/servo.h"
#include "include/led.h"
#include "include/dvig.h"
#include "include/dat_scor.h"
#include "include/foto.h"

unsigned long temp;

void foto_init(void)
{
  //
  ROM_SysCtlPeripheralEnable(CCP_FOTO_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(CCP_FOTO_TIMER_PERIPH);
  HWREG(CCP_FOTO_TIMER_BASE+TIMER_O_CFG)=TIMER_CFG_16_BIT;
  HWREG(CCP_FOTO_TIMER_BASE+TIMER_O_TAMR)=TIMER_TAMR_TAMR_CAP|TIMER_TAMR_TACMR|TIMER_TAMR_TACDIR;
  HWREG(CCP_FOTO_TIMER_BASE+TIMER_O_CTL)=TIMER_CTL_TAEVENT_POS;
  HWREG(CCP_FOTO_TIMER_BASE+TIMER_O_TAILR)=8000000;
  HWREG(CCP_FOTO_TIMER_BASE+TIMER_O_IMR)=TIMER_IMR_CAEIM;

  ROM_GPIOPinConfigure(CCP_FOTO_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(CCP_FOTO_GPIO_BASE,CCP_FOTO_GPIO_PIN);
  ROM_IntEnable(INT_WTIMER5A);
  HWREG(CCP_FOTO_TIMER_BASE+TIMER_O_CTL)|=TIMER_CTL_TAEN;
}

//*******************************************************************************************************
//
//
//
//
//
//*******************************************************************************************************
void WTimer5AIsr(void)
{
 temp=ROM_TimerIntStatus(CCP_FOTO_TIMER_BASE,0);   
 ROM_TimerIntClear(CCP_FOTO_TIMER_BASE,temp );
}
