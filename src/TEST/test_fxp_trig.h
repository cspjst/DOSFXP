#include "../FXP/fxp_trigonometry.h"

#include "../FXP/fxp_conversions.h"
#include <stdio.h>
#include <math.h>


/*
// 2PI radians / 256 8bit steps i.e. 0xFF
// 6.28318531 / 256
static const double radian_step = 0.02454369;

void fxp_build_table() {
    printf("BAM8 Sine Table[256]\n");
    for(int i = 0; i < 257; ++i) {
        double a = sin(radian_step * (double)i);
        printf("%3d, ", fxp_fix_float(a));
    }
}
*/

static void test_fxp_trig() {
    //fxp_build_table();
    int i[] = {0, 90, 180, 270, 360, 450, -90};
    for(int j = 0; j < 7; ++j) {
        fxp16_t a = fxp_fix_int(i[j]);
        printf("sin(%i) = %f\n", i[j], fxp_unfix_float(fxp_sin(a)));
    }
}
