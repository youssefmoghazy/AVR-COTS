/********************************************************/
/************** Name : Youssef Moghazy ******************/
/************** Date : 16/7/2023       ******************/
/************** SWC  : TIMERS          ******************/
/************** Version : 1.0          ******************/
/********************************************************/
#ifndef MCAL_TIMERS_TIMERS_CONFIG_H_
#define MCAL_TIMERS_TIMERS_CONFIG_H_
/*********************************************/
/* Timer Mode */
#define NORMAL_MODE				0
#define CTC_MODE				1
#define PWM_PHASE_CORRECT		2
#define PWM_FAST				3
/*********************************************/
/* Interrupt Mode */
#define Overflow_Mode			0
#define CTC_Mode				1
/*********************************************/
/* OC0 Mode */
#define Inverting				0
#define Non_Inverting			1
/*********************************************/
#define TIMER_MODE				PWM_FAST

#define INTERRUPT_MODE			CTC_Mode

#define OC0_MODE			Inverting


#endif /* MCAL_TIMERS_TIMERS_CONFIG_H_ */
