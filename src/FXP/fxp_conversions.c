#include "fxp_conversions.h"
#include "fxp_types.h"
#include "fxp_constants.h"

fxp16_t fxp_fix(float f) {
    float scaled = f * (float)FXP_ONE;
    return (fxp16_t)(scaled >= 0.0f ? scaled + 0.5f : scaled - 0.5f);
}

float fxp_unfix_float(fxp16_t x) {
    return (float)x / (float)FXP_ONE;
}
