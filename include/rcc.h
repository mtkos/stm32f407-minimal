#define RCC 0x40023800
#define   CR 0x0
#define     PLLRDY 1<<25
#define     PLLON 1<<24
#define     HSEON 1<<16
#define   PLLCFGR 0x4
#define     PLLQ(x) ((x)<<24)
#define     PLLP(x) ((x)<<16)
#define     PLLN(x) ((x)<<6)
#define     PLLM(x) (x)
#define   CFGR 0x8
#define     HPRE_Reset_Mask 0xFFFFFF0F
#define     HPRE_DIV1 0
#define     PLLSRC 1<<22
#define     SW_PLL 0x2
#define     SW_HSE 0x1
#define   AHB1ENR 0x30
#define     DMA1EN 1<<21
#define     GPIOEEN 1<<4
#define     GPIODEN 1<<3
#define     GPIOCEN 1<<2
#define     GPIOBEN 1<<1
#define     GPIOAEN 1<<0
#define   AHB2ENR 0x34
#define   APB1ENR 0x40
#define     TIM3EN 1<<1
#define   APB2ENR 0x44
#define     SYSCFGEN 1<<14
#define     USART1EN 1<<4
