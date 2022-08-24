#include "../include/sys_init.h"
#include "../arch/stm32f446re/include/dev/clock.h"
#include "../arch/stm32f446re/include/dev/usart.h"
#include "../arch/stm32f446re/include/dev/gpio.h"


typedef struct {
	uint32_t CPUID;
	uint32_t ICSR;
	uint32_t VTOR;
	uint32_t AIRCR;
	uint32_t SCR;
	uint32_t CCR;
	uint32_t SHPR1;
	uint32_t SHPR2;
	uint32_t SHPR3;
	uint32_t SHCSR;
	uint32_t CFSR;
	uint32_t HFSR;
	uint32_t MMAR;
	uint32_t BFAR;
	uint32_t AFSR;
	uint8_t reserved[76];
	uint32_t CPACR;
}SCB_type;
#define SCB ((SCB_type *) 0xE000ED00 )

//turn on the fpu
void DRV_FPU_ACTIVE(void) {
	SCB->CPACR |= ((3UL << 10 * 2) | (3UL << 11 * 2));
}

void __sys_init(void) {
	DRV_CLOCK_INIT(); //configure system clock 180 MHz
	DRV_GPIO_INIT(GPIOA);
	DRV_USART_INIT(USART2); //configure as standard input and output
	DRV_FPU_ACTIVE();
}
