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
    }
    else
    {
        // disable tx
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
        ROM_SysCtlPeripheralEnable(MODBUS_UART_PERIPH);
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
          HWREG(MODBUS_UART_BASE+UART_O_IM)= UART_INT_RX;
          EXIT_CRITICAL_SECTION();     
    }
    else
    {
      
    }
    return bInitialized;
}

BOOL xMBPortSerialPutByte( CHAR ucByte )
{
    return TRUE;
}

BOOL xMBPortSerialGetByte( CHAR * pucByte )
{
	if(!(HWREG(MODBUS_UART_BASE + UART_O_FR) & UART_FR_RXFE)) *pucByte = HWREG(MODBUS_UART_BASE + UART_O_DR);
	else return FALSE;
	return TRUE;
}


void prvvMBSerialIRQHandler( void )
{
    unsigned long ulStatus;    
    ulStatus = ROM_UARTIntStatus(MODBUS_UART_BASE, true);
    ROM_UARTIntClear(MODBUS_UART_BASE, ulStatus);
    if(ulStatus&UART_INT_RX)
    {
      while(!(HWREG(MODBUS_UART_BASE + UART_O_FR) & UART_FR_RXFE))
      {
        pxMBFrameCBByteReceived();
      }
    }      
}



void EnterCriticalSection( void )
{

}

void ExitCriticalSection( void )
{

}
