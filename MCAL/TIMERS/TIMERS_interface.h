/********************************************************/
/************** Name : Youssef Moghazy ******************/
/************** Date : 16/7/2023       ******************/
/************** SWC  : TIMERS          ******************/
/************** Version : 1.0          ******************/
/********************************************************/
#ifndef MCAL_TIMERS_TIMERS_INTERFACE_H_
#define MCAL_TIMERS_TIMERS_INTERFACE_H_

void TIMERS_voidTimer0Init(void);
void TIMERS_voidTimer1Init(void);
u8 TIMERS_u8TIMER0SetCallBack(void(*Copy_pf)(void));
u8 TIMERS_u8TIMER0CTCSetCallBack(void(*Copy_pf)(void));
void TIMERS_voidTIMER0SetCompareMatchValue(u8 Copy_u8OCR0Value);
void TIMERS_voidTIMER1SetCompareMatchValueA(u16 Copy_u8OCR1Value);

#endif /* MCAL_TIMERS_TIMERS_INTERFACE_H_ */
