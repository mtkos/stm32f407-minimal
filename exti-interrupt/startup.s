.set EXTI3_IRQn, 25
.section .init

.word _estack
.word prog
.skip 4*(EXTI3_IRQn - 2)
.word EXTI3_IRQHandler
