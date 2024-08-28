#include<stm32f407xx.h>

int main(){
	RCC -> AHB1ENR = 1<<2;//PORT A,C
	GPIOC -> MODER = 0x01;//PC0
	RCC -> APB1ENR = 1<<0;//TIM2 Enable
	TIM2 -> PSC = 1600-1;//16000000/1600{PSC value from 1 to 65535}
	TIM2 -> ARR = 10000-1;//count till 10000{16-bit or 32-bit mode,depending on timer}
	TIM2 -> CNT = 0;
	TIM2 -> CR1 = 1;//counter
	while(1){
		while(!(TIM2 -> SR & 1)){}
		TIM2 -> SR &= ~1;//UIF cleared
		GPIOC -> ODR ^= 0x01;//toggle
	}
}