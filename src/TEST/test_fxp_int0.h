#ifndef TEST_FXP_INT0_H
#define TEST_FXP_INT0_H

#include <stdio.h>

#include "../../DOSLIB/src/DOS/dos_services.h"
#include "../../DOSLIB/src/DOS/dos_services_constants.h"

static const char PANIC_MESSAGE[] = "*FXP Panic! INT 0*$";

void __interrupt __far dosfxp_int0_handler() {
    __asm {
        .8086

        lea     dx, PANIC_MESSAGE
        mov     ah, DOS_PRINT_STRING
        int     DOS_SERVICE

        mov     al, 13                  ; DOS_INVALID_DATA
        mov     ah, DOS_TERMINATE_PROCESS_WITH_RETURN_CODE
        int     DOS_SERVICE
    }
}

static void test_fxp_int0() {
    void* pint0 = dos_get_interrupt_vector(0);
    printf("dosfxp = %p\n", (void*)dosfxp_int0_handler);
    printf("int 0 = %p\n", pint0);
    dos_set_interrupt_vector(0, (void*)dosfxp_int0_handler);
    printf("int 0 = %p\n", dos_get_interrupt_vector(0));
    int x = 1;
    x /= 0;
    dos_set_interrupt_vector(0, pint0);
    printf("int 0 = %p\n", dos_get_interrupt_vector(0));
}

#endif
