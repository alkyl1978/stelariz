#ifndef _FOT_H_
#define _FOT_H_

#define CCP_FOTO_GPIO_PERIPH         SYSCTL_PERIPH_GPIOD
#define CCP_FOTO_TIMER_PERIPH        SYSCTL_PERIPH_WTIMER5
#define CCP_FOTO_GPIO_BASE           GPIO_PORTD_BASE
#define CCP_FOTO_TIMER_BASE          WTIMER5_BASE
#define CCP_FOTO_GPIO_PIN_CFG        GPIO_PD6_WT5CCP0
#define CCP_FOTO_GPIO_PIN            GPIO_PIN_6

void foto_init(void);

#endif
