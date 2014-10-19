#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "include/wiz610.h"

const unsigned char str[]="<QZ>";
volatile unsigned long wiz_r=WIZ_START;
volatile unsigned char buf_pr[32];
volatile unsigned char *yk_buf;

void wiz610_init(void)
{
  ROM_SysCtlPeripheralEnable(WIZ610_GPIO_PERIPH);
  ROM_GPIODirModeSet(WIZ610_GPIO_BASE,WIZ610_GPIO_PIN_CMD_ENABLE ,GPIO_DIR_MODE_OUT);
  ROM_GPIOPadConfigSet(WIZ610_GPIO_BASE,WIZ610_GPIO_PIN_CMD_ENABLE,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
  ROM_GPIOPinWrite(WIZ610_GPIO_BASE,WIZ610_GPIO_PIN_CMD_ENABLE,WIZ610_GPIO_PIN_CMD_ENABLE);
  // uart setup 
   ROM_SysCtlPeripheralEnable(WIZ610_UART_PERIPH);
   ROM_GPIOPinConfigure(GPIO_PB0_U1RX);
   ROM_GPIOPinConfigure(GPIO_PB1_U1TX);
   ROM_GPIOPinTypeUART(WIZ610_GPIO_BASE, WIZ610_GPIO_PIN_RX | WIZ610_GPIO_PIN_TX);
   ROM_UARTConfigSetExpClk(WIZ610_UART_BASE, ROM_SysCtlClockGet(), 38400,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
   ROM_GPIOPinWrite(WIZ610_GPIO_BASE,WIZ610_GPIO_PIN_CMD_ENABLE,0); 
   ROM_UARTEnable(WIZ610_GPIO_BASE);
   ROM_IntEnable(INT_UART1);
   ROM_UARTEnable(WIZ610_UART_BASE);
   ROM_UARTIntEnable(WIZ610_UART_BASE, UART_INT_RX | UART_INT_TX);
}

void wiz610_uart_isr(void)
{
  unsigned long ulStatus;
  unsigned char data;

    //
    // Get the interrrupt status.
    //
    ulStatus = ROM_UARTIntStatus(WIZ610_UART_BASE, true);
    //
    // Clear the asserted interrupts.
    //
    ROM_UARTIntClear(WIZ610_UART_BASE, ulStatus);
    if (ulStatus==UART_INT_RX)
	{
    	while(ROM_UARTCharsAvail(WIZ610_UART_BASE))
    	{
    		data=ROM_UARTCharGetNonBlocking(WIZ610_UART_BASE);
    		switch (wiz_r)
			{
    		case WIZ_START:
    		{
    			if (data==wiz_char_start)
    			{
    				yk_buf=&buf_pr[0];
    				wiz_r=WIZ_RESV;
    			}
    			break;
    		}
    		case WIZ_RESV:
    		{
    		    if(data==wiz_char_stop)
    		    {
    		    	wiz_r=WIZ_STOP;
    		    }
    		    else *yk_buf++=data;
    			break;
    		}
			}
			}
    	}
	}

void wiz_start(void)
{
	wiz_r=WIZ_START;
}

unsigned long wizInPrin(void)
{
	return wiz_r;
}

void wiz_put_str(unsigned char *buf)
{
	while(*buf!=0) ROM_UARTCharPutNonBlocking(WIZ610_UART_BASE,*buf++);
}
