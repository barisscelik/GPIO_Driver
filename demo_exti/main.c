/*
 * main.c
 * Created on Sun May 16 2021
 * Copyright (c) ERARGE
 * Author : Baris Celik
 */

#include "hardware_layer.h"

volatile _Bool intFlag = FALSE;

void periphConfig()
{
	GPIO_TYPE gpioLedBlue;
	GPIO_TYPE gpioLedRed;
	
	gpioLedBlue.port = PORTB;
	gpioLedBlue.pin = Pin_Number_7;
	gpioLedBlue.mode = OUTPUT_MODE;
	gpioLedBlue.mode_type = OUTPUT_PP;
	gpioLedBlue.pptype = NO_PULL;
	gpioLedBlue.speed = SPEED_HIGH;
	
	HL_IO_Init(gpioLedBlue);
	
	gpioLedRed.port = PORTB;
	gpioLedRed.pin = Pin_Number_14;
	gpioLedRed.mode = OUTPUT_MODE;
	gpioLedRed.mode_type = OUTPUT_PP;
	gpioLedRed.pptype = NO_PULL;
	gpioLedRed.speed = SPEED_HIGH;
	
	HL_IO_Init (gpioLedRed);
}

void intConfig()
{
	configInterrupt(PORTC, Pin_Number_13, RISING_EDGE);
	
	interruptEnable(Pin_Number_13, EXTI15_10_IRQn);
}

int main()
{
	periphConfig();
	
	intConfig();
	
	pinWrite(PORTB,Pin_Number_7,HIGH);
	
	
	while(1)
	{
		if(intFlag)
		{
			pinToggle(PORTB, Pin_Number_7);
			pinToggle(PORTB, Pin_Number_14);
		
			HL_Delay();
			
			intFlag = FALSE;
		}
	}

}


//interrrupt handler callback function
void EXTI15_10_IRQHandler()
{
	intFlag = TRUE;
	
	interruptClear(Pin_Number_13);
}
