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
 * File: $Id: portserial.c,v 1.3 2006/11/19 03:57:49 wolti Exp $
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"
//----------------------  sys includes ----------------------------------------
#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_uart.h"
#include "inc/gpio.h"
#include "inc/sysctl.h"
#include "inc/interrupt.h"
#include "inc/timer.h"
#include "inc/rom.h"
#include "inc/pin_map.h"
#include "inc/uart.h"
/* ----------------------- Static variables ---------------------------------*/
UCHAR           ucGIEWasEnabled = FALSE;
UCHAR           ucCriticalNesting = 0x00;

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    ENTER_CRITICAL_SECTION();
    if( xRxEnable )
    {
        // enable rx
    }
    else
    {
        // disable rx
    }
    if( xTxEnable )
    {
        // enable tx
    }
    else
    {
        // disable tx
    }
    EXIT_CRITICAL_SECTION(  );
}

BOOL
xMBPortSerialInit( UCHAR ucPort, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    BOOL            bInitialized = TRUE; 
    switch ( eParity )
    {
    case MB_PAR_NONE:
        break;
    case MB_PAR_ODD:
        // set party
        break;
    case MB_PAR_EVEN:
        // set party
        break;
    }
    switch ( ucDataBits )
    {
    case 8:
        break;
    case 7:
        break;
    default:
        bInitialized = FALSE;
    }
    if( bInitialized )
    {
        ENTER_CRITICAL_SECTION();
        GPIOPinConfigure(GPIO_PA0_U0RX);
        GPIOPinConfigure(GPIO_PA1_U0TX);
        ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        ROM_UARTConfigSetExpClk(MODBUS_UART_BASE, ROM_SysCtlClockGet(), 115200,
                              (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                               UART_CONFIG_PAR_NONE));
        ROM_IntEnable(INT_UART0);
        ROM_UARTIntEnable(MODBUS_UART_BASE, UART_INT_TX | UART_INT_RX);
        EXIT_CRITICAL_SECTION();     
    }
    else
    {
       GPIOPinConfigure(GPIO_PA0_U0RX);
       GPIOPinConfigure(GPIO_PA1_U0TX);
       ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
       ROM_UARTConfigSetExpClk(MODBUS_UART_BASE, ROM_SysCtlClockGet(), 115200,
                              (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                               UART_CONFIG_PAR_NONE));
        ROM_IntEnable(INT_UART0);
        ROM_UARTIntEnable(MODBUS_UART_BASE, UART_INT_TX | UART_INT_RX);
    }
    return bInitialized;
}

BOOL xMBPortSerialPutByte( CHAR ucByte )
{
    ROM_UARTCharPutNonBlocking(MODBUS_UART_BASE,ucByte);
    return TRUE;
}

BOOL xMBPortSerialGetByte( CHAR * pucByte )
{
    *pucByte = ROM_UARTCharGetNonBlocking(MODBUS_UART_BASE);
    return TRUE;
}


void prvvMBSerialIRQHandler( void )
{
    unsigned long ulStatus;    
    ulStatus = ROM_UARTIntStatus(MODBUS_UART_BASE, true);
    if(ulStatus&UART_INT_TX)
    {
      pxMBFrameCBTransmitterEmpty();
    }
    if(ulStatus&UART_INT_RX)
    {
      while(ROM_UARTCharsAvail(MODBUS_UART_BASE))
      {
        pxMBFrameCBByteReceived();
      }
    }    
    ROM_UARTIntClear(MODBUS_UART_BASE, ulStatus);
}



void EnterCriticalSection( void )
{
    if( ucCriticalNesting == 0 )
    {

    }
    ucCriticalNesting++;
}

void ExitCriticalSection( void )
{
    ucCriticalNesting--;
    if( ucCriticalNesting == 0 )
    {
       
    }
}
