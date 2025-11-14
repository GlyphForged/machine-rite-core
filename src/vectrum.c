#include "vectrum.h"

int v_init(Vectrum *vRef, size_t capacity, size_t elemSize) {
    if (elemSize == 0 || capacity > SIZE_MAX / elemSize) {
        vRef->length = 0;
        vRef->capacity = 0;
        vRef->elemSize = 0;
        vRef->data = NULL;

        int err = (elemSize == 0) ? VECTRUM_ERR_SIZE_INVALID : VECTRUM_ERR_OVERFLOW;
        return err;
    }
    if (capacity == 0) {
        vRef->length = 0;
        vRef->capacity = 0;
        vRef->elemSize = elemSize;
        vRef->data = NULL;
        return VECTRUM_OK;
    }

    void *buffer = malloc(capacity * elemSize);

    if (buffer == NULL) {
        vRef->length = 0;
        vRef->capacity = 0;
        vRef->elemSize = 0;
        vRef->data = NULL;
        return VECTRUM_ERR_OOM;
    }
    vRef->length = 0;
    vRef->capacity = capacity;
    vRef->elemSize = elemSize;
    vRef->data = buffer;
    return VECTRUM_OK;
}

void v_destroy(Vectrum *vRef) {
    if (vRef->data != NULL) {
        free(vRef->data);
    }
    vRef->length = 0;
    vRef->capacity = 0;
    vRef->elemSize = 0;
    vRef->data = NULL;
}

int v_push(Vectrum *vRef, const void *element) {
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
