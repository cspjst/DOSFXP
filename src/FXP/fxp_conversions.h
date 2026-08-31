/**
 * Copyright (C) 2026 Dr Jeremy Thornton
 * DOSFXP - Fast Fixed-Point Number Representation
 * Conversion functions to and from the the C <float> number line to the <fxp16_t> fixed point -512..+511.984357 number line
 * Numeric conversions for fxp16_t
 */
#ifndef FXP_CONVERSIONS_H
#define FXP_CONVERSIONS_H

#include "fxp_types.h"

// entry to the 10:6 fixed point number line float->fxp16_t
fxp16_t fxp_fix(float f);

// entry to the 10:6 fixed point number line, clamped narrowing of an already-rescaled 32-bit intermediate
// (e.g. a multiply result) -> fxp16_t
fxp16_t fxp_saturate(int32_t n);

// exit from the 10:6 fixed point number line fxp16_t->float
float fxp_unfix_float(fxp16_t x);

// exit from the 10:6 fixed point number line fxp16_t->int16_t, toward zero
int16_t fxp_unfix_trunc(fxp16_t x);

// exit from the 10:6 fixed point number line fxp16_t->int16_t, toward -infinity
int16_t fxp_unfix_floor(fxp16_t x);

// exit from the 10:6 fixed point number line fxp16_t->int16_t, toward +infinity
int16_t fxp_unfix_ceil(fxp16_t x);

// exit from the 10:6 fixed point number line fxp16_t->int16_t, nearest, ties toward +infinity
int16_t fxp_unfix_round(fxp16_t x);

#endif
