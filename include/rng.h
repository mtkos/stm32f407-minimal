#define RNG 0x50060800
#define   RNG_CR 0x0
#define     RNGEN 1<<2
#define   RNG_SR 0x4
#define     SECS 1<<2
#define     CECS 1<<1
#define     DRDY 1<<0
#define   RNG_DR 0x8
#define   RCC_RNGEN 1<<6