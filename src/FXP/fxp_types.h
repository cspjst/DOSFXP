/**
 * Copyright (C) 2026 Dr Jeremy Thornton
 * DOSFXP - Fast Fixed-Point Number Representation
 * 10:6 signed fixed point, one type to rule them all (CGA, HGA, VGA)
 */
#ifndef FXP_TYPES_H
#define FXP_TYPES_H

#define FXP_INTEGRAL_BITS    10
#define FXP_FRACTIONAL_BITS  6

#define FXP_PART_WHOLE_MASK  0xFFC0    // 1111111111.000000
#define FXP_PART_FRAC_MASK   0x3F      // 0000000000.111111

#include <stdint.h>

typedef int16_t fxp16_t;

#endif
