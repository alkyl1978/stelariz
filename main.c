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
#include "lcd.h"
#include "foto.h"
#include "mb.h"
#include "wiz610.h"
//****************************************************************************************

//****************************************************************************************
//
//
//****************************************************************************************
volatile unsigned long tick=0;
volatile unsigned long tick_dvig=0;
volatile unsigned long tick_serv=0;

volatile unsigned long serv_X_0=0;
volatile unsigned long serv_Y_0=0;
volatile unsigned long serv_Z_0=0;

volatile unsigned long serv_X_Angle=90;
volatile unsigned long serv_Y_Angle=90;
volatile unsigned long serv_Z_Angle=80;

volatile unsigned long dvig_napr[1];
//****************************************************************************************
//
//
//
//
//
//*******************************************************************************************************
void SysTickTimer_init(void)
{
  //
  ROM_SysTickPeriodSet(ROM_SysCtlClockGet()/100);
  ROM_SysTickEnable();
  ROM_SysTickIntEnable();
}
//******************************************************************************************************
//
//
//
//
//
//******************************************************************************************************
void SysTickIntHandler(void)
{

}

void UARTSend(const unsigned char *pucBuffer, unsigned long ulCount)
{
    //
    // Loop while there are more characters to send.
    //
    while(ulCount--)
    {
        //
        // Write the next character to the UART.
        //
        ROM_UARTCharPutNonBlocking(UART0_BASE, *pucBuffer++);
    }
}
//******************************************************************************************************
//
//
//
//
//
//******************************************************************************************************
int main()
{
  ROM_FPUEnable();
  ROM_FPULazyStackingEnable();
  ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  tick=ROM_SysCtlClockGet();
  tick_dvig=ROM_SysCtlClockGet()/20000;
  tick_serv=ROM_SysCtlClockGet()/50;
  serv_X_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_X_Angle;
  serv_Y_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_Y_Angle;
  serv_Z_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_Z_Angle;
  dvig_napr[0]=0;
  dvig_napr[1]=0;
  servo_init();
  led_init();
  lcd_init();
  Dvig_init();
  foto_init(); 
  lcd_goto(0,0);
  lcd_puts("---------------"); 
  lcd_goto(1,0);
  lcd_puts("    *SPEZ*     ");
  lcd_goto(2,0);
  lcd_puts(" *STACK-SPORT* "); 
  lcd_goto(3,0);
  lcd_puts("---------------"); 
  eMBInit(MB_RTU,0x0B,0,115200,MB_PAR_NONE);
  eMBEnable();
  wiz610_init();
  ROM_IntMasterEnable();
   while(1)
  {
    UARTSend("<QZ>",4);
    eMBPoll();
  }
  return 0;
}
