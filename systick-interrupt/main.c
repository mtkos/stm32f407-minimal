#include <stdint.h>

#include "../include/common.h"
#include "../include/scb.h"
#include "../include/rcc.h"
#include "../include/gpio.h"
#include "../include/systick.h"

#define CPU_FREQ 8000000

#define PIN6 6
#define PIN7 7

extern uint32_t _flash_base;

volatile uint8_t onoff[3];
volatile uint32_t period;

extern uint32_t _sidata, _sdata, _edata, _ebss, _sbss;

void SysTick_Handler() __attribute__((interrupt));

void SysTick_Handler(){

    REG(GPIOA + BSRR) = Pin(PIN6 + 16*onoff[1]);
    onoff[1] = 1 - onoff[1];
}

void flash_to_ram(){

    uint32_t *p_idata = &_sidata;

    for(uint32_t *p_data = &_sdata; p_data < &_edata; *p_data++ = *p_idata++);
    for(uint32_t *p_bss = &_sbss; p_bss < &_ebss; *p_bss++ = 0);

}

void inc(){

    period += 1000;
}

void prog(){

    flash_to_ram();

    REG(SCB + VTOR) = (uint32_t)&_flash_base;

    REG(RCC + AHB1ENR) = GPIOAEN;

    REG(GPIOA + MODER) = Output_Mode(PIN6) | Output_Mode(PIN7);

    REG(SysTick + STCVR) = 0;
    REG(SysTick + STRVR) = CPU_FREQ;
    REG(SysTick + STCSR) = CLKSOURCE | TICKINT | ENABLE;

    while(1){
        for(volatile uint32_t i = period; i > 0; i--);
        REG(GPIOA + BSRR) = Pin(PIN7 + 16*onoff[2]);
        onoff[2] = 1 - onoff[2];
        inc();
    };
}
