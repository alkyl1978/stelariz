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
#include "inc/uart.h"
#include "wiz610.h"

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
   ROM_GPIOPinTypeUART(WIZ610_GPIO_BASE, WIZ610_GPIO_PIN_RX | WIZ610_GPIO_PIN_RX);
   ROM_UARTConfigSetExpClk(WIZ610_UART_BASE, ROM_SysCtlClockGet(), 115200,
                            (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE |
                             UART_CONFIG_PAR_NONE));
   ROM_GPIOPinWrite(WIZ610_GPIO_BASE,WIZ610_GPIO_PIN_CMD_ENABLE,0);   
}
