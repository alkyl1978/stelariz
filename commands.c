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

extern volatile unsigned long tick_dvig;
extern volatile unsigned long dvig_napr[1];

extern volatile unsigned long serv_X_0;
extern volatile unsigned long serv_Y_0;
extern volatile unsigned long serv_Z_0;

extern volatile unsigned long serv_X_Angle;
extern volatile unsigned long serv_Y_Angle;
extern volatile unsigned long serv_Z_Angle;
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
    if (temp>100) return 0;
    if (temp==0)
    {
      ROM_GPIOPinWrite(PWM1_NAPR_A_GPIO_BASE,PWM1_NAPR_A_GPIO_PIN,0);
      ROM_GPIOPinWrite(PWM1_NAPR_B_GPIO_BASE,PWM1_NAPR_B_GPIO_PIN,0);
      ROM_TimerMatchSet(PWM1_TIMER_BASE, PWM1_TIMER,tick_dvig-1);
    }
    lcd_goto(3,0);
    lcd_puts("                ");
    lcd_goto(3,0);
    lcd_puts("R1 PWM value =");
    lcd_puts(argv[1]);
    temp=((tick_dvig-1)*temp)/100;
    ROM_TimerMatchSet(PWM1_TIMER_BASE, PWM1_TIMER,temp);
    if(dvig_napr[1]==1)
    {
      ROM_GPIOPinWrite(PWM1_NAPR_A_GPIO_BASE,PWM1_NAPR_A_GPIO_PIN,PWM1_NAPR_A_GPIO_PIN);
      ROM_GPIOPinWrite(PWM1_NAPR_B_GPIO_BASE,PWM1_NAPR_B_GPIO_PIN,0);
    }
    else
    {
      ROM_GPIOPinWrite(PWM1_NAPR_A_GPIO_BASE,PWM1_NAPR_A_GPIO_PIN,0);
      ROM_GPIOPinWrite(PWM1_NAPR_B_GPIO_BASE,PWM1_NAPR_B_GPIO_PIN,PWM1_NAPR_B_GPIO_PIN);
    }
  }
  return 0;
}

int CMD_POZ_R0 (int argc, char **argv)
{
  unsigned long temp;
  if(argc==2)
  {
    temp=ustrtoul(argv[1], 0, 0);
    if (temp>100) return 0;
    if (temp==0)
    {
      ROM_GPIOPinWrite(PWM0_NAPR_A_GPIO_BASE,PWM0_NAPR_A_GPIO_PIN,0);
      ROM_GPIOPinWrite(PWM0_NAPR_B_GPIO_BASE,PWM0_NAPR_B_GPIO_PIN,0);
      ROM_TimerMatchSet(PWM0_TIMER_BASE, PWM0_TIMER,tick_dvig-1);
    }
    lcd_goto(3,0);
    lcd_puts("                ");
    lcd_goto(3,0);
    lcd_puts("R0 PWM value =");
    lcd_puts(argv[1]);
    temp=((tick_dvig-1)*temp)/100;
    ROM_TimerMatchSet(PWM0_TIMER_BASE, PWM0_TIMER,temp);
    if(dvig_napr[0]==1)
    {
      ROM_GPIOPinWrite(PWM0_NAPR_A_GPIO_BASE,PWM0_NAPR_A_GPIO_PIN,PWM0_NAPR_A_GPIO_PIN);
      ROM_GPIOPinWrite(PWM0_NAPR_B_GPIO_BASE,PWM0_NAPR_B_GPIO_PIN,0);
    }
    else
    {
      ROM_GPIOPinWrite(PWM0_NAPR_A_GPIO_BASE,PWM0_NAPR_A_GPIO_PIN,0);
      ROM_GPIOPinWrite(PWM0_NAPR_B_GPIO_BASE,PWM0_NAPR_B_GPIO_PIN,PWM0_NAPR_B_GPIO_PIN);
    }
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
    serv_X_Angle=temp;
    serv_X_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*temp;
    ROM_TimerMatchSet(SERV_X_TIMER_BASE, SERV_X_TIMER,serv_X_0);
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
    serv_Y_Angle=temp;
    serv_Y_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*temp;
    ROM_TimerMatchSet(SERV_Y_TIMER_BASE, SERV_Y_TIMER,serv_Y_0);
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
    serv_Z_Angle=temp;
    serv_Z_0=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/112000)*temp;
    ROM_TimerMatchSet(SERV_Z_TIMER_BASE, SERV_Z_TIMER,serv_Z_0);
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
