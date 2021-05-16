/*
 * hardware_layer.c
 * Created on Sun May 16 2021
 * Copyright (c) ERARGE
 * Author : Baris Celik
 */

#include "hardware_layer.h"

// Pin position for external interrupt config
u32 PIN_POS[16] =
{
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x00),
	(0x04),
	(0x08),
	(0x0C),
	(0x00),
	(0x04),
	(0x08),
	(0x0C)
};
	
static void configMode(GPIO_TypeDef *port, u32 pinNumber, u32 mode)
{
	 u32 new_pinNum = 2* pinNumber;
	
	switch(mode)
	{
		case INPUT_MODE:
			port ->MODER &=  ~(3U << new_pinNum);
			break;
		
		case OUTPUT_MODE:
			port ->MODER |= (OUTPUT_MODE << new_pinNum);
			break;
		
		case ALTERNATE_FUNCTION_MODE:
			port ->MODER |= (ALTERNATE_FUNCTION_MODE << new_pinNum);
			break;
		
		case ANALOG_MODE:
			port -> MODER |= (ANALOG_MODE << new_pinNum);
			break;
	}//end switch

}

static void configModeType(GPIO_TypeDef *port, u32 pinNumber, u32 mode_type, u32 mode)
{
	if(mode == OUTPUT_MODE)
	{
		switch(mode_type)
		{
			case OUTPUT_PP:
				port ->OTYPER &= ~(1U << pinNumber);
				break;
		
			case OUTPUT_OD:
				port ->OTYPER |= (OUTPUT_OD << pinNumber);
				break;
		}//end switch
	}
	else
		return;
}


static void configPPType(GPIO_TypeDef *port, u32 pinNumber, u32 mode_type, u32 mode, u32 pptype)
{
	u32 new_pinNum = 2 * pinNumber;
	
	if(mode == OUTPUT_MODE && mode_type == OUTPUT_PP)
	{
		switch(pptype)
		{
			case NO_PULL:
				port ->PUPDR &=  ~(3U << new_pinNum);
				break;
		
			case PULL_UP:
				port ->PUPDR |= (PULL_UP << new_pinNum);
				break;
		
			case PULL_DOWN:
				port ->PUPDR |= (PULL_DOWN << new_pinNum);
				break;
		}//end switch
	}
	
	else
		return;
}

static void configSpeed(GPIO_TypeDef *port, u32 pinNumber, u32 speed, u32 mode)
{
	u32 new_pinNum = 2 * pinNumber;
	
	if(mode == OUTPUT_MODE)
	{
		switch(speed)
		{
			case SPEED_LOW:
				port ->OSPEEDR &=  ~(3U << new_pinNum);
				break;
		
			case SPEED_MEDIUM:
				port ->OSPEEDR |= (SPEED_MEDIUM << new_pinNum);
				break;
		
			case SPEED_HIGH:
				port ->OSPEEDR |= (SPEED_HIGH << new_pinNum);
				break;
		
			case SPEED_VERY_HIGH:
				port -> OSPEEDR |= (SPEED_VERY_HIGH << new_pinNum);
				break;
		}//end switch
	}
	else
	{
		return;
	}
}
	

void pinWrite(GPIO_TypeDef *port, u32 pinNumber, _Bool pinState)
{
	if(pinState)
	{
		port ->BSRR = (1U << pinNumber);
	}
	else
	{
		port ->BSRR = (1U << (pinNumber+16));
	}
}
	
void pinToggle(GPIO_TypeDef *port, u32 pinNumber)
{
	port ->ODR ^= (1U << pinNumber);
}

void HL_Delay()
{
	u32 time_index = INT16_MAX << 3;
	
	while(--time_index);
}

