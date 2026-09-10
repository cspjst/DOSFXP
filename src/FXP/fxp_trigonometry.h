/**
 * Copyright (C) 2026 Dr Jeremy Thornton
 * DOSFXP - Fast Fixed-Point Number Representation
 * @brief Fast Fixed-Point Trig by Binary Angular Measurement (BAM) 14 bit 8K Table-Lookup
 * @url https://en.wikipedia.org/wiki/Binary_angular_measurement.
 *
 * A 14 bit 8K BAM table hits a sweetspot for accuracy/memory and the worst-case error is ~0.098px (~6/64 of a single fxp16_t unit)
 * at the full logical plane's radius (512) - comfortably sub-pixel, at a quarter of the memory a full 16-bit angle would cost.
 * However, unlike a natural 8 or 16-bit width, 14 bits does not wrap for free on overflow but only needs a single and mask on entry.
 *
 * Using BAM14, a 14-bit angle held in a uint16_t a full revolution is 16384 units needing only one quadrant of sine such that
 * 0-90 degrees = 4097 tabulated points; quadrant symmetry derives the remaining three quadrants by sign and index mirroring.
 * For cosine a 90-degree phase shift into the same table solves the problem and so one 8194-byte table covers  both functions
 * across the full circle.
 */
#ifndef FXP_TRIGONOMETRY_H
#define FXP_TRIGONOMETRY_H

#include "fxp_types.h"

#define FXP_BAM14_ANGLE_BITS        14
#define FXP_BAM14_CIRCLE            16384   // steps/revolution
#define FXP_BAM14_QUADRANT          4096
#define FXP_BAM14_QUADRANT_BITS     12
#define FXP_BAM14_QUADRANT_MASK     0xFFF
#define FXP_BAM14_QUADRANT_SIZE     4096
#define FXP_BAM14_FULL_MASK         0x3FFF  //full 14-bit wrap, 0..16383

fxp16_t fxp_bam14_sin(fxp16_t a);

fxp16_t fxp_bam14_cos(fxp16_t a);

// fxp16_t fxp_bam14_tan(fxp16_t a);

void fxp_build_table();

#endif
