#include <stdint.h>

#include "../include/common.h"
#include "../include/rcc.h"
#include "../include/gpio.h"
#include "../include/timer.h"

#define PIN6 6

#define CPU_FREQ 16000000
#define CNT_MAX 0xffff
#define PRESCALER_VALUE (CPU_FREQ/CNT_MAX - 1)

void prog(){

    REG(RCC + AHB1ENR) = GPIOAEN;
    REG(RCC + APB1ENR) = TIM3EN;

    REG(GPIOA + MODER) = AF_Mode(PIN6);
    REG(GPIOA + AFRL) = AFRL_VAL(PIN6, AF_TIM3);

    REG(TIM3 + CCER) = CC1P | CC1E;
    REG(TIM3 + CCMR1) = OC1M_2 | OC1M_1;
    REG(TIM3 + CCR1) = CNT_MAX/10;

    REG(TIM3 + PSC) = PRESCALER_VALUE;
    REG(TIM3 + CR1) = CEN;

    while(1){
        __asm__ volatile("wfi");
    }
}