void HL_IO_Init(GPIO_TYPE gpio_type)
{
	if(gpio_type.port == PORTA)
	{
		GPIO_CLK_ENABLE_PORTA;
	}
	else if(gpio_type.port == PORTB)
	{
		GPIO_CLK_ENABLE_PORTB;
	}
	else if(gpio_type.port == PORTC)
	{
		GPIO_CLK_ENABLE_PORTC;
	}
	else if(gpio_type.port == PORTD)
	{
		GPIO_CLK_ENABLE_PORTD;
	}
	else if(gpio_type.port == PORTE)
	{
		GPIO_CLK_ENABLE_PORTE;
	}
	else if(gpio_type.port == PORTF)
	{
		GPIO_CLK_ENABLE_PORTF;
	}
	else if(gpio_type.port == PORTG)
	{
		GPIO_CLK_ENABLE_PORTG;
	}
	else if(gpio_type.port == PORTH)
	{
		GPIO_CLK_ENABLE_PORTH;
	}
	else if(gpio_type.port == PORTI)
	{
		GPIO_CLK_ENABLE_PORTI;
	}
	
	configMode(gpio_type.port, gpio_type.pin, gpio_type.mode);

	configModeType(gpio_type.port, gpio_type.pin, gpio_type.mode_type, gpio_type.mode);

	configPPType(gpio_type.port, gpio_type.pin, gpio_type.mode_type, gpio_type.mode, gpio_type.pptype);

	configSpeed(gpio_type.port, gpio_type.pin, gpio_type.speed, gpio_type.mode);
	
}

void configInterrupt(GPIO_TypeDef *port, u32 pinNumber, edge_t edge)
{
	
	SYSCFG_CLK_ENABLE;	// SYSTEM CONFIG clock enable
	
/*************************************************************************
				EXTI CONFIGURATION
*************************************************************************/
	if(port == PORTA)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] &= ~(EXTI_PORTA << PIN_POS[pinNumber]);
			break;
		}//end switch
	}// port A
	
	else if(port == PORTB)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTB << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTB << PIN_POS[pinNumber]);
			break;
		}//end switch
	}// port B
	
	else if(port == PORTC)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTC << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTC << PIN_POS[pinNumber]);
			break;
		}// end switch
	}// port C
	
	else if(port == PORTD)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTD << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTD << PIN_POS[pinNumber]);
			break;
		}// end switch
	}// port D
	
	else if(port == PORTE)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTE << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTE << PIN_POS[pinNumber]);
			break;
		}// end switch
	}// port E
	
	else if(port == PORTF)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTF << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTF << PIN_POS[pinNumber]);
			break;
		}/*end switch*/
	}// port F
	
	else if(port == PORTG)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTG << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTG << PIN_POS[pinNumber]);
			break;
		}// end switch
	}// port G
	
	else if(port == PORTH)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTH << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTH << PIN_POS[pinNumber]);
			break;
		}// end switch
	}// port H
	
	else if(port == PORTI)
	{
		switch(pinNumber)
		{
			case 0:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 1:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 2:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 3:
				SYSCFG ->EXTICR[0] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 4:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 5:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 6:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTI << PIN_POS[pinNumber]);			
			break;
			
			case 7:
				SYSCFG ->EXTICR[1] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 8:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 9:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 10:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 11:
				SYSCFG ->EXTICR[2] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 12:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 13:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 14:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
			
			case 15:
				SYSCFG ->EXTICR[3] |= (EXTI_PORTI << PIN_POS[pinNumber]);
			break;
		}// end switch
	}// port I
	
//********************************************************************************
	
//***************************EXTI TYPE CONFIGURATION******************************
	
	switch(edge)
	{
		case RISING_EDGE:
			EXTI ->RTSR |= (1U << pinNumber);
		break;
		
		case FALLING_EDGE:
			EXTI->FTSR |= (1U << pinNumber);
		break;
		
		case RISING_FALLING_EDGE:
			EXTI ->RTSR |= (1U << pinNumber);
			EXTI->FTSR |= (1U << pinNumber);
		break;
	}
//***********************************************************************************
}

void interruptEnable(u32 pinNumber, IRQn_Type irqNumber)
{
	//Enable interrupt in EXTI
	EXTI ->IMR |= (1U << pinNumber);
	
	//Enable interrupt in NVIC
	NVIC_EnableIRQ(irqNumber);
	
}


void interruptClear(u32 pinNumber)
{
	//This bit is cleared by programming it to 1. 
	EXTI ->PR |= (1U << pinNumber);
	
}
	

