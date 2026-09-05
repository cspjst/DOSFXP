#ifndef FXP_PARTS_H
#define FXP_PARTS_H

#include "fxp_types.h"

#define fxp_part_whole(v) ((fxp16_t)((v) & FXP_PART_WHOLE_MASK))

#define fxp_part_frac(v) ((fxp16_t)((v) & FXP_PART_FRAC_MASK))

#endif
