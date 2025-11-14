# Vectrum - A custom dynamic array

## MVP Goals

- contiguous block of values
- Stores elements in a contiguous buffer
- `elemSize` set at initialization
- Manages the backing buffer's lifetime

## MVP Functionality

- create (&VectrumPtr, initialCapacity, dataType/elemSize)
- destroy (&VectrumPtr)
- currentLength (&VectrumPtr)
- capacity (&VectrumPtr)
- pushElement(&VectrumPtr, data)
- popElement(&VectrumPtr)
- randomAccess(&VectrumPtr, index)
- removeElement(&VectrumPtr, index)
- clear(&VectrumPtr)

## Stretch Goals

- Additional functionality:
- Vectrum of pointers functionality for heterogeneous data

## Plain English Explanation

The Vectrum struct itself will include 4 key pieces of data:
- the current length of the vector
- the maximum size of the vector
- the element size of the vector
- a pointer to the start of the allocated block of memory

Creation of an empty vector involves:
- User creates a new Vectrum struct containing placeholder 'header' data
- vector_init:
  - sets the initial values and allocates a block of memory of the appropriate size
  - sets the length of the vector to 0
  - stores the address of the start of the allocated block of memory in the user-owned Vectrum struct

So the user of the vector library creates a new Vectrum object, and then calls `init` on the struct,
passing in the data type and the desired initial capacity, along with a pointer to the Verctrum object
the user created. init calls malloc to get a chunk of data of the appropriate size, then uses the pointer
to update the Vectrum object with the appropriate information, namely: The capacity, the current length,
the size of each item, and a pointer to the address of the allocated block of memory.

Vectrum Contains:
- length: size_t
  - The current length of the array, as a positive integer
  - Length will never underflow or overflow.
- capacity: size_t
  - The current maximum length of the array, as a positive integer
  - Capacity should never underflow or overflow.
- elemSize: size_t
  - The size of each element of the array
  - Once set via init, does not change.
- data: ptr*
  - A pointer to the data buffer
  - Updates when the Vectrum grows.

Invariants:
- Length is always less than or equal to Capacity, neither are ever below 0.
- If capacity is > 0, data will always hold a valid pointer to a block of size: capacity * elemSize
- Only buffer elements within the domain (0, length - 1) are valid
- elemSize, once set, is never changed, and always > 0.
- The Vectrum owns the memory pointed to by data
- Only the Vectrum may free(data)
- On destroy: data = NULL; length = 0; capacity = 0;
- Potential states:
  - Uninitialized
  - Initialized
  - Destroyed
- Calling any function except `init` on an Uninitialized Vectrum should return either an error, or a no-op.
- The only valid function you can call on a Destroyed Vectrum is `init`
- If capacity > 0, `capacity * elemSize` <= `size_t`

- Work out what the Vectrum looks like in each of these states:
  - Newly created, uninitialized Vectrum.
    - Garbage data. Running any operations other than init will result in undefined behavior.
  - Vectrum with 3 elements added.
    - elemSize = User defined size during init() && > 0
    - capacity = >= 3
    - length = 3
      - (Valid elements live in 0 to length - 1)
    - data = pointer to a valid buffer of at least `capacity * elemSize` bytes.
  - Vectrum after pushing an element that forces a grow operation.
    - elemSize = User defined size during init()
    - capacity = > prior capacity + 1
    - length = Prior length + 1
    - data = pointer to a new buffer of `newCapacity * elemSize` bytes.
    - All previous elements (0 to oldLength) are preseved bit for bit in the new buffer
    - Old buffer is released
  - Vectrum after destruction.
    - elemSize = 0
    - capacity = 0
    - length = 0
    - data = nullPtr
    - The only valid call on a destroyed Vectrum is `init().`

## Function Definitions

### init()

Init will handle initialization of the Vectrum. This can be either initialization of a destroyed Vectrum, or initialization of an uninitialized Vectrum.

Calling `init()` on an initialized Vectrum will result in undefined behavior.

#### init() Inputs

