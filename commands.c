//*****************************************************************************
//
// rgb_commands.c - Command line functionality implementation
//
// Copyright (c) 2012 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 9453 of the EK-LM4F120XL Firmware Package.
//
//*****************************************************************************
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
    {0,          0,                     0 }
};

const int NUM_CMD = sizeof(g_sCmdTable)/sizeof(tCmdLineEntry);

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
    temp=ROM_SysCtlClockGet()/1400+(ROM_SysCtlClockGet()/11200000)*temp;
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
