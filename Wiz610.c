#include "inc/hw_ints.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_types.h"
#include "inc/hw_timer.h"
#include "inc/hw_udma.h"
#include "inc/hw_uart.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/udma.h"
#include "include/wiz610.h"

unsigned char g_ucTxBuf[128];
unsigned char g_ucRxBuf[128];

static unsigned long g_ulRxBufACount = 0;
static unsigned long g_Wiz610_fTX;
static unsigned long g_Wiz610_fTXDMA_STOP;
static unsigned long g_Wiz610_fRX;

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
  ROM_UARTFIFOLevelSet(WIZ610_UART_BASE, UART_FIFO_TX4_8, UART_FIFO_RX1_8);
  ROM_IntEnable(INT_UART1);
  ROM_UARTEnable(WIZ610_UART_BASE);
  ROM_UARTDMAEnable(WIZ610_UART_BASE, UART_DMA_TX);
  ROM_UARTIntEnable(WIZ610_UART_BASE, UART_INT_RX);
  ROM_IntEnable(INT_UDMA);
}

void wiz610_uart_isr(void)
{
		unsigned long ulStatus;
		unsigned long ulMode;
	    ulStatus = ROM_UARTIntStatus(WIZ610_UART_BASE, true);
	    ROM_UARTIntClear(WIZ610_UART_BASE, ulStatus);
	    if(ulStatus==UART_INT_RX)
	    {
	    	g_Wiz610_fRX=true;
	    	while(!(HWREG(WIZ610_UART_BASE + UART_O_FR) & UART_FR_RXFE))
	    	{
	    		g_ucRxBuf[g_ulRxBufACount]=HWREG(WIZ610_UART_BASE+UART_O_DR);
	    		g_ulRxBufACount=(g_ulRxBufACount+1)&0x7f;
	    	}
	    }
}

void WIZ610Transfer(void)
{
    ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_UART1TX,
                                        UDMA_ATTR_ALTSELECT |
                                        UDMA_ATTR_HIGH_PRIORITY |
                                        UDMA_ATTR_REQMASK);
    ROM_uDMAChannelAttributeEnable(UDMA_CHANNEL_UART1TX, UDMA_ATTR_USEBURST);

    ROM_uDMAChannelControlSet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE |
                              UDMA_ARB_4);

}

unsigned char Wiz610_put_buf(unsigned char *buf, unsigned long count)
{
	unsigned long i;
	if (ROM_uDMAChannelModeGet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT)!=UDMA_MODE_STOP) return false;
	i=0;
	while(i<count)
	{
		g_ucTxBuf[i]=*buf++;
		i++;
	}
	ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT,
	                               UDMA_MODE_BASIC,(void *) g_ucTxBuf,
	                               (void *)(UART1_BASE + UART_O_DR),
	                                count);
	ROM_uDMAChannelEnable(UDMA_CHANNEL_UART1TX);
    return true;
}
