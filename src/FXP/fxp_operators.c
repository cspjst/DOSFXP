#include "fxp_operators.h"
#include "fxp_types.h"

fxp16_t fxp_mul(fxp16_t lhs, fxp16_t rhs) {
    __asm {
        .8086
        mov     ax, lhs
        mov     bx, rhs
        imul    bx                      ; DX:AX = lhs * rhs

        cmp     dx, 31                  ; will the hi word overflow 10.6?
        jg      INF                     ; yes clamp
        cmp     dx, -32                 ; will the hi word undeflow 10.6?
        jl      NINF                    ; yes clamp
        mov     cx, FXP_FRACTIONAL_BITS ; double precision shift right 6 bits
_SHRD:  sar     dx, 1                   ; shift right DX:AX as 32 bits
        rcr     ax, 1
        loop    _SHRD                   ; emulate the SHRD (80386) instruction
        jmp     END
INF:    mov     ax, FXP_MAX             ; clamp result to 10.6 +infinity (+511.984)
        jmp     END
NINF:   mov     ax, FXP_MIN             ; clamp result to 10.6 - infinity(-512.000)

END:

    }
}
