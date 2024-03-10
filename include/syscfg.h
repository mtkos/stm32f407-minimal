#define SYSCFG 0x40013800
#define   EXTICR1 0x8
#define     PA_Exti(x) (0b0<<(4*(x)))
#define     PB_Exti(x) (0b1<<(4*(x)))
#define     PE_Exti(x) (0b100<<(4*(x)))
