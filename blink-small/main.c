#include<stdint.h>

#include "../include/common.h"
#include "../include/rcc.h"
#include "../include/gpio.h"

#define PIN 6

void prog(){
    REG(RCC + AHB1ENR) = GPIOAEN;

    REG(GPIOA + MODER) = Output_Mode(PIN);

    while(1){
        for(int i = 1000000; i; i--);
        REG(GPIOA + ODR) ^= Pin(PIN);
    }
}
