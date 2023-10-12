/********************************************************/
/************** Name : Youssef Moghazy ******************/
/************** Date : 16/7/2023       ******************/
/************** SWC  : TIMERS          ******************/
/************** Version : 1.0          ******************/
/********************************************************/
/*LIB*/
#include "../../lib/STD_TYPES/STD_TYPES.h"
#include "../../lib/BIT_Math/BIT_MATH.h"
#include "TIMERS_config.h"
#include "TIMERS_interface.h"
#include "TIMERS_private.h"

/* Global Pointer To Function for TIMER0 Overflow */
static void(*TIMERS_pfTIMER0OVF)(void) = NULL;

/* Global Pointer To Function for TIMER0 CTC */
static void(*TIMERS_pfTIMER0CTC)(void) = NULL;

/*********************************************************************************/
/* Function: TIMERS_voidTimer0Init	                        				    **/
/* I/P Parameters: Nothing									          		    **/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function initialises Timer0							       	    **/
/*********************************************************************************/
void TIMERS_voidTimer0Init(void){
	/* Select Mode => Normal Mode*/
	#if TIMER_MODE == NORMAL_MODE
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM00_PIN);
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM01_PIN);
	/* Set Preload Value */
	TIMERS_u8_TCNT0_REG = 192;
	/* Enable Overflow Interrupt */
	#if INTERRUPT_MODE == Overflow_Mode
	SET_BIT(TIMERS_u8_TIMSK_REG, TIMERS_TIMSK_TOIE0_PIN);
	#else if INTERRUPT_MODE == CTC_Mode
	SET_BIT(TIMERS_u8_TIMSK_REG, TIMERS_TIMSK_TOIE1_PIN);
	#endif
	#elif TIMER_MODE == CTC_MODE
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM00_PIN);
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM01_PIN);
	/* SET Compare Match Unit Register */
	TIMERS_u8_OCR0_REG = 99;
	/* Enable Overflow Interrupt */
	#if INTERRUPT_MODE == Overflow_Mode
	SET_BIT(TIMERS_u8_TIMSK_REG, TIMERS_TIMSK_TOIE0_PIN);
	#else if INTERRUPT_MODE == CTC_Mode
	SET_BIT(TIMERS_u8_TIMSK_REG, TIMERS_TIMSK_TOIE1_PIN);
	#endif
	#elif TIMER_MODE == PWM_PHASE_CORRECT
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM00_PIN);
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM01_PIN);
	#if OC0_MODE == Inverting
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM01);
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM00);
	#elif OC0_MODE == Non_Inverting
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM01);
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM00);
	#endif
	#elif TIMER_MODE == PWM_FAST
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM00_PIN);
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_WGM01_PIN);
	#if OC0_MODE == Inverting
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM01);
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM00);
	#elif OC0_MODE == Non_Inverting
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM01);
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_COM00);
	#endif
	#endif


	/* Set Prescaler Value => clk / 8 */
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_CS00_PIN);
	SET_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_CS01_PIN);
	CLR_BIT(TIMERS_u8_TCCR0_REG, TIMERS_TCCR0_CS02_PIN);
}
/*********************************************************************************/
/* Function: TIMERS_voidTimer1Init	                        				    **/
/* I/P Parameters: Nothing									          		    **/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function initialises Timer1							       	    **/
/*********************************************************************************/
void TIMERS_voidTimer1Init(void){
	/* Select Timer1 Mode => PWM Fact(14) */
	SET_BIT(TIMERS_u8_TCCR1A_REG, TIMER1_WGM11);
	CLR_BIT(TIMERS_u8_TCCR1A_REG, TIMER1_WGM10);
	SET_BIT(TIMERS_u8_TCCR1B_REG, TIMER1_WGM12);
	SET_BIT(TIMERS_u8_TCCR1B_REG, TIMER1_WGM13);

	/* Select HW Action on OCA1 pin => Non- Inverting */
	SET_BIT(TIMERS_u8_TCCR1A_REG, TIMER1_COM1A1);
	CLR_BIT(TIMERS_u8_TCCR1A_REG, TIMER1_COM1A0);

	/* Set Top Value in ICR1 */
	TIMERS_u16_ICR1_REG = 19999;

	/* Set Angle Of Servo Motor */
	TIMERS_u16_OCR1A_REG = 499;

	/* Set Prescaler Value => clk / 8 */
	CLR_BIT(TIMERS_u8_TCCR1B_REG, TIMERS_TCCR0_CS00_PIN);
	SET_BIT(TIMERS_u8_TCCR1B_REG, TIMERS_TCCR0_CS01_PIN);
	CLR_BIT(TIMERS_u8_TCCR1B_REG, TIMERS_TCCR0_CS02_PIN);
}

