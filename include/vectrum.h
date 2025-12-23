#pragma once
#include <stddef.h>

/* Vectrum - generic dynamic array of values.
 *
 * Invariants (initialized state):
 *  - length <= capacity
 *  - elemSize > 0
 *  - if capacity == 0: data == NULL
 *  - if capacity > 0: data points to at least (capacity * elemSize) bytes
 *
 * Lifetime:
 *  - Call v_init() before any other operation
 *  - Call v_destroy() when done
 *  - After v_destroy(), the Vectrum is zeroed and may be re-initialized.
 *  - Behavior is undefined if any function is called on an uninitialized
 *    or non-destroyed-but-reinitialized Vectrum.
 *
 * Callers should treat Vectrum fields as read-only after v-init().
 * Modifying them directly can break invariants and result in UB.
 * Calling functions on an uninitialized Vectrum is UB.
 */
typedef struct {
    size_t length;   // Number of valid elements
    size_t capacity; // Number of elements that fit in the buffer
    size_t elemSize; // Size in bytes of each element
    void *data;      // Backing buffer (owned by Vectrum)
} Vectrum;

// Error codes returned by Vectrum operations
enum {
    VECTRUM_OK = 0,
    VECTRUM_ERR_OOM,          // Out of memory / allocation failure
    VECTRUM_ERR_OVERFLOW,     // Capacity * elemSize overflow
    VECTRUM_ERR_SIZE_INVALID, // Element Size Invalid
    VECTRUM_ERR_ARG_INVALID,  // Argument provided is invalid
    VECTRUM_ERR_SIZE_ZERO,    // Tried to pop a 0-size vectrum
    VECTRUM_ERR_BOUNDS,       // Attempted to access out of bounds
};

/* Initialize a Vectrum.
 *
 * Preconditions:
 *  - elem_size > 0
 *  - capacity * elemSize does not overflow size_t
 *  - vRef is either uninitialized or previously destroyed
 *
 * Postconditions on success:
 *  - vRef->length == 0
 *  - vRef->capacity == capacity
 *  - vRef->elemSize == elemSize
 *  - if capacity == 0: vRef->data == NULL
 *  - if capacity > 0: vRef->data points to capacity * elemSize bytes
 *
 * On failure:
 *  - vRef is zeroed (length = capacity = elemSize = 0, data = NULL)
 *  - a non-zero error code is returned
 */
int v_init(Vectrum *vRef, size_t capacity, size_t elemSize);

/* Destroy a Vectrum and free its backing buffer (if any).
 *
 * Preconditions:
 *  - vRef is either:
 *    - initialized
 *    - zeroed by v_destroy() or a failing v_init().
 *
 * Postconditions:
 *  - vRef->length == 0
 *  - vRef->capacity == 0
 *  - vRef->elemSize == 0
 *  - vRef->data == NULL
 *
 * On failure:
 *  - a non-zero error code is returned
 *
 * Behavior is undefined if called on an uninitialized  object or non-Vectrum
 */
int v_destroy(Vectrum *vRef);

/* Push one element into the back of the Vectrum.
 *
 * The element is copied by value into the backing buffer.
 *
 * Preconditions:
 *  - vRef != NULL
 *  - vRef is initialized (NOT destroyed/zeroed)
 *  - element points to at least vRef->elemSize bytes representing a value of
 *    the logical element type. If not, behavior is undefined.
 *
 * Postconditions on success:
 *  - let old_length = vRef->length on entry
 *  - let old_capacity = vRef->capacity on entry
 *  - vRef->length == old_length + 1
 *  - vRef->capacity >= vRef->length
 *  - elements at indices [0, old_length) are unchanged
 *  - element at index old_length is equal to the pushed value
 *  - if old_length == old_capacity on entry, capacity is increased
 *    (typically >= 2 * old_capacity, with overflow checks)
 *
 * On failure (OOM or overflow):
 *  - vRef is unchanged
 *  - a non-zero error code is returned
 */
int v_push(Vectrum *vRef, const void *element);

/* Pop the last element off of the Vectrum.
 *
 * The element is not destroyed, but rather, the length is simply reduced by one.
 * This should mean that pushing a new element simply overwrites the value
 * 
 * Preconditions:
 * - vRef != NULL
 * - vRef is initialized (NOT destroyed/zeroed)
 * - vRef length > 0
 *
 * Postconditions on success:
 * - let old_length = vRef->length on entry
 * - let new_length = old_length - 1
 * - elements at indices [0, new_length) are unchanged
 *
 * On failure (No elements in vectrum):
 * - vRef is unchanged
 * - a non-zero error code is returned
 */
int v_pop(Vectrum *vRef);

/* Return the value of an element.
 *
 * Preconditions:
 * - vRef != NULL
 * - vRef is initialized (NOT destroyed/zeroed)
 * - vRef length > 0
 * - index < vRef.length
 *
 * Postconditions on success:
 * - vRef is unchanged
 * - outElement == vRef.data at the provided index
 *
 * On failure (No elements or out of range):
 * - vRef is unchanged
 * - a non-zero error code is returned
 * - outElement == NULL
 */
int v_peek(const Vectrum *vRef, size_t index, void *outElement);
