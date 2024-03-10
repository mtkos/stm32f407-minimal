TARGET = picolibc-example

SRC = main.c

include ../build.mk

FLAGS = -Os -specs=picolibc.specs -mcpu=cortex-m4 -DPICOLIBC_INTEGER_PRINTF_SCANF -T../ld/Link-pico.ld