/*********************************************************************************/
/* Function: TIMERS_u8TIMER0SetCallBack(void(*capy_pf)(void))                   **/
/* I/P Parameters: 	Pointer to Function							          		**/
/* Returns:it returns Error states                                 				**/
/* Desc:This Function Timer0 ISR 							       	   		    **/
/*********************************************************************************/
u8 TIMERS_u8TIMER0SetCallBack(void(*Copy_pf)(void)){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL){
		TIMERS_pfTIMER0OVF = Copy_pf;
	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/*********************************************************************************/
/* Function: TIMERS_u8TIMER0CTCSetCallBack(void(*capy_pf)(void))                **/
/* I/P Parameters: 	POinter to Function							          		**/
/* Returns:it returns Error states                                				**/
/* Desc:This Function Sets the call back of Timer0	CTC Mode  					**/
/*********************************************************************************/

u8 TIMERS_u8TIMER0CTCSetCallBack(void(*Copy_pf)(void)){
	u8 Local_u8ErrorState = STD_TYPES_OK;
	if(Copy_pf != NULL){
		TIMERS_pfTIMER0CTC = Copy_pf;
	}
	else{
		Local_u8ErrorState = STD_TYPES_NOK;
	}
	return Local_u8ErrorState;
}
/*********************************************************************************/
/* Function: TIMERS_voidTIMER0SetCompareMatchValue	               				**/
/* I/P Parameters: Copy_u8OCR0Value						          		    	**/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function Sets the compare value of timer 0					       	**/
/*********************************************************************************/
/* Copy_u16CompareValue Options: Compare value assigned directly				**/
/*********************************************************************************/
void TIMERS_voidTIMER0SetCompareMatchValue(u8 Copy_u8OCR0Value){

	TIMERS_u8_OCR0_REG = Copy_u8OCR0Value;

}
/*********************************************************************************/
/* Function: TIMERS_voidTIMER1SetCompareMatchValueA               				**/
/* I/P Parameters: Copy_u8OCR1Value						          		        **/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function Sets the compare value of timer 1 - A				       	**/
/*********************************************************************************/
/* Copy_u16CompareValue Options: Compare value assigned directly				**/
/*********************************************************************************/
void TIMERS_voidTIMER1SetCompareMatchValueA(u16 Copy_u8OCR1Value){
	TIMERS_u16_OCR1A_REG = Copy_u8OCR1Value;
}
/*********************************************************************************/
/* Function:void __vector_11 (void) __attribute__((signal));					**/
/*            void __vector_11 (void)                      				        **/
/* I/P Parameters: Nothing									          		    **/
/* Returns:it returns No thing                                				    **/
/* Desc:Function Sets the call back of Timer0 of over flow 	normal mode 		**/
/*********************************************************************************/
/***********************************Timer0 ISR for over flow ***********************************/

void __vector_11(void)		__attribute__((signal));

void __vector_11(void){
	static u16 Local_u16CounterOVF = 0;
	Local_u16CounterOVF++;
	if(Local_u16CounterOVF == 3907){
		/* Update Preload Value */
		TIMERS_u8_TCNT0_REG = 192;

		/* Clear Overflow Counter */
		Local_u16CounterOVF = 0;

		/* Call App Function */
		if(TIMERS_pfTIMER0OVF != NULL){
			TIMERS_pfTIMER0OVF();
		}
	}
}
/*********************************************************************************/
/* Function:void __vector_10 (void) __attribute__((signal));					**/
/*            void __vector_10 (void)                      				        **/
/* I/P Parameters: Nothing									          		    **/
/* Returns:it returns No thing                                				    **/
/* Desc:This Function Timer0 ISR  of  CTC Mode 							       	**/
/*********************************************************************************/
/***********************************Timer0 ISR forCompare Match Event***********************************/
void __vector_10(void)		__attribute__((signal));

void __vector_10(void){
	static u16 Local_u16CounterCTC = 0;
	Local_u16CounterCTC++;
	if(Local_u16CounterCTC == 10000){
		Local_u16CounterCTC = 0;
		/* Call App Function */
		if(TIMERS_pfTIMER0CTC != NULL){
			TIMERS_pfTIMER0CTC();
		}
	}
}
