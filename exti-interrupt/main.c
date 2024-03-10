#include <stdint.h>

#include "../include/common.h"
#include "../include/scb.h"
#include "../include/nvic.h"
#include "../include/syscfg.h"
#include "../include/rcc.h"
#include "../include/gpio.h"
#include "../include/exti.h"

#define EXTI3_IRQn 9

#define PIN3 3
#define PIN6 6

extern uint32_t _flash_base;

void EXTI3_IRQHandler() __attribute__((interrupt));

void EXTI3_IRQHandler(){

    REG(EXTI + PR) = Pin(PIN3);
}

void prog(){

    REG(SCB + VTOR) = (uint32_t)&_flash_base;

    REG(RCC + AHB1ENR) = GPIOAEN | GPIOEEN;
    REG(RCC + APB2ENR) = SYSCFGEN;

    REG(GPIOE + MODER) = Input_Mode(PIN3);
    REG(GPIOE + PUPDR) |= PU(PIN3);

    REG(GPIOA + MODER) |= Output_Mode(PIN6);

    REG(SYSCFG + EXTICR1) = PE_Exti(PIN3);
    REG(EXTI + IMR) = Pin(PIN3);
    REG(EXTI + FTSR) = Pin(PIN3);

    REG(NVIC + ISER0) = 1<<EXTI3_IRQn;

    while(1){
        __asm__ volatile("wfi");
        REG(GPIOA + ODR) ^= Pin(PIN6);
    }
}
