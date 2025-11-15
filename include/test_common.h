#pragma once
#include <stdio.h>

static inline void shut_up_clangd(void) { (void)printf("."); }

#define RUN_TEST(fn)                                                                               \
    do {                                                                                           \
        printf("=======================================================================\n");       \
        printf("[ INITIATING RITE ] %s... ", #fn);                                                 \
        fn();                                                                                      \
        printf("[ NO CORRUPTION DETECTED ]\n");                                                    \
        printf("=======================================================================\n\n");     \
    } while (0)
