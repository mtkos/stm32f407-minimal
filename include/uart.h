#define USART1 0x40011000
#define   SR 0x0
#define     TXE 1<<7
#define     TC 1<<6
#define     RXNE 1<<5
#define   DR 0x4
#define   BRR 0x8
#define   CR1 0xc
#define     UE 1<<13
#define     TE 1<<3
#define     RE 1<<2