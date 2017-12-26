// File:  project.c
// Author: JS
// Date:  10/4/17
// Purpose: SPI experiment
// Hardware:  TM4C123 Tiva board

#include "HAL.h"

volatile uint32_t* SW1;
volatile uint32_t* SW2;


void InitHardware()
{
	__disable_irq();
	
	PLL_Init80MHz();

	GPIO_InitPort(PORTF);
	GPIO_EnableDI(PORTF, PIN_0 | PIN_4, PULL_UP);
	
	SPI_Enable(SSI1);

	SysTick_Init();
	
	SW1 = &PF4;
	SW2 = &PF0;
	
	__enable_irq();
	
}


int main()
{

	uint8_t counter = 0;
	uint8_t value = 0;
	uint8_t display = 3;
	uint8_t toggler = 0xAA;
	
	InitHardware();

	while (1) 
	{			
		
//		// If both switches are pressed, hold the current value.
//		if (!(*SW1 == 0 && *SW2 == 0)) {
//		
//			if (*SW1 == 0) {
//				// Toggle pattern.
//				value = toggler;	// Shift pattern
//			}
//			else if (*SW2 == 0) {
//				// Counting pattern
//				value = counter;
//			}
//			else {
//				value = 0x1 << (counter % 8);
//			}
//	
//		}
	
		//display = (display + 1) % 4;
		display = 3; //(display + 1) % 4;
		
		
		// Serialize the value...
		value = (0x1 << (display + 4)) | 0x8; 
		SPI_Write(SSI1, value);
			
		// Wait ...
		SysTick_Wait10us(500);

		value = 0x0F; 
		//SPI_Write(SSI1, value);


		counter++;
		toggler = ~toggler;
		
	}
	
}