CC = arm-none-eabi-gcc
CFLAGS = -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -O0
LFLAGS = -nostdlib  -T kern/asst01/stm32_ls.ld -Wl,-Map=$(OUTPUT_FOLDER)/final.map
MACH = cortex-m4
OUTPUT_FOLDER = build


all:kern_kstdio_kstdio.o kern_kmain_kmain.o kern_kmain_sys_init.o kern_arch_stm32f446re_dev_clock.o kern_arch_stm32f446re_dev_gpio.o kern_arch_stm32f446re_dev_usart.o kern_arch_stm32f446re_dev_timer.o kern_arch_stm32f446re_sys_stm32_startup.o final.elf

final.elf:kern_kstdio_kstdio.o kern_kmain_kmain.o kern_kmain_sys_init.o kern_arch_stm32f446re_dev_clock.o kern_arch_stm32f446re_dev_gpio.o kern_arch_stm32f446re_dev_usart.o kern_arch_stm32f446re_dev_timer.o kern_arch_stm32f446re_sys_stm32_startup.o 
	$(CC) $(LFLAGS) $(OUTPUT_FOLDER)/*.o  -o $(OUTPUT_FOLDER)/$@


kern_kstdio_kstdio.o:kern/kstdio/kstdio.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^

kern_kmain_kmain.o:kern/kmain/kmain.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^

kern_kmain_sys_init.o:kern/kmain/sys_init.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^

kern_arch_stm32f446re_dev_clock.o:kern/arch/stm32f446re/dev/clock.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^

kern_arch_stm32f446re_dev_gpio.o:kern/arch/stm32f446re/dev/gpio.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^

kern_arch_stm32f446re_dev_usart.o:kern/arch/stm32f446re/dev/usart.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^

kern_arch_stm32f446re_dev_timer.o:kern/arch/stm32f446re/dev/timer.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^

kern_arch_stm32f446re_sys_stm32_startup.o:kern/arch/stm32f446re/sys/stm32_startup.c
	$(CC) $(CFLAGS) -o $(OUTPUT_FOLDER)/$@ $^



clean-windows:
	@del /s *.o *.elf *.map

load:
	openocd -f board/stm32f4discovery.cfg