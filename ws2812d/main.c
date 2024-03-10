#include <stdint.h>

#include "../include/common.h"
#include "../include/rcc.h"
#include "../include/dma.h"
#include "../include/gpio.h"
#include "../include/timer.h"

extern uint32_t _sidata, _sdata, _edata, _ebss, _sbss;

void flash_to_ram(){

    uint32_t *p_idata = &_sidata;

    for(uint32_t *p_data = &_sdata; p_data < &_edata; *p_data++ = *p_idata++);
    for(uint32_t *p_bss = &_sbss; p_bss < &_ebss; *p_bss++ = 0);
}

#define BIT0 4 //16MHzclock -> 0.25 us high
#define BIT1 16 //1 us high
#define CNT_MAX 20 //1.25 us total pulse length
#define NUM_LEDS 3
#define SIZE NUM_LEDS*24 + 1

uint16_t bits[SIZE];

void set_pixel(int led, uint32_t rgb){

    uint32_t bit;
    int i;

    i = 24*led;
    for(bit = 1<<23; bit; bit >>= 1)
        bits[i++] = (rgb & bit) ? BIT1 : BIT0;
}

#define PIN6 6

void init_clocks(){

    REG(RCC + APB1ENR) = TIM3EN;
    REG(RCC + AHB1ENR) = GPIOCEN | DMA1EN;
}

void dma_init(){

    REG(DMA1 + S2PAR) = TIM3 + CCR1;
    REG(DMA1 + S2M0AR) = (uint32_t)bits;
    REG(DMA1 + S2CR) = CHSEL(5) | MSIZE16 | PSIZE16 | MINC | DIR;
}

void timer_init(){

    REG(GPIOC + MODER) = AF_Mode(PIN6);
    REG(GPIOC + PUPDR) = PU(PIN6);
    REG(GPIOC + AFRL) = AFRL_VAL(PIN6, AF_TIM3);

    REG(TIM3 + CCER) = CC1E;
    REG(TIM3 + CCMR1) = OC1M_2 | OC1M_1 | OC1PE;

    REG(TIM3 + ARR) = CNT_MAX;

    REG(TIM3 + DIER) = UDE;
    REG(TIM3 + CR1) =  CEN;
}

void send_bits(){

    REG(DMA1 + LIFCR) = CTCIF2;
//    REG(DMA1 + S2CR) &= ~(EN);
    REG(DMA1 + S2NDTR) = SIZE;
    REG(DMA1 + S2CR) |= EN;
}

uint32_t colors[NUM_LEDS] = {0x080000, 0x000800, 0x000008};

void cycle(){

    uint32_t c = colors[0];
    for(int i = 0; i < NUM_LEDS - 1; i++)
        colors[i] = colors[i + 1];
    colors[NUM_LEDS - 1] = c;
}

void prog(){

    flash_to_ram();
    init_clocks();
    dma_init();
    timer_init();

    while(1){
        for(int i = 0; i < NUM_LEDS; i++)
            set_pixel(i, colors[i]);
        send_bits();
        cycle();
        for(uint32_t i = 5000000; i; i--);
    }
}
