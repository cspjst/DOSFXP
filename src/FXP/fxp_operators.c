#include "fxp_operators.h"
#include "fxp_types.h"
#include "fxp_limits.h"

fxp16_t fxp_mul(fxp16_t lhs, fxp16_t rhs) {
    __asm {
        .8086
        mov     bx, dx
        imul    bx                      ; DX:AX = lhs * rhs
        cmp     dx, 31                  ; will the hi word overflow 10.6?
        jg      INF                     ; yes clamp
        cmp     dx, -32                 ; will the hi word undeflow 10.6?
        jl      NINF                    ; yes clamp

        sar     dx, 1                   ; emulating SHRD (80386) on 8086/8088
        rcr     ax, 1                   ; unrolled CX 6 LOOP double-precision shift right
        sar     dx, 1                   ; uses 24 instead of 118 cycles
        rcr     ax, 1                   ; shift right DX:AX as 32 bits
        sar     dx, 1
        rcr     ax, 1
        sar     dx, 1
        rcr     ax, 1
        sar     dx, 1
        rcr     ax, 1
        sar     dx, 1
        rcr     ax, 1

        jmp     END
INF:    mov     ax, FXP_MAX             ; clamp result to 10.6 +infinity (+511.984)
        jmp     END
NINF:   mov     ax, FXP_MIN             ; clamp result to 10.6 - infinity(-512.000)

END:

    }
}

fxp16_t fxp_div(fxp16_t lhs, fxp16_t rhs) {
    __asm {
		.8086
		mov		bx, dx
		cwd		                        ; DX:AX = sign-extend AX

		mov		cx, FXP_FRACTIONAL_BITS
_SHLD:	sal		ax, 1			        ; shift left DX:AX as 32 bits
		rcl		dx, 1				    ; ...
		loop	_SHLD					; emulate the SHLD (80386) instruction

		idiv	bx						; 80286 and 80386 divide 0 or quotient too large fit destination -> inf loop!
	}
}
