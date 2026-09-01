#ifndef TEST_FXP_H
#define TEST_FXP_H

#include <stdio.h>
#include <assert.h>

#include "../FXP/fxp_types.h"
#include "../FXP/fxp_conversions.h"
#include "../FXP/fxp_constants.h"
#include "../FXP/fxp_limits.h"

static void test_exhaustive_roundtrip() {
    int32_t raw;

    for (raw = INT16_MIN; raw <= INT16_MAX; raw++) {
        fxp16_t x = (fxp16_t)raw;
        float   f = fxp_unfix_float(x);
        fxp16_t y = fxp_fix(f);

        assert(x == y);
    }

    printf("test_exhaustive_roundtrip: PASS (65536/65536 values)\n");
}

static void test_known_constants() {
    static const float cases[] = {
        0.0f, 1.0f, -1.0f, 0.5f, -0.5f,
        3.14159265f, -3.14159265f,
        511.984375f,   /* == FXP_MAX exactly */
        -512.0f        /* == FXP_MIN exactly */
    };
    const float half_lsb = 0.5f / (float)FXP_ONE;
    size_t i;

    for (i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        float original  = cases[i];
        fxp16_t fixed    = fxp_fix(original);
        float recovered  = fxp_unfix_float(fixed);
        float error      = recovered - original;

        if (error < 0.0f) error = -error;
        assert(error <= half_lsb);
    }

    /* exact boundary checks - these constants are exact multiples of
       1/64, so the round trip should hit the limit values precisely,
       not just "within tolerance" */
    assert(fxp_fix(511.984375f) == FXP_MAX);
    assert(fxp_fix(-512.0f)     == FXP_MIN);

    printf("test_known_constants: PASS\n");
}

static void test_fxp() {
    printf("Test DOSFXP...\n");
    //test_exhaustive_roundtrip();
    test_known_constants();
    float f = 3.0;

    for(int i = 0; i < 10; ++i) {
        fxp16_t x = fxp_fix(f);
        printf("FXP_ONE = %i\n", fxp_unfix_round(x));
        f += 0.1;
    }
}

#endif
