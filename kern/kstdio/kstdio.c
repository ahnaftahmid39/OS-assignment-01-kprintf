#include "../include/kstdio.h"
#include "../../kern/arch/stm32f446re/include/dev/usart.h"

/*
	converts integer to ascii string
	size of buf should be greater than 32, so that we can access buf[32]
*/
void itoa(int val, int base, uint8_t* a) {
	if (val == 0) {
		*a = '0';
		*(a + 1) = 0;
		return;
	}
	uint8_t buf[33];
	buf[32] = 0;
	uint8_t neg = 0, i = 31, j = 0;
	if (val < 0) {
		neg = 1;
		val *= -1;
	}
	for (; val && i; --i, val /= base) {
		buf[i] = "0123456789abcdef"[val % base];
	}
	if (neg) {
		buf[i] = '-';
		i--;
	}
	while (buf[i + j + 1] != 0) {
		*a++ = buf[i + j + 1];
		j++;
	}
	*a = 0;
}
/*
	converts float to ascii string
*/
void ftoa(float f, uint8_t* buf) {
	int val = (int)f;
	uint8_t rstr[33], i = 0;
	itoa(val, 10, rstr);
	while (rstr[i] != '\0') {
		*buf++ = rstr[i];
		i++;
	}
	*buf++ = '.';

	if (f < 0) {
		val = -val;
		f = -f;
	}
	for (int j = 0; j < 6; j++) {
		f -= (float)val;
		f *= 10;
		val = (int)f;
		uint8_t c;
		itoa(val, 10, &c);
		*buf++ = c;
	}
	*buf = 0;
}
/*
	converts ascii to integer
*/
int atoi(uint8_t* buf, int base) {
	int ret = 0;
	uint8_t neg = 0;
	int8_t l = 0;



	while (buf[l]) l++;
	l--;
	if (buf[0] == '-') {
		neg = 1;
	}

	if (base == 16) {
		if (neg && buf[1] == '0' && buf[2] == 'x') {
			neg = 3;
		}
		else if (neg == 0 && buf[0] == '0' && buf[1] == 'x') {
			neg = 2;
		}
	}

	int i;
	for (i = 1; l >= neg; i *= base) {
		int a;
		if (buf[l] >= 'a' && buf[l] <= 'z') {
			a = buf[l] - 'a' + 10;
		}
		else if (buf[l] >= 'A' && buf[l] <= 'Z') {
			a = buf[l] - 'A' + 10;
		}
		else {
			a = buf[l] - '0';
		}
		ret += i * a;
		l--;
	}

	if (neg % 2 != 0) {
		ret *= -1;
	}
	return ret;
}

/*
	converts string to float
*/
float atof(uint8_t buff[]) {
	float num = 0;
	uint8_t minus = 0;
	uint8_t i = 0;
	if (buff[0] == '-') {
		minus = 1;
		i++;
	}

	for (; buff[i] != 0; i++) {
		if (buff[i] == '.' || buff[i] == 'e') {
			break;
		}
		num = num * 10 + (buff[i] - '0');
	}
	// printf("Number after decimal part: %f\n", num);

	if (buff[i] == '.') {
		float frac = 0;
		uint32_t len = 1;
		i++;
		for (; buff[i] != 0; i++) {
			if (buff[i] == 'e') {
				break;
			}
			frac = frac * 10 + (buff[i] - '0');
			len *= 10;
		}
		frac /= len;
		num += frac;
	}
	// printf("Number after fraction part: %f\n", num);


	if (buff[i] == 'e') {
		i++;
		uint8_t neg = 0;
		if (buff[i] == '-') {
			neg = 1;
			i++;
		}
		uint8_t exp = 0;
		for (; buff[i] != 0; i++) {
			exp = exp * 10 + (buff[i] - '0');
		}
		if (neg)
			for (uint8_t j = 0; j < exp; j++) {
				num /= 10;
			}
		else
			for (uint8_t j = 0; j < exp; j++) {
				num *= 10;
			}
	}
	// printf("Number after exponent part: %f\n", num);

	if (minus)
		num *= -1;
	return num;
}

/**
* first argument define the type of string to kprintf and kscanf,
* %c for charater
* %s for string,
* %d for integer
* %x hexadecimal
* %f for floating point number
*/
void kprintf(uint8_t* format, uint8_t* outvar) {
	// buffer for parsing int, hex, float to character array
	uint8_t buf[105];
	switch (format[1]) {

	// character
	case 'c':
		UART_SendChar(USART2, *((char*)outvar));
		break;

	// string
	case 's':
		_USART_WRITE(USART2, outvar);
		break;

	// decimal
	case 'd':
		itoa(*((int32_t*)outvar), 10, buf);
		_USART_WRITE(USART2, buf);
		break;

	// hexadecimal
	case 'x':
		itoa(*((uint32_t*)outvar), 16, buf);
		_USART_WRITE(USART2, (uint8_t*)"0x");
		_USART_WRITE(USART2, buf);
		break;

	// floating point
	case 'f':
		for (int i = 0; i < 100; i++) buf[i] = 0;
		ftoa(*(float*)outvar, (uint8_t*)buf);
		_USART_WRITE(USART2, buf);
		break;

	default:
		break;
	}
}

/**
* first argument define the type of string to kprintf and kscanf,
* %c for charater
* %s for string,
* %d for integer
* %x hexadecimal
* %f for floating point number
*/
void kscanf(uint8_t* format, uint8_t* invar) {
	// buffer for converting character array to int, hex, float
	uint8_t buf[105];
	switch (format[1]) {
	// character
	case 'c': {
		_USART_READ_WORD(USART2, buf, 3);
		*(char*)invar = buf[0];
		break;
	}
	// string
	case 's': {
		_USART_READ_WORD(USART2, invar, 100);
		break;
	}
	// decimal
	case 'd': {
		_USART_READ_WORD(USART2, buf, 32);
		int num = atoi(buf, 10);
		*(uint32_t*)invar = num;
		break;
	}
	// hexadecimal
	case 'x': {
		_USART_READ_WORD(USART2, buf, 32);
		int num = atoi(buf, 16);
		*(uint32_t*)invar = num;
		break;
	}
	// floating point
	case 'f': {
		_USART_READ_WORD(USART2, buf, 100);
		*(float*)invar = atof(buf);
		break;
	}
	default:
		break;
	}
}
