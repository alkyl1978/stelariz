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
#include "inc/uartstdio.h"
#include "inc/cmdline.h"
#include "servo.h"
#include "led.h"
#include "dvig.h"
#include "dat_scor.h"
#include "lcd.h"
#include "foto.h"
//****************************************************************************************
#define APP_INPUT_BUF_SIZE               128
//****************************************************************************************
//
//
//****************************************************************************************
volatile unsigned long tick=0;
volatile unsigned long tick_dvig=0;
volatile unsigned long tick_serv=0;
volatile unsigned long serv_0=0;
volatile unsigned char g_cInput[APP_INPUT_BUF_SIZE];
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
//******************************************************************************************************
//
//
//
//
//
//******************************************************************************************************
int main()
{
  unsigned long lCommandStatus;
  ROM_FPUEnable();
  ROM_FPULazyStackingEnable();
  ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  tick=ROM_SysCtlClockGet();
  tick_dvig=ROM_SysCtlClockGet()/20000;
  tick_serv=ROM_SysCtlClockGet()/50;
  serv_0=ROM_SysCtlClockGet()/430;
  servo_init();
  led_init();
  lcd_init();
  Dvig_init();
  foto_init();
  UARTStdioInit(0);
  ROM_IntMasterEnable();

  UARTprintf("Welcome to the Stellaris LM4F120 LaunchPad!\n");
  lcd_goto(0,0);
  lcd_puts("---------------"); 
  lcd_goto(1,0);
  lcd_puts("    *SPEZ*     ");
  lcd_goto(2,0);
  lcd_puts(" *STACK-SPORT* "); 
  lcd_goto(3,0);
  lcd_puts("---------------"); 
  
   while(1)
  {
   while(UARTPeek('\r') == -1)
    {
      UARTprintf("\n");
      UARTprintf(">");
      //
      // millisecond delay.  A SysCtlSleep() here would also be OK.
      //
     // ROM_SysCtlDelay(ROM_SysCtlClockGet() / (1000 / 3));
      //
      // считываем принятые данные
      //
      UARTgets((char *)&g_cInput,sizeof(g_cInput));
      //
      //
      //обрабатываем принятые данные 
      //
      lCommandStatus = CmdLineProcess((char *)&g_cInput);
      if(lCommandStatus == CMDLINE_BAD_CMD)
      {
          UARTprintf("Bad command!\n");
      }
      //
      // мало аргументов
      //
      else if(lCommandStatus == CMDLINE_TOO_MANY_ARGS)
      {
          UARTprintf("Too many arguments for command processor!\n");
      }
    }

  }
  return 0;
}
