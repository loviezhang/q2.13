#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "q2dot13.h"

void dump_32(const char* prefix, uint32_t v) {
    printf("%s: ", prefix);
    for (int i = 0; i < 32; i++) {
        printf(" %d", (v >> (31-i)) & 1);
    }
    printf("\n");
}

void dump_float(const char* prefix, float v) {
    dump_32(prefix, *((uint32_t*)&v));
}

void dump_16(const char* prefix, uint16_t v) {
    printf("%s: ", prefix);
    for (int i = 0; i < 16; i++) {
        printf(" %d", (v >> (15-i)) & 1);
    }
    printf("\n");
}

uint16_t q2dot13_encode(float v) {
	uint32_t bits = *(uint32_t*)&v;
	dump_32("bits    ", bits);
	uint32_t sign = bits >> 31;
	dump_32("sign    ", sign);
	uint32_t exponent = (bits >> 23) & 0xff;
	dump_32("exponent", exponent);
	uint32_t fraction = bits & 0x007fffff;
	dump_32("fraction", fraction);

	printf("%.8f\n", (float)fraction/(1<<23));

	//float r = pow(2, 127 - exponent) * 

	return 0;
}

float q2dot13_decode(uint16_t v) {
	return 0;
}

int main(int argc, char** argv) {
    float a = atof(argv[1]);
    printf("value = [%.8f]\n", a);

	q2dot13_encode(a);

    return 0;
}
