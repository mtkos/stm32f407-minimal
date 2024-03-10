.set TIM3_IRQn, 45
.section .init

.word _estack
.word prog
.skip 4*(TIM3_IRQn - 2)
.word TIM3_IRQHandler
