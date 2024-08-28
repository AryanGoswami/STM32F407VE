#include "stm32f4xx.h"
#include<stdio.h>

int _write(int file, char *ptr, int len){
	int DataIdx;

	for(DataIdx = 0;DataIdx<len;DataIdx++){
		ITM_SendChar(*ptr++);
	}

	return len;
}

int main (void) {
	int result;
/* set up pin PA5 for LED */
	RCC->AHB1ENR |= 1; /* enable GPIOA clock */
	GPIOA->MODER &=~0x00000C00; /* clear pin mode */
	GPIOA->MODER |= 0x00000400; /* set
	pin to output mode */
	/* set up pin PA1 for analog input */
	RCC->AHB1ENR |= 5; /* enable GPIOA clock */
	GPIOA->MODER |= 0xC; /*
	PA1 analog */
	GPIOC->MODER |=1;
	/* setup ADC1 */
	RCC->APB2ENR |= 0x00000100; /* enable ADC1 clock */
	ADC1->CR2 = 0; /* SW trigger */
	ADC1->SQR3 = 1; /* conversion sequence starts at ch 1 */
	ADC1->SQR1 = 0; /* conversion sequence length 1 */
	ADC1->CR2 |= 1; /* enable
	ADC1 */
	while (1) {
		ADC1->CR2 |= 0x40000000; /* start a conversion */
		while(!(ADC1->SR &2)) {} /* wait for conv complete */
		result = ADC1->DR; /* read
		conversion result */
		if (result & 0x100)
			GPIOC->BSRR = 1<<0; /* turn on LED */
		else
			GPIOC->BSRR = 1<<16; /* turn off LED */
		printf("Result- %d \n",result);
	}
}