- `vectrumRef` - A valid pointer to the Vectrum object/instance created by the user.
- `capacity` - An initial capacity. This can be any whole number of valid `size_t`
- `elemSize` - An element size. This can be any whole number of valid `size_t`

#### init() Preconditions

- `capacity * elemSize` must not overflow.
  - If overflow would occur, return an error to the user and cancel the operation.
- `capacity` CAN be zero.
  - Maximum value == `SIZE_MAX / elemSize`
- `elemSize` must be nonzero.

#### init() Postconditions

- After a successful init() call:
  - `length` = 0
  - `capacity` = user input
    - if `capacity == 0`, `data == NULL`
    - if `capacity > 0`, `data` points to at least `capacity * elemSize` bytes.
  - `elemSize` = user input
  - `data` = a valid pointer to the allocated buffer

#### init() Failure Conditions

- Return an error code
- Object is zeroed:
  - `length` = 0
  - `capacity` = 0
  - `elemSize` = 0
  - `data` = NULL
- This ensures the object can be safely destroyed or initialized again.

#### init() Tests

- Successful initialization
  - Start with a local Vectrum with garbage data (uninitialized).
  - Call `init(&v, 10, sizeof(int))`
  - Verify the following:
    - `length` == 0
    - `capacity` == 10
    - `elemSize` == `sizeof(int)`
    - `data` != NULL

- Zero Capacity Init
  - Start with a local Vectrum with garbage data (uninitialized).
  - Call `init(&v, 0, sizeof(int))`
  - Verify the following:
    - `length` == 0
    - `capacity` == 0
    - `elemSize` == `sizeof(int)`
    - `data` == NULL
  - ADDITIONAL TESTING:
    - Following the creation of a 0 cap Vectrum:
      - `pop()` should return an error and no-op.
      - `push()` should grow the array and allocate a buffer.

- Failure Path
  - Simulate out-of-memory condition.
    - `init()` should report a failure.
    - `&v` should be left in a safe state. (Zero Capacity)

- Re-init following a Destroy operation.
  - `init(&v, ...)`
  - `destroy(&v)`
  - `init(&v, ...)` again
  - Confirm that Vectrum behaves as a fresh vector each time. No leaks.

### destroy()

Destroy will handle destruction of the Vectrum. This will zero all numerical values within the Vectrum object, and set the data pointer to NULL.

Destroy should only be called against an initialized or 'zeroed' Vectrum. Calling destroy on an uninitialized Vectrum will result in undefined behavior.

#### destroy() Inputs

- A valid reference to a Vectrum object.

#### destroy() Preconditions

- The address must point to a valid Vectrum object which is either:
  - Initialized
  - In a 'zeroed' state due to destruction/failed init.

#### destroy() Postconditions

- After a successful `destroy()` call:
  - `length` = 0
  - `capacity` = 0
  - `elemSize` = 0
  - `data` = NULL

#### destroy() Failure Conditions

- None defined. Behavior is undefined if preconditions aren't met.

#### destroy() Tests

- Successful Destruction of a created Vectrum.
  - Vectrum should be 'zeroed'.

### push()

Push will handle adding new data to the Vectrum buffer. This will also handle growing a Vectrum which is at maximum capacity.

#### push() Inputs

- A valid reference to an Initialized Vectrum object.
- A reference to the data being pushed to the Vectrum.

#### push() Preconditions

- The reference provided is an initialized Vectrum.
- The data is of the appropriate type (or at least size, technically).
  - If the user violates this expectation, behavior is undefined.

#### push() Postconditions

- After a successful `push()`:
  - newLength = oldLength + 1
  - If `oldLength == oldCapacity` when `push()` is called:
    - newCapacity = oldCapacity * 2

#### push() Failure Conditions

- If growing the Vectrum would overflow or allocation fails:
  - Return an error code, do not change the Vectrum object.

#### push() Tests

- Successful push to an initialized Array.
  - Should meet `push()` postconditions.
  - New Vectrum is equal to old Vectrum plus the pushed data.

- Simulate OOM condition/unable to grow condition.
  - Should return an error code, and not change the Vectrum object.

- Vectrum @ max capacity.
  - Should return an error code and not change the Vectrum object.
