/**
 * Copyright (C) 2026 Dr Jeremy Thornton
 * DOSFXP - Fast Fixed-Point Number Representation
 * Characteristics of core fixed point types
 * Type support
 * Numeric limits for fxp16_t
 */
#ifndef FXP_LIMITS_H
#define FXP_LIMITS_H

#define FXP_INTEGRAL_BITS		10
#define FXP_FRACTIONAL_BITS	    6
#define FXP_FRACTIONAL_MASK	    0x3F		// i.e. 0000000000.111111
#define FXP_FRACTIONAL_MIN	    0.015625	// which in 10:6 bits layout is 0000000000.000001
#define FXP_MAX				    32767		// 0111111111.111111
#define FXP_MIN				    -32768		// 1000000000.000000
#define FXP_MAXINT			    511
#define FXP_MININT			    -512
#define FXP_INFINITY            32767		// which in 10:6 bits layout is 511.984
#define FXP_NINFINITY           -32767		// which in 10:6 bits layout is -512.000

#endif
