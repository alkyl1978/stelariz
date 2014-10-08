#include "inc/hw_types.h"
#include "inc/ustdlib.h"
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
#include "commands.h"
#include "dvig.h"
#include "lcd.h"

//*****************************************************************************
//
// Table of valid command strings, callback functions and help messages.
//
//*****************************************************************************
tCmdLineEntry g_sCmdTable[] =
{
    {"help",     CMD_help,      " : Display list of commands" },
    {"X",        CMD_POZ_X,     " : position  X"},
    {"Y",        CMD_POZ_Y,     " : position  Y"},
    {"Z",        CMD_POZ_Z,     " : position  Y"},
    {"R0",       CMD_POZ_R0,    " : pwm rolik 0"},
    {"R1",       CMD_POZ_R1,    " : pwm rolik 1"},
    {0,          0,                     0 }
};

const int NUM_CMD = sizeof(g_sCmdTable)/sizeof(tCmdLineEntry);

int CMD_POZ_R1 (int argc, char **argv)
{
  unsigned long temp;
  if(argc==2)
  {
    temp=ustrtoul(argv[1], 0, 0);
    lcd_goto(3,0);
    lcd_puts("                ");
    lcd_goto(3,0);
    lcd_puts("R1 PWM value =");
    lcd_puts(argv[1]);
    ROM_TimerMatchSet(PWM1_TIMER_BASE, PWM1_TIMER,500);
  }
  return 0;
}

int CMD_POZ_R0 (int argc, char **argv)
{
  unsigned long temp;
  if(argc==2)
  {
    temp=ustrtoul(argv[1], 0, 0);
    lcd_goto(3,0);
    lcd_puts("                ");
    lcd_goto(3,0);
    lcd_puts("R0 PWM value =");
    lcd_puts(argv[1]);
    ROM_TimerMatchSet(PWM0_TIMER_BASE, PWM0_TIMER,500);
  }
  return 0;
}

// установка позиции
int CMD_POZ_X (int argc, char **argv)
{
  unsigned long temp;
  if(argc==2)
  {
    temp=ustrtoul(argv[1], 0, 0);
    lcd_goto(0,0);
    lcd_puts("                ");
    lcd_goto(0,0);
    lcd_puts("X Angle =");
    lcd_puts(argv[1]);
    temp=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*temp;
    ROM_TimerMatchSet(SERV_X_TIMER_BASE, SERV_X_TIMER, temp);
  }
  return 0;
}

int CMD_POZ_Y (int argc, char **argv)
{
  unsigned long temp;
  if(argc==2)
  {
    lcd_goto(1,0);
    lcd_puts("                ");
    lcd_goto(1,0);
    lcd_puts("Y Angle =");
    lcd_puts(argv[1]);
    temp=ustrtoul(argv[1], 0, 0);
    temp=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*temp;
    ROM_TimerMatchSet(SERV_Y_TIMER_BASE, SERV_Y_TIMER, temp);
  }
  return 0;
}

int CMD_POZ_Z (int argc, char **argv)
{
  unsigned long temp;
  if(argc==2)
  {
    lcd_goto(2,0);
    lcd_puts("                ");
    lcd_goto(2,0);
    lcd_puts("Z Angle =");
    lcd_puts(argv[1]);
    temp=ustrtoul(argv[1], 0, 0);
    temp=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*temp;
    ROM_TimerMatchSet(SERV_Z_TIMER_BASE, SERV_Z_TIMER, temp);
  }
  return 0;
}
//*****************************************************************************
//
// Command: help
//
// Print the help strings for all commands.
//
//*****************************************************************************
int CMD_help (int argc, char **argv)
{
    int index;  
    (void)argc;
    (void)argv;
    lcd_temizle();
    UARTprintf("\n");
    for (index = 0; index < NUM_CMD; index++)
    {
      UARTprintf("%17s %s\n\n",
        g_sCmdTable[index].pcCmd,
        g_sCmdTable[index].pcHelp);
    }
    return (0);
}
