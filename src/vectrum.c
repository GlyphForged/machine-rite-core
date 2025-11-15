#include "vectrum.h"
#include <stdint.h> // SIZE_MAX
#include <stdlib.h> // malloc, realloc, free
#include <string.h> // memcpy

static void zero_vectrum(Vectrum *vRef);

int v_init(Vectrum *vRef, size_t capacity, size_t elemSize) {
    if (vRef == NULL) {
        return VECTRUM_ERR_REF_INVALID;
    }

    zero_vectrum(vRef);

    if (elemSize == 0) {
        return VECTRUM_ERR_SIZE_INVALID;
    }
    if (capacity > SIZE_MAX / elemSize) {
        return VECTRUM_ERR_OVERFLOW;
    }

    vRef->elemSize = elemSize;

    if (capacity == 0) {
        return VECTRUM_OK;
    }

    void *buffer = malloc(capacity * elemSize);
    if (buffer == NULL) {
        return VECTRUM_ERR_OOM;
    }

    vRef->capacity = capacity;
    vRef->data = buffer;
    return VECTRUM_OK;
}

int v_destroy(Vectrum *vRef) {
    if (vRef == NULL) {
        return VECTRUM_ERR_REF_INVALID;
    }
    if (vRef->data != NULL) {
        free(vRef->data);
    }
    zero_vectrum(vRef);
    return VECTRUM_OK;
}

int v_push(Vectrum *vRef, const void *element) {
    if (vRef == NULL || element == NULL) {
        return VECTRUM_ERR_REF_INVALID;
    }
    if (vRef->length == vRef->capacity) {
        size_t newCap;
        if (vRef->capacity == 0) {
            newCap = 2;
        } else {
            newCap = vRef->capacity * 2;
        }
        if (newCap > SIZE_MAX / vRef->elemSize) {
            return VECTRUM_ERR_OVERFLOW;
        }

        void *tmp = realloc(vRef->data, (newCap * vRef->elemSize));

        if (tmp == NULL) {
            return VECTRUM_ERR_OOM;
        }

        vRef->capacity = newCap;
        vRef->data = tmp;
    }
    size_t index = vRef->length;
    unsigned char *dataPtr = (unsigned char *)vRef->data;
    unsigned char *dest = dataPtr + (index * vRef->elemSize);
    memcpy(dest, element, vRef->elemSize);
    vRef->length++;
    return VECTRUM_OK;
}

static void zero_vectrum(Vectrum *vRef) {
    vRef->length = 0;
    vRef->capacity = 0;
    vRef->elemSize = 0;
    vRef->data = NULL;
}
