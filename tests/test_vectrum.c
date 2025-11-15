// Test Pattern:
//  Arrange, Act, Assert
#include "test_common.h"
#include "vectrum.h"
#include <assert.h>
#include <stdint.h>

// Helper signatures
static void destroy_vectrum(Vectrum *vec);
static void init_int_vectrum(Vectrum *vec, size_t capacity);
static void push_int(Vectrum *vec, int value);

static void test_init(void) {
    Vectrum vec;
    init_int_vectrum(&vec, 10); // NOLINT
    destroy_vectrum(&vec);
}

// TODO:
// - `pop()` on zero cap should return an error and no-op.
//   > pop test should run before push test when built
static void test_zero_capacity(void) {
    Vectrum vec;
    const int ANSWER = 42;
    const int NICE = 69;

    init_int_vectrum(&vec, 0); // NOLINT

    push_int(&vec, ANSWER);
    assert(vec.length == 1);
    assert(vec.capacity == 2);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data != NULL);

    push_int(&vec, NICE);
    push_int(&vec, ANSWER);
    int *data = (int *)vec.data;
    assert(data[0] == ANSWER);
    assert(data[1] == NICE);
    assert(data[2] == ANSWER);
    assert(vec.length == 3);
    assert(vec.capacity == 4);
    assert(vec.data != NULL);

    destroy_vectrum(&vec);
}

static void test_size_fail(void) {
    Vectrum vec;

    int res = v_init(&vec, 0, 0);
    assert(res == VECTRUM_ERR_SIZE_INVALID);
    assert(vec.length == 0);
    assert(vec.capacity == 0);
    assert(vec.elemSize == 0);
    assert(vec.data == NULL);

    destroy_vectrum(&vec);
}

static void test_overflow_fail(void) {
    Vectrum vec;

    int res = v_init(&vec, 2, SIZE_MAX);
    assert(res == VECTRUM_ERR_OVERFLOW);
    assert(vec.length == 0);
    assert(vec.capacity == 0);
    assert(vec.elemSize == 0);
    assert(vec.data == NULL);

    destroy_vectrum(&vec);
}

static void test_reinit(void) {
    Vectrum vec;
    const int ANSWER = 42;
    const int NICE = 69;

    init_int_vectrum(&vec, 10); // NOLINT
    push_int(&vec, ANSWER);
    int *data0 = (int *)vec.data;
    assert(data0[0] == ANSWER);
    assert(vec.length == 1);
    assert(vec.capacity == 10);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data != NULL);

    destroy_vectrum(&vec);

    init_int_vectrum(&vec, 5); // NOLINT
    push_int(&vec, NICE);
    int *data1 = (int *)vec.data;
    assert(data1[0] == NICE);
    assert(vec.length == 1);
    assert(vec.capacity == 5);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data != NULL);

    destroy_vectrum(&vec);
}

// Vectrum init helper
static void init_int_vectrum(Vectrum *vec, size_t capacity) {
    int res = v_init(vec, capacity, sizeof(int));
    assert(res == VECTRUM_OK);
    assert(vec->length == 0);
    assert(vec->capacity == capacity);
    assert(vec->elemSize == sizeof(int));
    if (capacity == 0) {
        assert(vec->data == NULL);
    } else {
        assert(vec->data != NULL);
    }
}

// Vectrum destruction helper
static void destroy_vectrum(Vectrum *vec) {
    int res = v_destroy(vec);
    assert(res == VECTRUM_OK);
    assert(vec->length == 0);
    assert(vec->capacity == 0);
    assert(vec->elemSize == 0);
    assert(vec->data == NULL);
}

// Vectrum push helper
static void push_int(Vectrum *vec, int value) {
    int res = v_push(vec, &value);
    assert(res == VECTRUM_OK);
}

void run_vectrum_tests(void) {
    RUN_TEST(test_init);
    RUN_TEST(test_zero_capacity);
    RUN_TEST(test_reinit);
    RUN_TEST(test_size_fail);
    RUN_TEST(test_overflow_fail);
}
