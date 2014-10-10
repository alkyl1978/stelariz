#ifndef _LED_H_
#define _LED_H_

// определение светодиодов
#define LED_BLU GPIO_PIN_2
#define LED_RED GPIO_PIN_1
#define LED_GREN GPIO_PIN_3

// определение шима

#define RED_GPIO_PERIPH         SYSCTL_PERIPH_GPIOF
#define RED_TIMER_PERIPH        SYSCTL_PERIPH_TIMER0
#define BLUE_GPIO_PERIPH        SYSCTL_PERIPH_GPIOF
#define BLUE_TIMER_PERIPH       SYSCTL_PERIPH_TIMER1
#define GREEN_GPIO_PERIPH       SYSCTL_PERIPH_GPIOF
#define GREEN_TIMER_PERIPH      SYSCTL_PERIPH_TIMER1


#define RED_GPIO_BASE           GPIO_PORTF_BASE
#define RED_TIMER_BASE          TIMER0_BASE
#define BLUE_GPIO_BASE          GPIO_PORTF_BASE
#define BLUE_TIMER_BASE         TIMER1_BASE
#define GREEN_GPIO_BASE         GPIO_PORTF_BASE
#define GREEN_TIMER_BASE        TIMER1_BASE

#define RED_GPIO_PIN            GPIO_PIN_1
#define BLUE_GPIO_PIN           GPIO_PIN_2
#define GREEN_GPIO_PIN          GPIO_PIN_3


#define RED_GPIO_PIN_CFG        GPIO_PF1_T0CCP1
#define BLUE_GPIO_PIN_CFG       GPIO_PF2_T1CCP0
#define GREEN_GPIO_PIN_CFG      GPIO_PF3_T1CCP1

#define RED_TIMER_CFG           TIMER_CFG_B_PWM
#define BLUE_TIMER_CFG          TIMER_CFG_A_PWM
#define GREEN_TIMER_CFG         TIMER_CFG_B_PWM

#define RED_TIMER               TIMER_B
#define BLUE_TIMER              TIMER_A
#define GREEN_TIMER             TIMER_B

void led_init(void);

#endif