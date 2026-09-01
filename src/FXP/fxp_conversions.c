#include "fxp_conversions.h"
#include "fxp_types.h"
#include "fxp_constants.h"
#include "fxp_limits.h"

fxp16_t fxp_fix_float(float f) {
    float scaled = f * (float)FXP_ONE;
    return (fxp16_t)(scaled >= 0.0f ? scaled + 0.5f : scaled - 0.5f);
}

fxp16_t fxp_saturate(int32_t n)
{
    if (n > FXP_INFINITY)  return (fxp16_t)FXP_MAX;
    if (n < FXP_NINFINITY) return (fxp16_t)FXP_MIN;
    return (fxp16_t)n;
}

/**
 * Truncate toward zero: bias negative values by FXP_FRACTIONAL_MASK before the arithmetic shift
 * Use standard signed-truncating-division-by-power-of-2 trick.
 * NB 1. Needs a onditional (sign test), hence a plain function with an __asm block rather than #pragma aux.
 * NB 2. Uses Watcom calling convention returning in AX
 */
int16_t fxp_unfix_truncate(fxp16_t x) {
    __asm {
        .8086
        mov ax, x
        or  ax, ax
        jns L1
        add ax, FXP_FRACTIONAL_MASK
L1:     sar ax, 1
        sar ax, 1
        sar ax, 1
        sar ax, 1
        sar ax, 1
        sar ax, 1
    }
}

/**
 * Ceiling toward +infinity: floor, then +1 if any fractional bit was set, regardless of sign.
 * Original value preserved in CX across the shift since SAR clobbers the flags TEST would otherwise set first.
 */
int16_t fxp_unfix_ceiling(fxp16_t x) {
    __asm {
        .8086
        mov cx, x
        mov ax, x
        sar ax, 1
        sar ax, 1
        sar ax, 1
        sar ax, 1
        sar ax, 1
        sar ax, 1
        test cx, FXP_FRACTIONAL_MASK
        jz L1
L1:     inc ax
    }
}
