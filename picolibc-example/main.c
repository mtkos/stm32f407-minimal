#include <stdio.h>
#include <math.h>

#include "../include/common.h"
#include "../include/flash.h"
#include "../include/rcc.h"
#include "../include/gpio.h"
#include "../include/uart.h"
#include "../include/rng.h"

#define BAUDRATE 921600
#define CLOCK_FREQUENCY 168000000
#define BAUD_REG (CLOCK_FREQUENCY/BAUDRATE - 1)

#define PIN9 9
#define PIN10 10

int uart_putc(char c, FILE *file){

    REG(USART1 + DR) = c;
    while(!(REG(USART1 + SR) & TC));
    return c;
}

int uart_getc(FILE *file){

    unsigned char c;

    while(!(REG(USART1 + SR) & RXNE));
    c = REG(USART1 + DR);
    return c;
}

FILE __stdio = FDEV_SETUP_STREAM(uart_putc, uart_getc, NULL, _FDEV_SETUP_RW);

FILE *const stdin = &__stdio;
__strong_reference(stdin, stdout);
__strong_reference(stdin, stderr);

void uart_init(){

    REG(RCC + CFGR) = SW_PLL;
    REG(RCC + PLLCFGR) = PLLSRC | PLLM(8) | PLLN(336) | PLLP(0) | PLLQ(4); //HSE clock, system clock = 8MHz/8*336/2 = 168MHz

    REG(RCC + CR) = PLLON | HSEON;
    while(!(REG(RCC + CR) & PLLRDY));

    REG(RCC + AHB1ENR) = GPIOAEN;

    REG(GPIOA + MODER) |= AF_Mode(PIN9);
    REG(GPIOA + MODER) |= AF_Mode(PIN10);
    REG(GPIOA + AFRH) |= AFRH_VAL(PIN9, AF_USART1);
    REG(GPIOA + AFRH) |= AFRH_VAL(PIN10, AF_USART1);

    REG(RCC + APB2ENR) = USART1EN;

    REG(USART1 + BRR) = BAUD_REG;
    REG(USART1 + CR1) = TE | RE | UE;
}

void rng_init(){

    REG(RCC + AHB2ENR) = RCC_RNGEN;
    REG(RNG + CR) = RNGEN;
}

uint32_t rand(){

    while(!(REG(RNG + RNG_SR) & DRDY));
    if(REG(RNG + RNG_SR) & ~(DRDY))
        return 0;
    else
        return REG(RNG + RNG_DR);
}

void main(){

    uart_init();
    rng_init();

    while(1){
        getchar();
        printf("0x%08x\r\n", rand());
    }
}
