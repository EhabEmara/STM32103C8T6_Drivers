/**********************************************************/
/* Author    : Ehab Emara Ahmed                           */
/* Date      : 26/4/2022                                  */
/* Version   : V01                                        */
/**********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "RCC_interface.h"
#include "DIO_interface.h"
#include "NVIC_interface.h"
#include "EXTI_interface.h"
#include "STK_interface.h"
#include "AFIO_interface.h"



/*functions to be O/P when external interrupts fired */
void EXTI0_Func(void);
void EXTI1_Func(void);
void EXTI3_Func(void);
/**********************************************************/

int main(void)
{

    /************ Enable clock for the processor*********** */

	MRCC_voidInitSysClock();
	/**********************************************************/

	/************ Enable the peripherals which used in the application : GPIOA , GPIOB , AFIO
	 * and those peripherals are on the APB2 Bus  *************/

	MRCC_voidEnableClock(RCC_APB2 , AFIO);
	MRCC_voidEnableClock(RCC_APB2 , GPIOA);
	MRCC_voidEnableClock(RCC_APB2 , GPIOB);
	/**********************************************************/

	/*Configure a EXTI_LINE0 PIN_A0 for EXTI0 and EXTI_LINE1 PIN_A1 for EXTI3
	 *  and EXTI_LINE3 PIN_B3 for EXTI3 */
	MAFIO_voidSetEXTIConfiguration(EXTI_LINE0,EXTI_PINA);
	MAFIO_voidSetEXTIConfiguration(EXTI_LINE1,EXTI_PINA);
	MAFIO_voidSetEXTIConfiguration(EXTI_LINE3,EXTI_PINB);
	/**********************************************************/

	/*EXTI0_Func will be called when A0 pin is fired */
	/*EXTI1_Func will be called when A1 pin is fired */
	/*EXTI3_Func will be called when B3 pin is fired */
	MEXTI_SetCallBack(EXTI0_Func,0);
	MEXTI_SetCallBack(EXTI1_Func,1);
	MEXTI_SetCallBack(EXTI3_Func,3);
	/**********************************************************/
	

	/******* Configure PIN0 IN PORTA AS I/P PULL UP RESISITOR to receive Interrupt 0 ******/
	MGPIO_VidSetPinDirection(GPIOA , PIN0 , INPUT_PULLUP_PULLDOWN);
	MGPIO_VidSetPinValue(GPIOA , PIN0 ,HIGH );
	/**********************************************************/

	/******* Configure PIN1 IN PORTA AS I/P PULL UP RESISITOR to receive Interrupt 1 ******/
	MGPIO_VidSetPinDirection(GPIOA , PIN1 , INPUT_PULLUP_PULLDOWN);
	MGPIO_VidSetPinValue(GPIOA , PIN1 ,HIGH );
	/**********************************************************/

	/******* Configure PIN3 IN PORTB AS I/P PULL UP RESISITOR to receive Interrupt 3 ******/
	MGPIO_VidSetPinDirection(GPIOB , PIN3 , INPUT_PULLUP_PULLDOWN);
	MGPIO_VidSetPinValue(GPIOB , PIN3 ,HIGH );
	/**********************************************************/

	/*** Configure PIN2 , PIN3 , PIN1  In ports PORTA & PORTB As O/P PUSH UP RESISTOR  *****/
	MGPIO_VidSetPinDirection(GPIOA , PIN2 , OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(GPIOA , PIN3 , OUTPUT_SPEED_2MHZ_PP);
	MGPIO_VidSetPinDirection(GPIOB , PIN1 , OUTPUT_SPEED_2MHZ_PP);
	/**********************************************************/

	/* Configure The interrupt according to its EXTI_LINE  which passed to the function
	 and also configure the sensing mode of the I/P signal for this interrupt */
	MEXTI_voidSetSignalLatch(EXTI_LINE0 , FALLING_EDGE);
	MEXTI_voidSetSignalLatch(EXTI_LINE1 , FALLING_EDGE);
	MEXTI_voidSetSignalLatch(EXTI_LINE3 , FALLING_EDGE);
	/**********************************************************/

	/* Setting the priority according to the Selected mode which is 2 bits for
	 *  GROUPs and 2 bits for SUBs */
	/*EXTI0 which its number is 6 is located in group 3 and sub 3*/
	/*EXTI1 which its number is 7 is located in group 3 and sub 0*/
	/*EXTI3 which its number is 9 is located in group 0 and sub 0 */


	/*  Note : EXTI3 has the highest priority so it can't be interrupted by EXTI0 or EXTI1
	 *  while running and EXTI1 and EXTI0 located in the same group but EXTI1 is highest
	 *  priority in its group only so EXTI0 can't interrupted EXT1 while running , EXTI0
	 *  has the lowest priority in the 3 interrupts so it can be interrupted by EXTI1 and EXTI3  */
	MNVIC_voidSetPriority(6 , 0b11110000);
	MNVIC_voidSetPriority(7 , 0b11000000);
	MNVIC_voidSetPriority(9 , 0b00000000);
	/**********************************************************/

	/*Enable EXTI0 and EXTI1 and EXTI3 by NVIC Controller*/
	MNVIC_voidEnableInterrupt(6);
	MNVIC_voidEnableInterrupt(7);
	MNVIC_voidEnableInterrupt(9);
	/**********************************************************/
	

	while(1)
	{


	}
	
	return 0;
}



void EXTI0_Func(void)
{

	while( MGPIO_u8GetPinValue(GPIOA,0)==LOW  )
	{
		MGPIO_VidSetPinValue(GPIOA , PIN2 , HIGH );
	}
	MGPIO_VidSetPinValue(GPIOA , PIN2 , LOW );


}
void EXTI1_Func(void)
{

	while( MGPIO_u8GetPinValue(GPIOA,1)==LOW  )
	{
		MGPIO_VidSetPinValue(GPIOA , PIN3 , HIGH );
	}
	MGPIO_VidSetPinValue(GPIOA , PIN3 , LOW );

}



void EXTI3_Func(void)
{


	while( MGPIO_u8GetPinValue(GPIOB,3)==LOW )
	{
		MGPIO_VidSetPinValue(GPIOB , PIN1 , HIGH );
	}

	MGPIO_VidSetPinValue(GPIOB , PIN1 , LOW );

}









