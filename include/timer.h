#define TIM3 0x40000400
#define   CR1 0x0
#define     CEN 1<<0
#define   DIER 0xc
#define     UDE 1<<8
#define     UIE 1<<0
#define   SR 0x10
#define   CCMR1 0x18
#define     OC1M_2 1<<6
#define     OC1M_1 1<<5
#define     OC1M_0 1<<4
#define     OC1PE 1<<3
#define   CCER 0x20
#define     CC1P 1<<1
#define     CC1E 1<<0
#define   CNT 0x24
#define   PSC 0x28
#define   ARR 0x2c
#define   CCR1 0x34
#define   CCR3 0x3c
