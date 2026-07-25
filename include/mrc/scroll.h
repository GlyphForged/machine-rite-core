#pragma once
#include <stdint.h>
#include <stdlib.h>

/**
 * @brief A dynamic array container managing a contiguous backing buffer
 */
typedef struct {
  void *data;       // Address of the data backing buffer
  size_t span;      // Current length of the data
  size_t limit;     // Maximum unit capacity of the buffer
  size_t unit_size; // Size of each unit of data in bytes
} MRC_Scroll;

/**
 * @brief Error codes returned by the Scroll API
 */
typedef enum {
  SCROLL_OK = 0,           ///< Operation completed successfully
  SCROLL_ERR_OOM,          ///< Out of memory (allocation failed)
  SCROLL_ERR_OVERFLOW,     ///< Requested allocation size sxceeds MAX_SIZE limit
  SCROLL_ERR_SIZE_INVALID, ///< Requested capacity size is out of acceptable
                           ///< bounds
  SCROLL_ERR_ARG_INVALID,  ///< A passed argument pointer was NULL
  SCROLL_ERR_SIZE_ZERO,    ///< The unit size cannot be zero
  SCROLL_ERR_BOUNDS,       ///< Attempted to access an index out of bounds
} MRC_ScrollStatus;

/**
 * @brief Initiazlies a scroll struct and allocates its backing buffer
 *
 * @pre scroll must point to a valid, allocated memory location
 * @post On success, scroll->data points to a buffer of size (capacity *
 * unit_size) On failure, the struct members are cleared or left unchanged
 *
 * @param[in,out] scroll        The address of an unitialized scroll created by
 * the user
 * @param[in]     capacity      The starting capacity will default to 2 if the
 * value provided is < 2
 * @param[in]     unit_size     The size of a single element in bytes. Must be >
 * 0
 *
 * @return 0 on success, or a non-zero SCROLL_ERR error code on failure
 */
MRC_ScrollStatus mrc_scroll_init(MRC_Scroll *scroll, size_t capacity,
                                 size_t unit_size);

/**
 * @brief Frees the backing buffer of a scroll and zeroes its members
 *
 * @pre scroll must point to an initialized MRC_Scroll struct
 *
 * @param[in,out]   scroll    The address of the scroll to be deleted
 *
 * @return 0 on success, or SCROLL_ERR_ARG_INVALID if scroll is NULL
 */
MRC_ScrollStatus mrc_scroll_purge(MRC_Scroll *scroll);

/**
 * @brief Pushes a new element onto the end of the scroll, resizing if necessary
 *
 * @pre scroll must point to an initialized MRC_Scroll struct
 * @pre data must point to a valid memory location of size scroll->unit_size
 * @pre data must not point into scroll->data
 *
 * @param[in,out]   scroll    The address of the scroll to push data onto
 * @param[in]       data      The address of the data to be pushed onto the
 * scroll
 *
 * @return 0 on success, or a non-zero SCROLL_ERR error code on failure
 */
MRC_ScrollStatus mrc_scroll_push(MRC_Scroll *scroll, void *data);

/**
 * @brief Pops an element off the end of the scroll, copying the data to a
 * destination buffer
 *
 * This is a destructive operation on the scroll.
 *
 * @pre scroll must point to an initialized MRC_Scroll struct
 * @pre dest must point to a valid buffer of the appropriate size
 *
 * @param[in]       scroll    The address of the scroll to pop the data from
 * @param[in, out]  dest      The address of the destination buffer
 *
 * @return 0 on success, or a non-zer SCROLL_ERR error code on failure
 */
MRC_ScrollStatus mrc_scroll_pop(MRC_Scroll *scroll, void *dest);

/**
 * @brief Provides a copy of the data at a given index location
 * (non-destructive)
 *
 * @pre scroll must point to an initialized MRC_Scroll struct
 * @pre dest must point to a valid destination buffer of size scroll->unit_size
 *
 * @param[in]       scroll  The address of the scroll
 * @param[in, out]  dest    The address of a destination buffer
 * @param[in]       index   The index of the data you want
 *
 * @return 0 on success, or a non-zero SCROLL_ERR error code on failure
 */
MRC_ScrollStatus mrc_scroll_scan(MRC_Scroll *scroll, void *dest, size_t index);

/**
 * @brief Inserts a new element into the the scroll at a given index, resizing
 * if necessary
 *
 * @pre scroll must point to an initialized MRC_Scroll struct
 * @pre data must point to a valid memory location of size scroll->unit_size
 * @pre data must not point into scroll->data
 * @pre index must not be greater than span or less than zero
 *
 * @param[in,out]   scroll    The address of the scroll to push data onto
 * @param[in]       data      The address of the data to be inserted into the
 *                           scroll
 * @param[in]       index     The index where data will be inserted
 *
 * @return 0 on success, or a non-zero SCROLL_ERR error code on failure
 */
MRC_ScrollStatus mrc_scroll_insert(MRC_Scroll *scroll, void *data, size_t index);

/**
 * @brief Provides a copy of data at a given location and removes it from the
 * scroll
 *
 * This is a destructive operation on the scroll
 *
 * @pre scroll must point to an initialized MRC_Scroll struct
 * @pre dest must point to a valid destination buffer of size scroll->unit_size
 *
 * @param[in]       scroll  The address of the scroll
 * @param[in, out]  dest    The address of a destination buffer
 * @param[in]      index    The index to be removed
 *
 * @return 0 on success, or a non-zero SCROLL_ERR error code on failure
 */
MRC_ScrollStatus mrc_scroll_remove(MRC_Scroll *scroll, void *dest, size_t index);
