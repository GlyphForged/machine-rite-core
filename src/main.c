#include "vectrum.h"
#include <stdio.h>

int main(void) {
    printf("Machine Rite Core Library - Vectrum Demo\n");

    Vectrum vec;
    int testInt = 42; // NOLINT

    if (v_init(&vec, 0, sizeof(int)) != VECTRUM_OK) {
        fprintf(stderr, "Failed to init Vectrum.\n");
        return 1;
    }

    if (v_push(&vec, &testInt) != VECTRUM_OK) {
        fprintf(stderr, "Failed to push to Vectrum.\n");
        return 1;
    }

    testInt = 69; // NOLINT

    if (v_push(&vec, &testInt) != VECTRUM_OK) {
        fprintf(stderr, "Failed to push to Vectrum.\n");
        return 1;
    }

    testInt = 420; // NOLINT

    if (v_push(&vec, &testInt) != VECTRUM_OK) {
        fprintf(stderr, "Failed to push to Vectrum.\n");
        return 1;
    }

    int *data = (int *)vec.data;

    for (size_t i = 0; i < vec.length; i++) {
        printf("%d\n", data[i]);
    }

    if (v_destroy(&vec) != VECTRUM_OK) {
        fprintf(stderr, "Failed to destroy Vectrum.\n");
        return 1;
    }

    printf("End of rite. Praise the Omnissiah.\n");

    return 0;
}
