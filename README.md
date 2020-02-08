# W5500 LwIp binding #

W5500 is used in MAC RAW mode.
Hardware address filtering is switched off (this important if you are intended to use it as one of bridge interfaces)
Interrupts are used only for RECV signal.
Uses FreeRTOS. Tested with STM32.

## How to use ##

1. Patch your LwIp tree with files from `external_libs/lwip/port/FreeRTOS` folder
2. Implement your low level init (SPI, GPIO, NVIC, clocks, etc.) and low level IO functions in `device/wizchip/wizchip_port.c`
3. Check interrupt handler example in `app/interrupts.c`. Change in accordance with your platform and GPIO setup (i.e. external interrupt number and so on)
4. Call `lwipInit()` in your main function.