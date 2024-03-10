#include <stdint.h>

#include "../include/common.h"
#include "../include/scb.h"
#include "../include/nvic.h"
#include "../include/rcc.h"
#include "../include/gpio.h"
#include "../include/timer.h"

#define TIM3_IRQn 29

#define PIN6 6

#define CPU_FREQ 16000000
#define CNT_MAX 0xffff
#define PRESCALER_VALUE (CPU_FREQ/CNT_MAX - 1)

extern uint32_t _flash_base;

void TIM3_IRQHandler() __attribute__((interrupt));

void TIM3_IRQHandler(){

    REG(TIM3 + SR) = 0;
}

void prog(){

    REG(SCB + VTOR) = (uint32_t)&_flash_base;

    REG(RCC + AHB1ENR) = GPIOAEN;
    REG(RCC + APB1ENR) = TIM3EN;

    REG(GPIOA + MODER) = Output_Mode(PIN6);

    REG(TIM3 + PSC) = PRESCALER_VALUE;

    REG(TIM3 + DIER) = UIE;
    REG(NVIC + ISER0) = 1<<TIM3_IRQn;

    REG(TIM3 + CR1) = CEN;

    while(1){
        __asm__ volatile ("wfi");
        REG(GPIOA + ODR) ^= Pin(PIN6);
    }
}
