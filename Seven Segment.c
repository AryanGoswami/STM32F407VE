#include<stm32f407xx.h>

void delay(unsigned int time)
{
	int i, j;
	for(i=0; i<=time; i++)
	{
		for(j=0; j<=1275; j++);
	}
}

int main()
{
	RCC->AHB1ENR = 0x017;//PORT A,B,C,E

	GPIOA->MODER = 0x01100;//SEG_SEL_1,2 == PA4,PA6
	GPIOA->OTYPER = 0x00;
	GPIOA->PUPDR = 0x00;
	GPIOA->OSPEEDR= 0x00;

	GPIOB->MODER = 0x05000;//SEG_SEL_3,4 == PB6,PB7
	GPIOB->OTYPER = 0x00;
	GPIOB->PUPDR = 0x00;
	GPIOB->OSPEEDR= 0x00;

	GPIOC->MODER = 0x05000;//A,B == PC6, PC7
	GPIOC->OTYPER = 0x00;
	GPIOC->PUPDR = 0x00;
	GPIOC->OSPEEDR= 0x00;

	GPIOE->MODER = 0x0515;//C,D,E,F,G == PE0, PE1, PE2, PE4, PE5
	GPIOE->OTYPER = 0x00;
	GPIOE->PUPDR = 0x00;
	GPIOE->OSPEEDR= 0x00;

	GPIOA -> BSRR = 0x050;//first & second 7 segment
	GPIOB -> BSRR= 0x0C0;//third & fourth 7 segment

	int C[10] = {0xC0,0x80,0xC0,0xC0,0x80,0x40,0x40,0xC0,0xC0,0xC0};
	int E[10] = {0x17,0x01,0x26,0x23,0x31,0x33,0x37,0x01,0x37,0x33};
	while(1)
	{
		unsigned int k;
		for(k=0;k<10;k++){
			GPIOC -> ODR = C[k];
			GPIOE -> ODR = E[k];
			delay(500);
		}
	}
}
