#include "driverlib/hw_ints.h"
#include "driverlib/hw_gpio.h"
#include "driverlib/hw_memmap.h"
#include "driverlib/hw_sysctl.h"
#include "driverlib/hw_types.h"
#include "driverlib/hw_timer.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "include/servo.h"
#include "include/led.h"
#include "include/dvig.h"
#include "include/dat_scor.h"
#include "include/lcd.h"

void lcd_temizle(void)
{  
  lcd_komut(0x01);
  ROM_SysCtlDelay(ROM_SysCtlClockGet()/300); // 10ms
}


// ��������� ��������� LCD
void lcd_init(void)
{
  ROM_SysCtlPeripheralEnable(LCD_GPIO_PERIPH);
  ROM_GPIODirModeSet(LCD_GPIO_BASE,LCD_PORT_MASK,GPIO_DIR_MODE_OUT);
  ROM_GPIOPadConfigSet(LCD_GPIO_BASE,LCD_PORT_MASK,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
  LCD_RS(0);
  LCD_EN(0);
  lcd_komut(0x28);  // 4 Bit , �ift Sat�r LCD
  lcd_komut(0x0C);  // �mle� Gizleniyor
  lcd_komut(0x06);  // Sa�a do�ru yazma aktif
  lcd_komut(0x80);  // LCD Birinci Sat�r Konumunda
  lcd_komut(0x28);  // 4 Bit , �ift Sat�r LCD
  lcd_temizle();

}
// ������� ������� � LCD
void lcd_komut(unsigned char c)
{
  LCD_RS(0);  
  ROM_SysCtlDelay(ROM_SysCtlClockGet()/1500); // 2ms
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,0);
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,(c & 0xF0));
  EN_ACKAPA();
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,0);
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,((c & 0x0F)<<4));
  EN_ACKAPA(); 
}

void lcd_putch(char c)
{
  LCD_RS(1);       
  ROM_SysCtlDelay(ROM_SysCtlClockGet()/1500); // 2ms
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,0);
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,(c & 0xF0));
  EN_ACKAPA();
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,0);
  ROM_GPIOPinWrite(GPIO_PORTA_BASE,0xF0,((c & 0x0F)<<4));
  EN_ACKAPA(); 
}

void lcd_puts(const char* s)
{ 
  while(*s) lcd_putch(*s++);
}

void lcd_goto(char x, char y)
{ 
  switch(x)
  {
  case 0:
    {
    lcd_komut(0x80+(y%16));
    break;
    }
  case 1:
    {
    lcd_komut(0xC0+(y%16));
    break;
    }
    case 2:
    {
    lcd_komut(0x90+(y%16));
    break;
    }
     case 3:
    {
    lcd_komut(0xD0+(y%16));
    break;
    }
  }
}

