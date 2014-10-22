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

static unsigned char g_ucTxBuf[256];
static unsigned char g_ucRxBufA[256];
static unsigned char g_ucRxBufB[256];

static unsigned long g_ulRxBufACount = 0;
static unsigned long g_ulRxBufBCount = 0;

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
  ROM_UARTFIFOLevelSet(WIZ610_GPIO_BASE, UART_FIFO_TX4_8, UART_FIFO_RX4_8);
  ROM_IntEnable(INT_UART1);
  ROM_UARTEnable(WIZ610_UART_BASE);
  ROM_UARTDMAEnable(WIZ610_UART_BASE, UART_DMA_RX | UART_DMA_TX);
  ROM_UARTIntEnable(WIZ610_UART_BASE, UART_INT_RX | UART_INT_TX);
  ROM_IntEnable(INT_UDMA);
}

void wiz610_uart_isr(void)
{
	unsigned long ulStatus;
	unsigned long ulMode;
	    //
	    // Read the interrupt status of the UART.
	    //
	    ulStatus = ROM_UARTIntStatus(WIZ610_UART_BASE, true);

	    //
	    // Clear any pending status, even though there should be none since no UART
	    // interrupts were enabled.  If UART error interrupts were enabled, then
	    // those interrupts could occur here and should be handled.  Since uDMA is
	    // used for both the RX and TX, then neither of those interrupts should be
	    // enabled.
	    //
	    ROM_UARTIntClear(WIZ610_UART_BASE, ulStatus);

	    //
	    // Check the DMA control table to see if the ping-pong "A" transfer is
	    // complete.  The "A" transfer uses receive buffer "A", and the primary
	    // control structure.
	    //
	    ulMode = ROM_uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT);

	    //
	    // If the primary control structure indicates stop, that means the "A"
	    // receive buffer is done.  The uDMA controller should still be receiving
	    // data into the "B" buffer.
	    //
	    if(ulMode == UDMA_MODE_STOP)
	    {
	        //
	        // Increment a counter to indicate data was received into buffer A.  In
	        // a real application this would be used to signal the main thread that
	        // data was received so the main thread can process the data.
	        //
	        g_ulRxBufACount++;

	        //
	        // Set up the next transfer for the "A" buffer, using the primary
	        // control structure.  When the ongoing receive into the "B" buffer is
	        // done, the uDMA controller will switch back to this one.  This
	        // example re-uses buffer A, but a more sophisticated application could
	        // use a rotating set of buffers to increase the amount of time that
	        // the main thread has to process the data in the buffer before it is
	        // reused.
	        //
	        ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
	                                   UDMA_MODE_PINGPONG,
	                                   (void *)(WIZ610_UART_BASE + UART_O_DR),
	                                   g_ucRxBufA, sizeof(g_ucRxBufA));
	    }

	    //
	    // Check the DMA control table to see if the ping-pong "B" transfer is
	    // complete.  The "B" transfer uses receive buffer "B", and the alternate
	    // control structure.
	    //
	    ulMode = ROM_uDMAChannelModeGet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT);

	    //
	    // If the alternate control structure indicates stop, that means the "B"
	    // receive buffer is done.  The uDMA controller should still be receiving
	    // data into the "A" buffer.
	    //
	    if(ulMode == UDMA_MODE_STOP)
	    {
	        //
	        // Increment a counter to indicate data was received into buffer A.  In
	        // a real application this would be used to signal the main thread that
	        // data was received so the main thread can process the data.
	        //
	        g_ulRxBufBCount++;

	        //
	        // Set up the next transfer for the "B" buffer, using the alternate
	        // control structure.  When the ongoing receive into the "A" buffer is
	        // done, the uDMA controller will switch back to this one.  This
	        // example re-uses buffer B, but a more sophisticated application could
	        // use a rotating set of buffers to increase the amount of time that
	        // the main thread has to process the data in the buffer before it is
	        // reused.
	        //
	        ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
	                                   UDMA_MODE_PINGPONG,
	                                   (void *)(WIZ610_UART_BASE + UART_O_DR),
	                                   g_ucRxBufB, sizeof(g_ucRxBufB));
 }
}

