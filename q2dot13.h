#ifndef __Q_2_DOT_13_H__
#define __Q_2_DOT_13_H__

#include <stdint.h>

const float pos_q2dot13_max = 4 - pow(2, -13);
const float pos_q2dot13_min = pow(2, -13);

const float neg_q2dot13_max = -1 * pos_q2dot13_max;
const float neg_q2dot13_min = -1 * pos_q2dot13_min;


uint16_t q2dot13_encode(float v) {
    if (v > pos_q2dot13_max || v < neg_q2dot13_max) {
        return 0;
    }
    if (v < pos_q2dot13_min && v > neg_q2dot13_min) {
        return 0;
    }

    uint32_t bits = *(uint32_t*)&v;

    int exponent = ((bits >> 23) & 0xff) - 127;
    uint32_t fraction;
    if (exponent >= 0) {
        fraction = ((bits & 0x007fffff) | 0x00800000) << exponent;
    } else {
        fraction = ((bits & 0x007fffff) | 0x00800000) >> (-1*exponent);
    }

    return ((bits>>16)&0x8000) | ((fraction>>10)&0x6000) | ((fraction>>10)&0x1fff);
}

float q2dot13_decode(uint16_t v) {
    if (v == 0) {
        return 0;
    }

    int exponent = 2;
    uint32_t bits = 0;

    bits |= ((uint32_t)v & 0x7fff) << 8;

    do {
        bits <<= 1;
        exponent--;
    } while ((bits & 0x800000) == 0);

    bits &= ~0x800000;
    bits |= (exponent + 127) << 23 | ((uint32_t)v & 0x8000) << 16;

    return *(float*)&bits;
}

#endif
