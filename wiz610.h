#ifndef _WIZ610_H_
#define _WIZ610_H_

#define WIZ610_GPIO_BASE                      GPIO_PORTB_BASE
#define WIZ610_UART_BASE                      UART1_BASE
#define WIZ610_GPIO_PERIPH                    SYSCTL_PERIPH_GPIOB
#define WIZ610_UART_PERIPH                    SYSCTL_PERIPH2_UART1
#define WIZ610_GPIO_PIN_CMD_ENABLE            GPIO_PIN_5
#define WIZ610_GPIO_PIN_RX                    GPIO_PIN_0
#define WIZ610_GPIO_PIN_TX                    GPIO_PIN_1

void wiz610_init(void);
#endif
