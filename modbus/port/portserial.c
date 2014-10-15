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
#include "inc/gpio.h"
#include "inc/sysctl.h"
#include "inc/interrupt.h"
#include "inc/timer.h"
#include "inc/rom.h"
#include "inc/pin_map.h"
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
        ENTER_CRITICAL_SECTION(  );
        /* Reset USART */
       
        /* Initialize all UART registers */
        
        /* SSELx = 11 = SMCLK. Use only if PLL is synchronized ! */
       
        /* Configure USART0 Baudrate Registers. */
       
        /* Enable UART */
        
        /* Clear reset flag. */
        

        /* USART0 TXD/RXD */
        

        EXIT_CRITICAL_SECTION(  );

      
    }
    return bInitialized;
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    //TXBUF0 = ucByte;
    return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    //*pucByte = RXBUF0;
    return TRUE;
}


void prvvMBSerialIRQHandler( void )
{
    pxMBFrameCBByteReceived(  );
    pxMBFrameCBTransmitterEmpty(  );
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
