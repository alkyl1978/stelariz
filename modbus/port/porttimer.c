/*
 * FreeModbus Libary: MSP430 Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id: porttimer.c,v 1.3 2007/06/12 06:42:01 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"
//----------------------  sys includes ----------------------------------------
#include "../../inc/hw_ints.h"
#include "../../inc/hw_gpio.h"
#include "../../inc/hw_memmap.h"
#include "../../inc/hw_sysctl.h"
#include "../../inc/hw_types.h"
#include "../../inc/hw_timer.h"
#include "../../inc/hw_uart.h"
#include "../../driverlib/gpio.h"
#include "../../driverlib/sysctl.h"
#include "../../driverlib/interrupt.h"
#include "../../driverlib/timer.h"
#include "../../driverlib/rom.h"
#include "../../driverlib/pin_map.h"
#include "../../driverlib/uart.h"
/* ----------------------- Modbus includes ----------------------------------*/
#include "../include/mb.h"
#include "../include/mbport.h"

/* ----------------------- Defines ------------------------------------------*/
/* Timer ticks are counted in multiples of 50us. Therefore 20000 ticks are
 * one second.
 */
/* ----------------------- Start implementation -----------------------------*/
BOOL xMBPortTimersInit( USHORT usTim1Timeout50us )
{
    BOOL            bInitialized = FALSE;
    ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    ROM_TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    ROM_TimerLoadSet(TIMER2_BASE, TIMER_A, ROM_SysCtlClockGet()/9000);
    ROM_IntEnable(INT_TIMER2A); 
    ROM_TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);    
    bInitialized = TRUE;
    return bInitialized;
}

void vMBPortTimersEnable( void )
{
	ROM_TimerLoadSet(TIMER2_BASE, TIMER_A, ROM_SysCtlClockGet()/9000);
    ROM_TimerEnable(TIMER2_BASE, TIMER_A);
}

void vMBPortTimersDisable( void )
{
   ROM_TimerDisable(TIMER2_BASE, TIMER_A);
}


void prvvMBTimerIRQHandler( void )
{
    ROM_TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    pxMBPortCBTimerExpired();
}
