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
#include "servo.h"
#include "led.h"
#include "dvig.h"
#include "dat_scor.h"
//********************************************************************************************************
//
//********************************************************************************************************
extern volatile unsigned long tick_serv;
//********************************************************************************************************
//
//
// ��������� ��������� ����
//
//
//********************************************************************************************************
void servo_init(void)
{
//******************************************************************************************************
//
//******************************************************************************************************
  ROM_SysCtlPeripheralEnable(SERV_X_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(SERV_X_TIMER_PERIPH);

  ROM_SysCtlPeripheralEnable(SERV_Y_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(SERV_Y_TIMER_PERIPH);

  ROM_SysCtlPeripheralEnable(SERV_Z_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(SERV_Z_TIMER_PERIPH);

  //
  // Configure each timer for output mode
  //
  HWREG(SERV_X_TIMER_BASE + TIMER_O_CFG)   = 0x04;
  HWREG(SERV_X_TIMER_BASE + TIMER_O_TAMR)  = 0x0A;
  HWREG(SERV_X_TIMER_BASE + TIMER_O_TAILR) = tick_serv;

  HWREG(SERV_Y_TIMER_BASE + TIMER_O_CFG)   = 0x04;
  HWREG(SERV_Y_TIMER_BASE + TIMER_O_TBMR)  = 0x0A;
  HWREG(SERV_Y_TIMER_BASE + TIMER_O_TBILR) = tick_serv;

  HWREG(SERV_Z_TIMER_BASE + TIMER_O_CFG)   = 0x04;
  HWREG(SERV_Z_TIMER_BASE + TIMER_O_TAMR)  = 0x0A;
  HWREG(SERV_Z_TIMER_BASE + TIMER_O_TAILR) = tick_serv;
    
    //
    // Invert the output signals.
    //
  HWREG(SERV_X_TIMER_BASE + TIMER_O_CTL)   |= 0x40;
  HWREG(SERV_Y_TIMER_BASE + TIMER_O_CTL)   |= 0x4000;
  HWREG(SERV_Z_TIMER_BASE + TIMER_O_CTL)   |= 0x40;
  
  ROM_TimerEnable(SERV_X_TIMER_BASE, TIMER_A);
  ROM_TimerEnable(SERV_Y_TIMER_BASE, TIMER_B);
  ROM_TimerEnable(SERV_Z_TIMER_BASE, TIMER_A);

  ROM_GPIOPinConfigure(SERV_X_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(SERV_X_GPIO_BASE, SERV_X_GPIO_PIN);
  ROM_GPIOPadConfigSet(SERV_X_GPIO_BASE, SERV_X_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);

  ROM_GPIOPinConfigure(SERV_Y_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(SERV_Y_GPIO_BASE, SERV_Y_GPIO_PIN);
  ROM_GPIOPadConfigSet(SERV_Y_GPIO_BASE, SERV_Y_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);

  ROM_GPIOPinConfigure(SERV_Z_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(SERV_Z_GPIO_BASE, SERV_Z_GPIO_PIN);
  ROM_GPIOPadConfigSet(SERV_Z_GPIO_BASE, SERV_Z_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);
//
  ROM_TimerMatchSet(SERV_X_TIMER_BASE, SERV_X_TIMER, serv_0);
  ROM_TimerMatchSet(SERV_Y_TIMER_BASE, SERV_Y_TIMER, serv_0);
  ROM_TimerMatchSet(SERV_Z_TIMER_BASE, SERV_Z_TIMER, serv_0);
}
