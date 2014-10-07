#ifndef _DVIG_H_
#define _DVIG_H_

#define PWM0_GPIO_BASE           GPIO_PORTB_BASE
#define PWM0_TIMER_BASE          TIMER3_BASE
#define PWM1_GPIO_BASE           GPIO_PORTB_BASE
#define PWM1_TIMER_BASE          TIMER3_BASE

#define PWM0_GPIO_PERIPH         SYSCTL_PERIPH_GPIOB
#define PWM0_TIMER_PERIPH        SYSCTL_PERIPH_TIMER3
#define PWM1_GPIO_PERIPH         SYSCTL_PERIPH_GPIOB
#define PWM1_TIMER_PERIPH        SYSCTL_PERIPH_TIMER3

#define PWM0_GPIO_PIN            GPIO_PIN_2
#define PWM1_GPIO_PIN            GPIO_PIN_3

#define PWM0_GPIO_PIN_CFG        GPIO_PB2_T3CCP0
#define PWM1_GPIO_PIN_CFG        GPIO_PB3_T3CCP1

#define PWM0_TIMER_CFG           TIMER_CFG_A_PWM
#define PWM1_TIMER_CFG           TIMER_CFG_B_PWM

#define PWM0_TIMER               TIMER_A
#define PWM1_TIMER               TIMER_B

#define PWM0_NAPR_A_GPIO_PERIPH      SYSCTL_PERIPH_GPIOE
#define PWM0_NAPR_B_GPIO_PERIPH      SYSCTL_PERIPH_GPIOE

#define PWM0_NAPR_A_GPIO_PIN         GPIO_PIN_0
#define PWM0_NAPR_B_GPIO_PIN         GPIO_PIN_1

#define PWM0_NAPR_A_GPIO_BASE        GPIO_PORTE_BASE
#define PWM0_NAPR_B_GPIO_BASE        GPIO_PORTE_BASE

#define PWM1_NAPR_A_GPIO_PERIPH      SYSCTL_PERIPH_GPIOE
#define PWM1_NAPR_B_GPIO_PERIPH      SYSCTL_PERIPH_GPIOE

#define PWM1_NAPR_A_GPIO_PIN         GPIO_PIN_2
#define PWM1_NAPR_B_GPIO_PIN         GPIO_PIN_3

#define PWM1_NAPR_A_GPIO_BASE        GPIO_PORTE_BASE
#define PWM1_NAPR_B_GPIO_BASE        GPIO_PORTE_BASE

void Dvig_init(void);

#endif