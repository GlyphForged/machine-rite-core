// Test Pattern:
//  Arrange, Act, Assert
#include "vectrum.h"
#include <assert.h>

static void test_init(void) {
    Vectrum vec;

    int init = v_init(&vec, 10, sizeof(int)); // NOLINT

    assert(init == VECTRUM_OK);
    assert(vec.length == 0);
    assert(vec.capacity == 10);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data != NULL);

    int dest = v_destroy(&vec);
    assert(dest == VECTRUM_OK);
    assert(vec.length == 0);
    assert(vec.capacity == 0);
    assert(vec.elemSize == 0);
    assert(vec.data == NULL);
}

// TODO:
// - `pop()` on zero cap should return an error and no-op.
//   > pop test should run before push test when built
static void test_zero_capacity(void) {
    Vectrum vec;
    const int ANSWER = 42;
    const int NICE = 69;

    int init = v_init(&vec, 0, sizeof(int));

    assert(init == VECTRUM_OK);
    assert(vec.length == 0);
    assert(vec.capacity == 0);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data == NULL);

    int push0 = v_push(&vec, &ANSWER);
    assert(push0 == VECTRUM_OK);
    assert(vec.length == 1);
    assert(vec.capacity == 2);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data != NULL);

    int push1 = v_push(&vec, &NICE);
    int push2 = v_push(&vec, &ANSWER);
    int *data = (int *)vec.data;
    assert(push1 == VECTRUM_OK);
    assert(push2 == VECTRUM_OK);
    assert(data[0] == ANSWER);
    assert(data[1] == NICE);
    assert(vec.length == 3);
    assert(vec.capacity == 4);
    assert(vec.data != NULL);

    int dest = v_destroy(&vec);
    assert(dest == VECTRUM_OK);
}

/*
 TODO:
    - Failure Path
        - Call v_init with elemSize == 0;
            - Result should be VECTRUM_ERR_SIZE_INVALID
            - Struct should be in a "safe" state.
        - Call v_init with values that trigger overflow.
            - i.e. capacity == MAX_SIZE and elemSize == 2
            - Expect VECTRUM_ERR_OVERFLOW
            - Expect safe state again
*/
static void test_init_failure(void) {
    // WIP
}

static void test_reinit(void) {
    Vectrum vec;
    const int ANSWER = 42;
    const int NICE = 69;

    int init0 = v_init(&vec, 10, sizeof(int)); // NOLINT
    int push0 = v_push(&vec, &ANSWER);
    int *data0 = (int *)vec.data;
    assert(init0 == VECTRUM_OK);
    assert(push0 == VECTRUM_OK);
    assert(data0[0] == ANSWER);
    assert(vec.length == 1);
    assert(vec.capacity == 10);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data != NULL);

    int dest0 = v_destroy(&vec);
    assert(dest0 == VECTRUM_OK);
    assert(vec.length == 0);
    assert(vec.capacity == 0);
    assert(vec.elemSize == 0);
    assert(vec.data == NULL);

    int init1 = v_init(&vec, 5, sizeof(int)); // NOLINT
    int push1 = v_push(&vec, &NICE);
    int *data1 = (int *)vec.data;
    assert(init1 == VECTRUM_OK);
    assert(push1 == VECTRUM_OK);
    assert(data1[0] == NICE);
    assert(vec.length == 1);
    assert(vec.capacity == 5);
    assert(vec.elemSize == sizeof(int));
    assert(vec.data != NULL);

    int dest1 = v_destroy(&vec);
    assert(dest1 == VECTRUM_OK);
}

void run_vectrum_tests(void) {
    test_init();
    test_zero_capacity();
    test_init_failure();
    test_reinit();
}
