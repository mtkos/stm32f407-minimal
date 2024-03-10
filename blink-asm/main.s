.set RCC, 0x40023800
.set AHB1ENR, 0x30
.set GPIOAEN, 1<<0
.set GPIOA, 0x40020000
.set MODER, 0x0
.set ODR, 0x14
.set PIN, 6
.set Output_Mode, (0x1<<(2*PIN))

.word _estack
.word prog + 1

prog:
ldr r0, = RCC
mov r1, # GPIOAEN
str r1, [r0, # AHB1ENR]

ldr r0, = GPIOA
ldr r1, = Output_Mode
str r1, [r0, # MODER]

1:
ldr r1, = (1<<PIN)
ldr r2, [r0, # ODR]
eor r2, r1
str r2, [r0, # ODR]

ldr r1, = 1000000
2:
sub r1, # 1
cmp r1, # 0
bne 2b

b 1b
