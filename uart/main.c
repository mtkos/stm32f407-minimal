#include<stdint.h>

#include "../include/common.h"
#include "../include/flash.h"
#include "../include/rcc.h"
#include "../include/gpio.h"
#include "../include/uart.h"

#define BAUDRATE 921600
#define CLOCK_FREQUENCY 168000000
#define BAUD_REG CLOCK_FREQUENCY/BAUDRATE - 1

#define PIN9 9 //PA9 = TX
#define PIN10 10 //PA10 = RX

void prog(){

    REG(RCC + CFGR) = SW_PLL;
    REG(RCC + PLLCFGR) = PLLSRC | PLLM(8) | PLLN(336) | PLLP(0);

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

    while(1){
        while(!(REG(USART1 + SR) & RXNE));
        REG(USART1 + DR)++;
        while(!(REG(USART1 + SR) & TXE));
    }
}
