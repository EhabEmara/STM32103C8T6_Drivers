/**********************************************************/
/* Author    : Ehab Emara Ahmed                           */
/* Date      : 26/4/2022                                  */
/* Version   : V01                                        */
/**********************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"EXTI_interface.h"
#include"EXTI_config.h"
#include"EXTI_private.h"


/*Global pointer to array of void functions each function is required to each interrupt*/
static void (*EXTI_CallBack[3]) (void);
/**************************************************************************************/




void MEXTI_voidInit(void)
{
	#if		EXTI_LINE == EXTI_LINE0
			SET_BIT(EXTI -> IMR , EXTI_LINE0 );
	#elif	EXTI_LINE == EXTI_LINE1
			SET_BIT(EXTI -> IMR , EXTI_LINE1 );
	#elif	EXTI_LINE == EXTI_LINE2
			SET_BIT(EXTI -> IMR , EXTI_LINE2 );
	#else
	//	#error ("Wrong Externl Interrupt Line !")
	#endif
	
	
	#if		EXTI_SENSE_MODE == FALLING_EDGE
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == RISING_EDGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
	#elif	EXTI_SENSE_MODE == ON_CHANGE
			SET_BIT(EXTI -> RTSR , EXTI_LINE);
			SET_BIT(EXTI -> FTSR , EXTI_LINE);
	#else
		//#error ("Wrong Externl Interrupt Sense Mode !")
	#endif
	
	
}
void MEXTI_voidSetSignalLatch(u8 Copy_u8EXTILine , u8 Copy_u8EXTISenseMode)
{	
	switch(Copy_u8EXTISenseMode)
	{
		case	RAISING_EDGE		:	SET_BIT(EXTI -> RTSR , Copy_u8EXTILine);break;
		case	FALLING_EDGE	:	SET_BIT(EXTI -> FTSR , Copy_u8EXTILine);	break;
		case	ANY_CHANGE		:	SET_BIT(EXTI -> RTSR , Copy_u8EXTILine);
									SET_BIT(EXTI -> FTSR , Copy_u8EXTILine);	break;
	}
	SET_BIT(EXTI -> IMR , Copy_u8EXTILine);
}
void MEXTI_voidEnableEXTI(u8 Copy_u8EXTILine)
{
	SET_BIT(EXTI -> IMR , Copy_u8EXTILine);
}
void MEXTI_voidDisableEXTI(u8 Copy_u8EXTILine)
{
	CLR_BIT(EXTI -> IMR , Copy_u8EXTILine);
	
}
void MEXTI_voidSoftwareTrigger(u8 Copy_u8EXTILine)
{
	
}

void MEXTI_SetCallBack(void (*ptr)(void) ,u8 number)
{
	      EXTI_CallBack[number] = ptr;
}


/*ISR for EXternal interrupt number = 0 */
void	EXTI0_IRQHandler(void)
{

     EXTI_CallBack[0]() ;
	 SET_BIT(EXTI -> PR , 0);

}
/**************************************************************************************/

/*ISR for EXternal interrupt number = 1 */
void	EXTI1_IRQHandler(void)
{
	EXTI_CallBack[1]();

	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 1);

}
/**************************************************************************************/

/*ISR for EXternal interrupt number = 3 */
void	EXTI3_IRQHandler(void)
{

	EXTI_CallBack[3]();
	/*	Clear pending Bit		*/
	SET_BIT(EXTI -> PR , 3);

}
/**************************************************************************************/

