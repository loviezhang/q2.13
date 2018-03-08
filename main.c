#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include "q2dot13.h"

void dump_32(const char* prefix, uint32_t v) {
    printf("%s: ", prefix);
    for (int i = 0; i < 32; i++) {
        printf(" %d", (v >> (31-i)) & 1);
        if (i % 8 == 0) {
            printf("  ");
        }
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
        if (i % 8 == 0) {
            printf("  ");
        }
    }
    printf("\n");
}


int main(int argc, char** argv) {
    printf("max = [%.16f]\n", pos_q2dot13_max);
    printf("min = [%.16f]\n", pos_q2dot13_min);
    printf("\n");

    float a = atof(argv[1]);
    printf("value  = [%.8f]\n", a);
    printf("\n");
    dump_float("value   ", a);
    uint16_t en = q2dot13_encode(a);
    dump_16("encode  ", en);

    float de = q2dot13_decode(en);
    dump_float("decode  ", a);
    printf("\n");
    printf("decode = [%.8f]\n", de);

    return 0;
}
