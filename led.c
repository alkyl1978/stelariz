#include "driverlib/hw_ints.h"
#include "driverlib/hw_gpio.h"
#include "driverlib/hw_memmap.h"
#include "driverlib/hw_sysctl.h"
#include "driverlib/hw_types.h"
#include "driverlib/hw_timer.h"
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

//*******************************************************************************************************
//
//
//
//
//
//*******************************************************************************************************
void led_init(void)
{
  //
  ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
  
  //
  ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_BLU|LED_RED|LED_GREN);
  
  //
  ROM_SysCtlPeripheralEnable(RED_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(RED_TIMER_PERIPH);

  ROM_SysCtlPeripheralEnable(GREEN_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(GREEN_TIMER_PERIPH);

  ROM_SysCtlPeripheralEnable(BLUE_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(BLUE_TIMER_PERIPH);

  HWREG(GREEN_TIMER_BASE + TIMER_O_CFG)   = 0x04;
  HWREG(GREEN_TIMER_BASE + TIMER_O_TAMR)  = 0x0A;
  HWREG(GREEN_TIMER_BASE + TIMER_O_TAILR) = 0xFFFF;

  HWREG(BLUE_TIMER_BASE + TIMER_O_CFG)   = 0x04;
  HWREG(BLUE_TIMER_BASE + TIMER_O_TBMR)  = 0x0A;
  HWREG(BLUE_TIMER_BASE + TIMER_O_TBILR) = 0xFFFF;

  HWREG(RED_TIMER_BASE + TIMER_O_CFG)   = 0x04;
  HWREG(RED_TIMER_BASE + TIMER_O_TBMR)  = 0x0A;
  HWREG(RED_TIMER_BASE + TIMER_O_TBILR) = 0xFFFF;
   
  HWREG(RED_TIMER_BASE + TIMER_O_CTL)   |= 0x4000;
  HWREG(GREEN_TIMER_BASE + TIMER_O_CTL)   |= 0x4000;
  HWREG(BLUE_TIMER_BASE + TIMER_O_CTL)   |= 0x40;

  
  ROM_TimerEnable(RED_TIMER_BASE, TIMER_BOTH);
  ROM_TimerEnable(GREEN_TIMER_BASE, TIMER_BOTH);
  ROM_TimerEnable(BLUE_TIMER_BASE, TIMER_BOTH);

  ROM_GPIOPinConfigure(GREEN_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(GREEN_GPIO_BASE, GREEN_GPIO_PIN);
  ROM_GPIOPadConfigSet(GREEN_GPIO_BASE, GREEN_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);

  ROM_GPIOPinConfigure(BLUE_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(BLUE_GPIO_BASE, BLUE_GPIO_PIN);
  ROM_GPIOPadConfigSet(BLUE_GPIO_BASE, BLUE_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);

  ROM_GPIOPinConfigure(RED_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(RED_GPIO_BASE, RED_GPIO_PIN);
  ROM_GPIOPadConfigSet(RED_GPIO_BASE, RED_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);
//*************************************************************************************************************
// ������� ��������� �������� ����
  ROM_TimerMatchSet(RED_TIMER_BASE, RED_TIMER, 0xfff0);
  ROM_TimerMatchSet(GREEN_TIMER_BASE, GREEN_TIMER, 0xfff0);
  ROM_TimerMatchSet(BLUE_TIMER_BASE, BLUE_TIMER, 0xfff0);
}
