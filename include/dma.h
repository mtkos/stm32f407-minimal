#define DMA1 0x40026000
#define   LIFCR 0x8
#define     CTCIF2 1<<21
#define   S2CR 0x40
#define     CHSEL(x) ((x)<<25)
#define     MSIZE16 1<<13
#define     PSIZE16 1<<11
#define     MINC 1<<10
#define     DIR 1<<6
#define     EN 1<<0
#define   S2NDTR 0x44
#define   S2PAR 0x48
#define   S2M0AR 0x4c
