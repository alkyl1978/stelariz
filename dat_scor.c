<<<<<<< HEAD
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

///*****************************************************************************************
//
//
//
//
//
//******************************************************************************************
void DatSkor_init(void)
{
  ROM_SysCtlPeripheralEnable(CCP_A_GPIO_PERIPH); // �������� ������������ ����� 
  ROM_SysCtlPeripheralEnable(CCP_A_TIMER_PERIPH); // �������� ������������ �������
  HWREG(CCP_A_TIMER_BASE+TIMER_O_CFG)=TIMER_CFG_16_BIT; // �������� ��������� ��� �������.
  HWREG(CCP_A_TIMER_BASE+TIMER_O_TAMR)=TIMER_TAMR_TAMR_CAP|TIMER_TAMR_TACMR; // �������� ����� �������
  HWREG(CCP_A_TIMER_BASE+TIMER_O_CTL)=TIMER_CTL_TAEVENT_POS; // �������� �� �������������� ������. 
  HWREG(CCP_A_TIMER_BASE+TIMER_O_TAILR)=80000000; /// ����� �����
  HWREG(CCP_A_TIMER_BASE+TIMER_O_IMR)=TIMER_IMR_CAEIM|TIMER_IMR_CAMIM|TIMER_IMR_TATOIM; // �������� ������ ����������
  //������������� ���� �� ���� ���������
  ROM_GPIOPinConfigure(CCP_A_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(CCP_A_GPIO_BASE,CCP_A_GPIO_PIN);
  ROM_IntEnable(INT_WTIMER3A);
  HWREG(CCP_A_TIMER_BASE+TIMER_O_CTL)|=TIMER_CTL_TAEN; // ��������� ������
}

//*******************************************************************************************************
//
//
// ������������ ������� 3 ������� ��������� �� ������� �������� 0
//
//
//*******************************************************************************************************
void WTimer3AIsr(void)
{
  unsigned long temp;
  temp=ROM_TimerIntStatus(CCP_A_TIMER_BASE,0);   
  ROM_TimerIntClear(CCP_A_TIMER_BASE,temp );
}
//*********************************************************************************************************
//
//
// ������������ ������� 3 ������� ��������� �� ������� �������� 1
//
//
//*********************************************************************************************************
void WTimer3BIsr(void)
{
  unsigned long temp;
  temp=ROM_TimerIntStatus(CCP_B_TIMER_BASE,0);   
  ROM_TimerIntClear(CCP_B_TIMER_BASE,temp );
}
=======
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

///*****************************************************************************************
//
//
//
//
//
//******************************************************************************************
void DatSkor_init(void)
{
  ROM_SysCtlPeripheralEnable(CCP_A_GPIO_PERIPH); // �������� ������������ ����� 
  ROM_SysCtlPeripheralEnable(CCP_A_TIMER_PERIPH); // �������� ������������ �������
  HWREG(CCP_A_TIMER_BASE+TIMER_O_CFG)=TIMER_CFG_16_BIT; // �������� ��������� ��� �������.
  HWREG(CCP_A_TIMER_BASE+TIMER_O_TAMR)=TIMER_TAMR_TAMR_CAP|TIMER_TAMR_TACMR; // �������� ����� �������
  HWREG(CCP_A_TIMER_BASE+TIMER_O_CTL)=TIMER_CTL_TAEVENT_POS; // �������� �� �������������� ������. 
  HWREG(CCP_A_TIMER_BASE+TIMER_O_TAILR)=80000000; /// ����� �����
  HWREG(CCP_A_TIMER_BASE+TIMER_O_IMR)=TIMER_IMR_CAEIM|TIMER_IMR_CAMIM|TIMER_IMR_TATOIM; // �������� ������ ����������
  //������������� ���� �� ���� ���������
  ROM_GPIOPinConfigure(CCP_A_GPIO_PIN_CFG);
  ROM_GPIOPinTypeTimer(CCP_A_GPIO_BASE,CCP_A_GPIO_PIN);
  ROM_IntEnable(INT_WTIMER3A);
  HWREG(CCP_A_TIMER_BASE+TIMER_O_CTL)|=TIMER_CTL_TAEN; // ��������� ������
}

//*******************************************************************************************************
//
//
// ������������ ������� 3 ������� ��������� �� ������� �������� 0
//
//
//*******************************************************************************************************
void WTimer3AIsr(void)
{
  unsigned long temp;
  temp=ROM_TimerIntStatus(CCP_A_TIMER_BASE,0);   
  ROM_TimerIntClear(CCP_A_TIMER_BASE,temp );
}
//*********************************************************************************************************
//
//
// ������������ ������� 3 ������� ��������� �� ������� �������� 1
//
//
//*********************************************************************************************************
void WTimer3BIsr(void)
{
  unsigned long temp;
  temp=ROM_TimerIntStatus(CCP_B_TIMER_BASE,0);   
  ROM_TimerIntClear(CCP_B_TIMER_BASE,temp );
}
>>>>>>> master
