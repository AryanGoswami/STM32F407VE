#include<stm32f407xx.h>

void delay(unsigned int time)
{
	int i, j;
	for(i=0; i<=time;i++)
	{
		for(j= 0; j<=1275; j++)
		{

		}
	}
}

int main()
{
	RCC->AHB1ENR=0x00000016;//PORT B,C,E for LEDs on board
	GPIOC->MODER = 0x051;PC0, PC2,PC3
	GPIOC->OTYPER = 0x00;
	GPIOC->PUPDR = 0x00;
	GPIOC->OSPEEDR= 0x00;

	GPIOB->MODER = 0x0100015;PB0,PB1,PB2,PB10
	GPIOB->OTYPER = 0x00;
	GPIOB->PUPDR = 0x00;
	GPIOB->OSPEEDR= 0x00;

	GPIOE->MODER = 0x040;PE3
	GPIOE->OTYPER = 0x00;
	GPIOE->PUPDR = 0x00;
	GPIOE->OSPEEDR= 0x00;

	while(1)
	{
		GPIOC->BSRR = 0x0000000D;//1<<x
		GPIOB->BSRR = 0x00000407;
		GPIOE->BSRR = 0x00000008;
		delay(200);
		GPIOC->BSRR = 0x000D0000;//1<<(x+16)
		GPIOB->BSRR = 0x04070000;
		GPIOE->BSRR = 0x00080000;
		delay(200);
	}
}
