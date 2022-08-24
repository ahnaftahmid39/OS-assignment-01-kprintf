#include "../include/sys_init.h"
#include "../include/kmain.h"
#include "../include/kstdio.h"
#include <stdint.h>

void newline(void) { kprintf((uint8_t*)"%c", (uint8_t*)"\n"); }

void kmain(void) {
	__sys_init();

	float f = -3.1416;
	uint32_t dec = -2000;
	uint32_t hex = -0x2ff;
	char c = 'k';

	// note: char *str will not work for kscanf bcz you can't change
	// its value in fucntion, you have to use char**
	// ref: https://stackoverflow.com/questions/41526782/can-i-change-an-initialized-char-pointer-via-function
	char str[] = "Hello world!";

	kprintf((uint8_t*)"%s", (uint8_t*)"<<---Testing printf---->>\n\n");
	kprintf((uint8_t*)"%s", (uint8_t*)"String: ");
	kprintf((uint8_t*)"%s", (uint8_t*)str);
	newline();
	kprintf((uint8_t*)"%s", (uint8_t*)"Floating point: ");
	kprintf((uint8_t*)"%f", (uint8_t*)&f);
	newline();
	kprintf((uint8_t*)"%s", (uint8_t*)"Decimal: ");
	kprintf((uint8_t*)"%d", (uint8_t*)&dec);
	newline();
	kprintf((uint8_t*)"%s", (uint8_t*)"Character: ");
	kprintf((uint8_t*)"%c", (uint8_t*)&c);
	newline();

	kprintf((uint8_t*)"%s", (uint8_t*)"\n<<---Testing scanf---->>\n\n");
	kprintf((uint8_t*)"%s", (uint8_t*)"Enter a decimal value:\n");
	kscanf((uint8_t*)"%d", (uint8_t*)&dec);
	kprintf((uint8_t*)"%s", (uint8_t*)"Enter a hex value:\n");
	kscanf((uint8_t*)"%x", (uint8_t*)&hex);
	kprintf((uint8_t*)"%s", (uint8_t*)"Enter a float value:\n");
	kscanf((uint8_t*)"%f", (uint8_t*)&f);
	kprintf((uint8_t*)"%s", (uint8_t*)"Enter a character:\n");
	kscanf((uint8_t*)"%c", (uint8_t*)&c);
	kprintf((uint8_t*)"%s", (uint8_t*)"Enter a string:\n");
	kscanf((uint8_t*)"%s", (uint8_t*)str);

	kprintf((uint8_t*)"%s", (uint8_t*)"\n<<---Values received from scanf---->>\n\n");
	kprintf((uint8_t*)"%d", (uint8_t*)&dec);
	newline();
	kprintf((uint8_t*)"%x", (uint8_t*)&hex);
	newline();
	kprintf((uint8_t*)"%f", (uint8_t*)&f);
	newline();
	kprintf((uint8_t*)"%c", (uint8_t*)&c);
	newline();
	kprintf((uint8_t*)"%s", (uint8_t*)str);
	newline();


	kprintf((uint8_t*)"%s", (uint8_t*)"\n<<----Now operations on the received input will be tested---->>\n\n");
	uint32_t a = 2000;
	uint32_t b = 0;

	kprintf((uint8_t*)"%s", (uint8_t*)"Enter a decimal value for var A\n");
	kscanf((uint8_t*)"%d", (uint8_t*)&a);

	a = a * 5;
	kprintf((uint8_t*)"%s", (uint8_t*)"A multiplied by 5 (A = A*5):\n");
	kprintf((uint8_t*)"%d", (uint8_t*)&a);
	newline();

	kprintf((uint8_t*)"%s", (uint8_t*)"Enter another decimal for var B\n");
	kscanf((uint8_t*)"%d", (uint8_t*)&b);

	a = a + b;
	kprintf((uint8_t*)"%s", (uint8_t*)"Sum of A and B: (A + B)\n");
	kprintf((uint8_t*)"%d", (uint8_t*)&a);
	newline();

	float fl;
	kprintf((uint8_t*)"%s", (uint8_t*)"Enter a float value for var F\n");
	kscanf((uint8_t*)"%f", (uint8_t*)&fl);
	fl = 2 * fl;

	kprintf((uint8_t*)"%s", (uint8_t*)"2x of F: (F = 2.00 * F)\n");
	kprintf((uint8_t*)"%f", (uint8_t*)&fl);
	newline();

	while (1) {
	}
}
