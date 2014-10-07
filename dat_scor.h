#ifndef _DAT_SCOR_H_
#define _DAT_SCOR_H_

#define CCP_A_GPIO_PERIPH         SYSCTL_PERIPH_GPIOD
#define CCP_B_GPIO_PERIPH         SYSCTL_PERIPH_GPIOD

#define CCP_A_GPIO_PIN            GPIO_PIN_2
#define CCP_B_GPIO_PIN            GPIO_PIN_3

#define CCP_A_TIMER_PERIPH        SYSCTL_PERIPH_WTIMER3
#define CCP_B_TIMER_PERIPH        SYSCTL_PERIPH_WTIMER3

#define CCP_A_GPIO_PIN_CFG        GPIO_PD2_WT3CCP0
#define CCP_B_GPIO_PIN_CFG        GPIO_PD3_WT3CCP1

#define CCP_A_TIMER               TIMER_A
#define CCP_B_TIMER               TIMER_B

#define CCP_A_GPIO_BASE           GPIO_PORTD_BASE
#define CCP_A_TIMER_BASE          WTIMER3_BASE

#define CCP_B_GPIO_BASE           GPIO_PORTD_BASE
#define CCP_B_TIMER_BASE          WTIMER3_BASE

void DatSkor_init(void);

#endif