/*
 * Vectrum - A custom dynamic array
 *
 * MVP Goals:
 * - contiguous block of values
 * - Stores elements in a contiguous buffer
 * - `elemSize` set at initialization
 * - Manages the backing buffer's lifetime
 * 
 * MVP Functionality:
 *  - create (&VectrumPtr, initialCapacity, dataType/elemSize)
 *  - destroy (&VectrumPtr)
 *  - currentLength (&VectrumPtr)
 *  - capacity (&VectrumPtr)
 *  - pushElement(&VectrumPtr, data)
 *  - popElement(&VectrumPtr)
 *  - randomAccess(&VectrumPtr, index)
 *  - removeElement(&VectrumPtr, index)
 *  - clear(&VectrumPtr)
 * 
 * Stretch Goals:
 * - Additional functionality:
 *  - Vectrum of pointers functionality for heterogeneous data
 * 
 * Plain English Explanation:
 * The Vectrum struct itself will include 4 key pieces of data: 
 *    - the current length of the vector
 *    - the maximum size of the vector
 *    - the element size of the vector
 *    - a pointer to the start of the allocated block of memory
 * 
 * Creation of an empty vector involves:
 *    - User creates a new Vectrum struct containing placeholder 'header' data
 *    - vector_init:
 *      - sets the initial values and allocates a block of memory of the appropriate size
 *      - sets the length of the vector to 0
 *      - stores the address of the start of the allocated block of memory in the user-owned Vectrum struct
 * 
 * So the user of the vector library creates a new Vectrum object, and then calls `init` on the struct,
 * passing in the data type and the desired initial capacity, along with a pointer to the Verctrum object
 * the user created. init calls malloc to get a chunk of data of the appropriate size, then uses the pointer
 * to update the Vectrum object with the appropriate information, namely: The capacity, the current length,
 * the size of each item, and a pointer to the address of the allocated block of memory.
 *
 * Vectrum Contains:
 * - length: size_t
 *    - The current length of the array, as a positive integer
 *    - Never needs to be below 0
 * - capacity: size_t
 *    - The current maximum length of the array, as a positive integer
 *    - Never needs to be below 0
 * - elemSize: size_t
 *    - The size of each element of the array
 * - data: ptr*
 *    - A pointer to the data buffer
 * Invariants:
 * - Length is always less than or equal to Capacity, neither are ever below 0.
 * - If capacity is > 0, data will always hold a valid pointer to a block of size: capacity * elemSize
 * - Only buffer elements within the domain [0, length] are valid
 * - elemSize, once set, is never changed, and always > 0.
 * - The Vectrum owns the memory pointed to by data
 * - Only the Vectrum may free(data)
 * - On destroy: data = NULL; length = 0; capacity = 0;
 * - Potential states:
 *    - Uninitialized
 *    - Initialized
 *    - Destroyed
 *  - Calling any function except `init` on an Uninitialized function will return `Undefined`.
 *  - The only valid function you can call on a Destroyed Vectrum is `init`
 *  - If capacity > 0, `capacity * elemSize` <= `size_t`
 *
 * TODO:
 * - Work out what the Vectrum looks like in each of these states:
 *   - Newly created empty Vectrum.
 *   - Vectrum with 3 elements added.
 *   - Vectrum after pushing an element that forces a grow operation.
 *   - Vectrum after destruction.
 */
