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
//****************************************************************************************
// ���������� ����������
extern volatile unsigned long tick_dvig;
//****************************************************************************************
//
//
// ��������� ��������� ���������� �������
//
//
//****************************************************************************************
void Dvig_init(void)
{
  // ����������� ��� �������
//*************************************************************************************************************
  ROM_SysCtlPeripheralEnable(PWM0_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(PWM0_TIMER_PERIPH);

  ROM_SysCtlPeripheralEnable(PWM1_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(PWM1_TIMER_PERIPH);
  
  ROM_SysCtlPeripheralEnable(PWM2_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(PWM2_TIMER_PERIPH);

  HWREG(PWM0_TIMER_BASE + TIMER_O_CFG)   = TIMER_CFG_16_BIT;
  HWREG(PWM0_TIMER_BASE + TIMER_O_TAMR)  = 0x0A;
  HWREG(PWM0_TIMER_BASE + TIMER_O_TAILR) = 0xFFFF;
  
  HWREG(PWM1_TIMER_BASE + TIMER_O_CFG)   = TIMER_CFG_16_BIT;
  HWREG(PWM1_TIMER_BASE + TIMER_O_TBMR)  = 0x0A;
  HWREG(PWM1_TIMER_BASE + TIMER_O_TBILR) = 0xFFFF;

  HWREG(PWM2_TIMER_BASE + TIMER_O_CFG)   = TIMER_CFG_16_BIT;
  HWREG(PWM2_TIMER_BASE + TIMER_O_TAMR)  = 0x0A;
  HWREG(PWM2_TIMER_BASE + TIMER_O_TAILR) = 0xFFFF;

  HWREG(PWM0_TIMER_BASE + TIMER_O_CTL)   |= 0x0040;
  HWREG(PWM1_TIMER_BASE + TIMER_O_CTL)   |= 0x4000;
  HWREG(PWM2_TIMER_BASE + TIMER_O_CTL)   |= 0x0040;
  
  ROM_TimerEnable(PWM0_TIMER_BASE, TIMER_A);
  ROM_TimerEnable(PWM1_TIMER_BASE, TIMER_B);
  ROM_TimerEnable(PWM2_TIMER_BASE, TIMER_A);
  
  ROM_GPIOPinConfigure(PWM0_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(PWM0_GPIO_BASE, PWM0_GPIO_PIN);
  ROM_GPIOPadConfigSet(PWM0_GPIO_BASE, PWM0_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);
  
  ROM_GPIOPinConfigure(PWM1_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(PWM1_GPIO_BASE, PWM1_GPIO_PIN);
  ROM_GPIOPadConfigSet(PWM1_GPIO_BASE, PWM1_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                     GPIO_PIN_TYPE_STD);

  ROM_GPIOPinConfigure(PWM2_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(PWM2_GPIO_BASE, PWM2_GPIO_PIN);
  ROM_GPIOPadConfigSet(PWM2_GPIO_BASE, PWM2_GPIO_PIN, GPIO_STRENGTH_8MA_SC,
                       GPIO_PIN_TYPE_STD);

 // ������� ��������� �������� ����
  ROM_TimerPrescaleSet(PWM0_TIMER_BASE, PWM0_TIMER, 0);
  ROM_TimerPrescaleSet(PWM1_TIMER_BASE, PWM1_TIMER, 0);
  ROM_TimerPrescaleSet(PWM2_TIMER_BASE, PWM2_TIMER, 0);

  ROM_TimerPrescaleMatchSet(PWM0_TIMER_BASE, PWM0_TIMER, 0);
  ROM_TimerPrescaleMatchSet(PWM1_TIMER_BASE, PWM1_TIMER, 0);
  ROM_TimerPrescaleMatchSet(PWM2_TIMER_BASE, PWM2_TIMER, 0);

  ROM_TimerMatchSet(PWM0_TIMER_BASE, PWM0_TIMER,0);
  ROM_TimerMatchSet(PWM1_TIMER_BASE, PWM1_TIMER,0);
  ROM_TimerMatchSet(PWM2_TIMER_BASE, PWM2_TIMER,0);

  ROM_TimerLoadSet(PWM0_TIMER_BASE, PWM0_TIMER,tick_dvig);
  ROM_TimerLoadSet(PWM1_TIMER_BASE, PWM1_TIMER,tick_dvig);
  ROM_TimerLoadSet(PWM2_TIMER_BASE, PWM2_TIMER,tick_dvig);
  //************************************************************************************************************
  // ����������� ����������� ����������
  ROM_SysCtlPeripheralEnable(PWM0_NAPR_A_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(PWM0_NAPR_B_GPIO_PERIPH);
  
  ROM_GPIODirModeSet(PWM0_NAPR_A_GPIO_BASE,PWM0_NAPR_A_GPIO_PIN,GPIO_DIR_MODE_OUT);
  ROM_GPIODirModeSet(PWM0_NAPR_B_GPIO_BASE,PWM0_NAPR_B_GPIO_PIN,GPIO_DIR_MODE_OUT);
  
  ROM_GPIOPadConfigSet(PWM0_NAPR_A_GPIO_BASE,PWM0_NAPR_A_GPIO_PIN,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
  ROM_GPIOPadConfigSet(PWM0_NAPR_B_GPIO_BASE,PWM0_NAPR_B_GPIO_PIN,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
  
  ROM_GPIOPinWrite(PWM0_NAPR_A_GPIO_BASE,PWM0_NAPR_A_GPIO_PIN,PWM0_NAPR_A_GPIO_PIN);
  ROM_GPIOPinWrite(PWM0_NAPR_B_GPIO_BASE,PWM0_NAPR_B_GPIO_PIN,0);
  //**********************************************************************************************************
  ROM_SysCtlPeripheralEnable(PWM1_NAPR_A_GPIO_PERIPH);
  ROM_SysCtlPeripheralEnable(PWM1_NAPR_B_GPIO_PERIPH);
  
  ROM_GPIODirModeSet(PWM1_NAPR_A_GPIO_BASE,PWM1_NAPR_A_GPIO_PIN,GPIO_DIR_MODE_OUT);
  ROM_GPIODirModeSet(PWM1_NAPR_B_GPIO_BASE,PWM1_NAPR_B_GPIO_PIN,GPIO_DIR_MODE_OUT);
  
  ROM_GPIOPadConfigSet(PWM1_NAPR_A_GPIO_BASE,PWM1_NAPR_A_GPIO_PIN,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
  ROM_GPIOPadConfigSet(PWM1_NAPR_B_GPIO_BASE,PWM1_NAPR_B_GPIO_PIN,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
  
  ROM_GPIOPinWrite(PWM1_NAPR_A_GPIO_BASE,PWM1_NAPR_A_GPIO_PIN,PWM1_NAPR_A_GPIO_PIN);
  ROM_GPIOPinWrite(PWM1_NAPR_B_GPIO_BASE,PWM1_NAPR_B_GPIO_PIN,0);
}