void WIZ610Transfer(void)
{
    ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_UART1RX,
                                    UDMA_ATTR_ALTSELECT | UDMA_ATTR_USEBURST |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);

    //
    // Configure the control parameters for the primary control structure for
    // the UART RX channel.  The primary contol structure is used for the "A"
    // part of the ping-pong receive.  The transfer data size is 8 bits, the
    // source address does not increment since it will be reading from a
    // register.  The destination address increment is byte 8-bit bytes.  The
    // arbitration size is set to 4 to match the RX FIFO trigger threshold.
    // The uDMA controller will use a 4 byte burst transfer if possible.  This
    // will be somewhat more effecient that single byte transfers.
    //
    ROM_uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_4);

    //
    // Configure the control parameters for the alternate control structure for
    // the UART RX channel.  The alternate contol structure is used for the "B"
    // part of the ping-pong receive.  The configuration is identical to the
    // primary/A control structure.
    //
    ROM_uDMAChannelControlSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_NONE | UDMA_DST_INC_8 |
                              UDMA_ARB_4);

    //
    // Set up the transfer parameters for the UART RX primary control
    // structure.  The mode is set to ping-pong, the transfer source is the
    // UART data register, and the destination is the receive "A" buffer.  The
    // transfer size is set to match the size of the buffer.
    //
    ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_PRI_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)(UART1_BASE + UART_O_DR),
                               g_ucRxBufA, sizeof(g_ucRxBufA));

    //
    // Set up the transfer parameters for the UART RX alternate control
    // structure.  The mode is set to ping-pong, the transfer source is the
    // UART data register, and the destination is the receive "B" buffer.  The
    // transfer size is set to match the size of the buffer.
    //
    ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1RX | UDMA_ALT_SELECT,
                               UDMA_MODE_PINGPONG,
                               (void *)(UART1_BASE + UART_O_DR),
                               g_ucRxBufB, sizeof(g_ucRxBufB));

    //
    // Put the attributes in a known state for the uDMA UART1TX channel.  These
    // should already be disabled by default.
    //
    ROM_uDMAChannelAttributeDisable(UDMA_CHANNEL_UART1TX,
                                    UDMA_ATTR_ALTSELECT |
                                    UDMA_ATTR_HIGH_PRIORITY |
                                    UDMA_ATTR_REQMASK);

    //
    // Set the USEBURST attribute for the uDMA UART TX channel.  This will
    // force the controller to always use a burst when transferring data from
    // the TX buffer to the UART.  This is somewhat more effecient bus usage
    // than the default which allows single or burst transfers.
    //
    ROM_uDMAChannelAttributeEnable(UDMA_CHANNEL_UART1TX, UDMA_ATTR_USEBURST);

    //
    // Configure the control parameters for the UART TX.  The uDMA UART TX
    // channel is used to transfer a block of data from a buffer to the UART.
    // The data size is 8 bits.  The source address increment is 8-bit bytes
    // since the data is coming from a buffer.  The destination increment is
    // none since the data is to be written to the UART data register.  The
    // arbitration size is set to 4, which matches the UART TX FIFO trigger
    // threshold.
    //
    ROM_uDMAChannelControlSet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT,
                              UDMA_SIZE_8 | UDMA_SRC_INC_8 | UDMA_DST_INC_NONE |
                              UDMA_ARB_4);

    //
    // Set up the transfer parameters for the uDMA UART TX channel.  This will
    // configure the transfer source and destination and the transfer size.
    // Basic mode is used because the peripheral is making the uDMA transfer
    // request.  The source is the TX buffer and the destination is the UART
    // data register.
    //
    ROM_uDMAChannelTransferSet(UDMA_CHANNEL_UART1TX | UDMA_PRI_SELECT,
                               UDMA_MODE_BASIC, g_ucTxBuf,
                               (void *)(UART1_BASE + UART_O_DR),
                               4);

    //
    // Now both the uDMA UART TX and RX channels are primed to start a
    // transfer.  As soon as the channels are enabled, the peripheral will
    // issue a transfer request and the data transfers will begin.
    //
    ROM_uDMAChannelEnable(UDMA_CHANNEL_UART1RX);
    ROM_uDMAChannelEnable(UDMA_CHANNEL_UART1TX);
}


