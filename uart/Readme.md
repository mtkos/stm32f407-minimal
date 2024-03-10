# the uart program

This program uses the (maximum for this chip) CPU frequency of 168MHz. Configuration is done using the (in my board 8MHz) external oscillator, combined with the PLL. PLL configuration is
easier and more flexible than for the STM32F103. The PLL has its own configuration register, PLLCFGR. It is documented in section 7.3.2 of [RM0090]. Configuration is done as follows:

1. Set the PLLSRC bit to 1 to use the HSE oscillator as PLL input.

2. Set the PLLM bits. They define a factor by which the input clock is divided. The divided clock should be between 1 and 2 MHz, so in our case a factor of 8 will do.

3. Set the PLLP bits. They again define a factor by which the input clock is divided. The smallest possible factor is 2, which we use.

4. Finally, set the PLLN bits. They multiply the frequency from the preceding steps. To get 168MHz we set them to 336.

Caution: not all combinations of PLLM, PLLN and PLLP are allowed.
