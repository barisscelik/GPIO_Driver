#ifndef HARDWARE_LAYER
#define HARDWARE_LAYER

#include "stm32f429xx.h"                 // Device header
#include "RTE_Components.h"             // Component selection


#define LOW				0
#define HIGH				1

#define FALSE				0
#define TRUE				1

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;
typedef	int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

#define PORTA		GPIOA
#define PORTB		GPIOB
#define PORTC		GPIOC
#define PORTD		GPIOD
#define PORTE		GPIOE
#define PORTF		GPIOF
#define PORTG		GPIOG
#define PORTH		GPIOH
#define PORTI		GPIOI

#define Pin_Number_0			0		
#define Pin_Number_1			1	
#define Pin_Number_2			2	
#define Pin_Number_3			3	
#define Pin_Number_4			4
#define Pin_Number_5			5
#define Pin_Number_6			6	
#define Pin_Number_7			7	
#define Pin_Number_8			8	
#define Pin_Number_9			9	
#define Pin_Number_10			10	
#define Pin_Number_11			11	
#define Pin_Number_12			12	
#define Pin_Number_13			13	
#define Pin_Number_14			14
#define Pin_Number_15			15


//PIN MODES
#define INPUT_MODE			((u32) 0x00)
#define OUTPUT_MODE			((u32) 0x01)
#define ALTERNATE_FUNCTION_MODE		((u32) 0x02)
#define ANALOG_MODE			((u32) 0x03)

//OUTPUT MODE TYPE
#define OUTPUT_PP			((u32) 0x00)
#define OUTPUT_OD			((u32) 0x01)

//PUSH PULL TYPE
#define NO_PULL				((u32) 0x00)
#define PULL_UP				((u32) 0x01)
#define PULL_DOWN			((u32) 0x02)

//PIN SPEED SLOW RATE
#define SPEED_LOW			((u32) 0x00)
#define SPEED_MEDIUM			((u32) 0x01)
#define SPEED_HIGH			((u32) 0x02)
#define SPEED_VERY_HIGH			((u32) 0x03)

//CLOCK ENABLING
#define GPIO_CLK_ENABLE_PORTA			(RCC->AHB1ENR |= (1U<<0))
#define GPIO_CLK_ENABLE_PORTB			(RCC->AHB1ENR |= (1U<<1))
#define GPIO_CLK_ENABLE_PORTC			(RCC->AHB1ENR |= (1U<<2))
#define GPIO_CLK_ENABLE_PORTD			(RCC->AHB1ENR |= (1U<<3))
#define GPIO_CLK_ENABLE_PORTE			(RCC->AHB1ENR |= (1U<<4))
#define GPIO_CLK_ENABLE_PORTF			(RCC->AHB1ENR |= (1U<<5))
#define GPIO_CLK_ENABLE_PORTG			(RCC->AHB1ENR |= (1U<<6))
#define GPIO_CLK_ENABLE_PORTH			(RCC->AHB1ENR |= (1U<<7))
#define GPIO_CLK_ENABLE_PORTI			(RCC->AHB1ENR |= (1U<<8))
#define SYSCFG_CLK_ENABLE			(RCC->APB2ENR |= (1U<<14))

//EXTI DEFINATION
#define EXTI_PORTA		 ((u32) 0b1111)
#define EXTI_PORTB 		 ((u32) 0b0001)
#define EXTI_PORTC    		 ((u32) 0b0010)
#define EXTI_PORTD 		 ((u32) 0b0011)
#define EXTI_PORTE		 ((u32) 0b0100)
#define EXTI_PORTF		 ((u32) 0b0101)
#define EXTI_PORTG		 ((u32) 0b0110)
#define EXTI_PORTH		 ((u32) 0b0111)
#define EXTI_PORTI		 ((u32) 0b1000)


//Configuration Structure
typedef struct
{
	GPIO_TypeDef *port;
	
	u32 pin;
	
	u32 mode;
	
	u32 mode_type;
	
	u32 pptype;
	
	u32 speed;
	
	u32 alt_func;

}GPIO_TYPE;

typedef enum
{
	RISING_EDGE,
	FALLING_EDGE,
	RISING_FALLING_EDGE
}edge_t;

//Function Prototypes
/*========================================================================
				GPIO CONFIGURATION
==========================================================================*/

static void configMode(GPIO_TypeDef *port, u32 pinNumber, u32 mode);

static void configModeType(GPIO_TypeDef *port, u32 pinNumber, u32 mode_type, u32 mode);

static void configPPType(GPIO_TypeDef *port, u32 pinNumber, u32 mode_type, u32 mode, u32 pptype);

static void configSpeed(GPIO_TypeDef *port, u32 pinNumber, u32 speed, u32 mode);

void HL_IO_Init(GPIO_TYPE gpio_type);

/*========================================================================
			GPIO USER PIN FUNCTIONS
==========================================================================*/

void pinWrite(GPIO_TypeDef *port, u32 pinNumber, _Bool pinState);

void pinToggle(GPIO_TypeDef *port, u32 pinNumber);

void HL_Delay();

/*========================================================================
				GPIO INTERRUPT
==========================================================================*/

void configInterrupt(GPIO_TypeDef *port, u32 pinNumber, edge_t edge);
void interruptEnable(u32 pinNumber, IRQn_Type irqNumber);
void interruptClear(u32 pinNumber);

#endif
