#ifndef _SERVO_H_
#define _SERVO_H_

//******************************************************************************************
#define SERV_X_GPIO_PERIPH         SYSCTL_PERIPH_GPIOC
#define SERV_X_TIMER_PERIPH        SYSCTL_PERIPH_WTIMER0
#define SERV_Y_GPIO_PERIPH        SYSCTL_PERIPH_GPIOC
#define SERV_Y_TIMER_PERIPH       SYSCTL_PERIPH_WTIMER0
#define SERV_Z_GPIO_PERIPH       SYSCTL_PERIPH_GPIOC
#define SERV_Z_TIMER_PERIPH      SYSCTL_PERIPH_WTIMER1


#define SERV_X_GPIO_BASE           GPIO_PORTC_BASE
#define SERV_X_TIMER_BASE          WTIMER0_BASE
#define SERV_Y_GPIO_BASE          GPIO_PORTC_BASE
#define SERV_Y_TIMER_BASE         WTIMER0_BASE
#define SERV_Z_GPIO_BASE         GPIO_PORTC_BASE
#define SERV_Z_TIMER_BASE        WTIMER1_BASE

#define SERV_X_GPIO_PIN            GPIO_PIN_4
#define SERV_Y_GPIO_PIN           GPIO_PIN_5
#define SERV_Z_GPIO_PIN          GPIO_PIN_6


#define SERV_X_GPIO_PIN_CFG        GPIO_PC4_WT0CCP0
#define SERV_Y_GPIO_PIN_CFG       GPIO_PC5_WT0CCP1
#define SERV_Z_GPIO_PIN_CFG      GPIO_PC6_WT1CCP0

#define SERV_X_TIMER_CFG           TIMER_CFG_A_PWM
#define SERV_Y_TIMER_CFG          TIMER_CFG_B_PWM
#define SERV_Z_TIMER_CFG         TIMER_CFG_A_PWM

#define SERV_X_TIMER               TIMER_A
#define SERV_Y_TIMER              TIMER_B
#define SERV_Z_TIMER             TIMER_A

void servo_init(void);

#endif