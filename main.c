#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_uart.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "include/servo.h"
#include "include/led.h"
#include "include/dvig.h"
#include "include/dat_scor.h"
#include "include/lcd.h"
#include "include/foto.h"
#include "modbus/include/mb.h"
#include "include/wiz610.h"
#include "include/Dma_src.h"
//****************************************************************************************
unsigned char buf_rab[128];
unsigned long Sys_tick=0;
unsigned long Wiz610_cmd_get=false;
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
	unsigned char i;
	Sys_tick++;
	if(!Wiz610_cmd_get)
	{
		i=false;
		i=Wiz610_get_buf(buf_rab);
		if(i!=false)
		{
			Wiz610_cmd_get=i;
		}
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
  ROM_SysCtlPeripheralClockGating(true);
  ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
  DMA_init();
  tick=ROM_SysCtlClockGet();
  tick_dvig=ROM_SysCtlClockGet()/20000;
  tick_serv=ROM_SysCtlClockGet()/50;
  serv_X_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_X_Angle;
  serv_Y_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_Y_Angle;
  serv_Z_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*serv_Z_Angle;
  dvig_napr[0]=0;
  dvig_napr[1]=0;
  SysTickTimer_init();
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
   ROM_IntMasterEnable();
  wiz610_init();
  WIZ610Transfer();
  // RESET WI-FI
  Wiz610_put_buf("<WR>",4);
  Sys_tick=0;
  while(Sys_tick>10000 && Wiz610_cmd_get!=0);
  Sys_tick=0;
  lcd_temizle();
  Wiz610_cmd_get=false;
  lcd_temizle();
  lcd_goto(0,0);
  lcd_puts("WI-FI REBOOT");
  while(!Wiz610_cmd_get)
  {
	  if(Sys_tick>10000)
	  {
		  Wiz610_put_buf("<RF>",4);
		  Sys_tick=0;
	  }
  }
  lcd_temizle();
  lcd_goto(0,0);
  lcd_puts("WI-FI RUN");
  lcd_goto(1,0);
  Wiz610_cmd_get=false;
  Wiz610_put_buf("<RF>",4);
  while(!Wiz610_cmd_get);
  lcd_puts(buf_rab);
   while(1)
  {

  }
  return 0;
}
