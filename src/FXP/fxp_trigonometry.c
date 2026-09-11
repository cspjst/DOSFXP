/**
 * Copyright (C) 2026 Dr Jeremy Thornton
 * DOSFXP - Fast Fixed-Point Number Representation
 * BAM14 quarter-sine lookup table data.
 */
#include "fxp_trigonometry.h"
#include "fxp_types.h"

//const fxp16_t FXP_BAM14_SIN_TABLE[FXP_BAM14_QUADRANT_SIZE] = {};

#include <stdio.h>
#include <math.h>
#include "fxp_conversions.h"

// 2PI radians / 16384 14bit steps i.e. 0x3FFF
static const double radian_step = 0.0003835;

void fxp_build_table() {
    printf("sin(90) = %f\n", sin(radian_step * 4095.0));
    for(int i = 4090; i < FXP_BAM14_QUADRANT; ++i) {
        double a = sin(radian_step * (double)i);
        printf("%i = %f\n", i, a);
        //if(!(i % 32)) printf("\n");
    }
}
