#ifndef _LCD_H_
#define _LCD_H_

#define LCD_GPIO_PERIPH         SYSCTL_PERIPH_GPIOA
#define LCD_GPIO_BASE           GPIO_PORTA_BASE
#define LCD_PORT_MASK           0xFC     

#define DB7_GPIO_PIN            GPIO_PIN_7
#define DB6_GPIO_PIN            GPIO_PIN_6
#define DB5_GPIO_PIN            GPIO_PIN_5
#define DB4_GPIO_PIN            GPIO_PIN_4
#define RS_GPIO_PIN             GPIO_PIN_3
#define EN_GPIO_PIN              GPIO_PIN_2


#define	LCD_RS(x)       ( (x) ? (ROM_GPIOPinWrite(GPIO_PORTA_BASE,RS_GPIO_PIN,RS_GPIO_PIN)) : (ROM_GPIOPinWrite(GPIO_PORTA_BASE,RS_GPIO_PIN,0)) )
#define LCD_EN(x)       ( (x) ? (ROM_GPIOPinWrite(GPIO_PORTA_BASE,EN_GPIO_PIN,EN_GPIO_PIN)) : (ROM_GPIOPinWrite(GPIO_PORTA_BASE,EN_GPIO_PIN,0)) )
#define	EN_ACKAPA()     LCD_EN(1),LCD_EN(0)

void lcd_init(void);
void lcd_komut(unsigned char c);
void lcd_temizle(void);
void lcd_putch(char c);
void lcd_puts(const char* s);
void lcd_goto(char x, char y);

#endif