#ifndef _WIZ610_H_
#define _WIZ610_H_

#define WIZ610_GPIO_BASE                      GPIO_PORTB_BASE
#define WIZ610_UART_BASE                      UART1_BASE
#define WIZ610_GPIO_PERIPH                    SYSCTL_PERIPH_GPIOB
#define WIZ610_UART_PERIPH                    SYSCTL_PERIPH2_UART1
#define WIZ610_GPIO_PIN_CMD_ENABLE            GPIO_PIN_5
#define WIZ610_GPIO_PIN_RX                    GPIO_PIN_0
#define WIZ610_GPIO_PIN_TX                    GPIO_PIN_1

#define wiz_char_start '<'
#define wiz_char_stop  '>'
#define WIZ_MB_TCP_UID          6
#define MB_TCP_TID          0
#define MB_TCP_PID          2

typedef enum
{
	WIZ_IDLE,
	WIZ_START,
	WIZ_RESV,
	WIZ_STOP
}wiz_rab;

typedef enum
{
	MODBUS_TCP_IDLE,
	MODBUS_TCP_RCV
}wiz_tcp_rab;



void wiz610_init(void);
void WIZ610Transfer(void);
unsigned char Wiz610_put_buf(unsigned char *buf, unsigned long count);
unsigned char Wiz610_get_buf(unsigned char *buf);
#endif
