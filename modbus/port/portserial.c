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
#include "../include/mb.h"
#include "../include/mbport.h"
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
/* ----------------------- Static variables ---------------------------------*/
UCHAR           ucGIEWasEnabled = FALSE;
UCHAR           ucCriticalNesting = 0x00;

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    unsigned long enb=0;
    unsigned long flag=0;
    ENTER_CRITICAL_SECTION();
    if( xRxEnable )
    {
        // enable rx
       flag|=UART_CTL_RXE|UART_CTL_UARTEN;
       enb|=UART_INT_RX;
    }
    else
    {
        // disable rx
        flag&=~UART_CTL_RXE;
        enb&=~UART_INT_RX;
    }
    if( xTxEnable )
    {
        // enable tx
        flag|=UART_CTL_TXE|UART_CTL_UARTEN;
        enb|=UART_INT_TX;
    }
    else
    {
        // disable tx
        flag&=~UART_CTL_TXE;
        enb&=~UART_INT_TX;
    }
    HWREG(MODBUS_UART_BASE+UART_O_CTL)=flag;   
    HWREG(MODBUS_UART_BASE+UART_O_IM)=enb;
    EXIT_CRITICAL_SECTION();
}

BOOL
xMBPortSerialInit( UCHAR ucPort, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
    BOOL            bInitialized = TRUE; 
    unsigned long ulDiv,ulUARTClk,ulConfig;
    ulUARTClk=ROM_SysCtlClockGet();
    ulConfig=UART_CONFIG_STOP_ONE;
    switch ( eParity )
    {
    case MB_PAR_NONE:
        ulConfig|=UART_CONFIG_PAR_NONE;
        break;
    case MB_PAR_ODD:
        // set party
      ulConfig|=UART_CONFIG_PAR_ODD;
        break;
    case MB_PAR_EVEN:
        // set party
      ulConfig|=UART_CONFIG_PAR_EVEN;
        break;
    }
    switch ( ucDataBits )
    {
    case 8:
        ulConfig|=UART_CONFIG_WLEN_8;
        break;
    case 7:
        ulConfig|=UART_CONFIG_WLEN_7;
        break;
    default:
        bInitialized = FALSE;
    }
    if( bInitialized )
    {
        ENTER_CRITICAL_SECTION();
        ROM_GPIOPinConfigure(GPIO_PA0_U0RX);
        ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
        ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
        while(HWREG(MODBUS_UART_BASE + UART_O_FR) & UART_FR_BUSY){};
        HWREG(MODBUS_UART_BASE + UART_O_LCRH) &= ~(UART_LCRH_FEN);
        HWREG(MODBUS_UART_BASE + UART_O_CTL) &= ~UART_CTL_UARTEN;
        if((ulBaudRate * 16) > ulUARTClk)
        {
          //
          // Enable high speed mode.
          //
          HWREG(MODBUS_UART_BASE + UART_O_CTL) |= UART_CTL_HSE;
          //
          // Half the supplied baud rate to compensate for enabling high speed
          // mode.  This allows the following code to be common to both cases.
          //
          ulBaudRate /= 2;
         }
        else
          {
            //
            // Disable high speed mode.
            //
            HWREG(MODBUS_UART_BASE + UART_O_CTL) &= ~(UART_CTL_HSE);
          }
          //
          // Compute the fractional baud rate divider.
          //
          ulDiv = (((ulUARTClk * 8) / ulBaudRate) + 1) / 2;
          HWREG(MODBUS_UART_BASE + UART_O_IBRD) = ulDiv / 64;
          HWREG(MODBUS_UART_BASE + UART_O_FBRD) = ulDiv % 64;
          //
          // Clear the flags register.
          //
          HWREG(MODBUS_UART_BASE + UART_O_FR) = 0;
          HWREG(MODBUS_UART_BASE + UART_O_LCRH) = ulConfig;
          HWREG(MODBUS_UART_BASE + UART_O_LCRH) |= UART_LCRH_FEN;
          HWREG(MODBUS_UART_BASE + UART_O_CTL) |= (UART_CTL_UARTEN );
          ROM_IntEnable(INT_UART0);
          HWREG(MODBUS_UART_BASE+UART_O_IM)=UART_INT_TX | UART_INT_RX;
          EXIT_CRITICAL_SECTION();     
    }
    else
    {
      
    }
    return bInitialized;
}

BOOL xMBPortSerialPutByte( CHAR ucByte )
{
    HWREG(MODBUS_UART_BASE + UART_O_DR) = ucByte;
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
    ROM_UARTIntClear(MODBUS_UART_BASE, ulStatus);
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
