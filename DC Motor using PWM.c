
#include <stm32f407xx.h>

#define PWM_FREQUENCY 10000  // PWM frequency in Hz
#define MAX_DUTY_CYCLE 1000 // Max duty cycle value

void init_pwm() {
    // Enable GPIO clock for Port B
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    // Enable TIM2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;

    // Configure PB2 (TIM2_CH3) and PB10 (TIM2_CH3) as alternate function
    GPIOB->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER10_1; // Alternate function mode
    GPIOB->AFR[0] |= 0x01 << ((2 - 0) * 4); // AF1 (TIM2) for PB2
    GPIOB->AFR[1] |= 0x01 << ((10 - 8) * 4); // AF1 (TIM2) for PB10

    // Configure TIM2
    TIM2->PSC = (SystemCoreClock / PWM_FREQUENCY) - 1; // Prescaler
    TIM2->ARR = MAX_DUTY_CYCLE; // Auto-reload register
    TIM2->CCR3 = 0; // Initial duty cycle for CH3
    TIM2->CCR4 = 0; // Initial duty cycle for CH4

    // PWM mode 1, edge-aligned for CH3 and CH4
    TIM2->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2; // CH3
    TIM2->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2; // CH4
    TIM2->CCER |= TIM_CCER_CC3E; // Enable capture/compare channel 3
    TIM2->CCER |= TIM_CCER_CC4E; // Enable capture/compare channel 4

    // Main output enable
    TIM2->BDTR |= TIM_BDTR_MOE;

    // Counter enable
    TIM2->CR1 |= TIM_CR1_CEN;
}

void set_motor_speed(uint16_t duty_cycle) {
    if (duty_cycle > MAX_DUTY_CYCLE) {
        duty_cycle = MAX_DUTY_CYCLE;
    }

    // Update duty cycle for CH3 and CH4
    TIM2->CCR3 = duty_cycle; // For PB2
    TIM2->CCR4 = duty_cycle; // For PB10
}

int main(void) {
    // Initialize PWM
     init_pwm();

    while (1) {
        // Control motor speed by setting duty cycle
        // Example: set_motor_speed(500); // Sets duty cycle to 50%
        //          set_motor_speed(800); // Sets duty cycle to 80%
    }
}
