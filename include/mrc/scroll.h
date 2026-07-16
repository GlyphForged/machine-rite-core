#include <stdint.h>
#include <stdlib.h>

/**
 * @brief A dynamic array container managing a contiguous backing buffer
 */
typedef struct{
  void *data;         // Address of the data backing buffer
  size_t span;        // Current length of the data
  size_t limit;       // Maximum unit capacity of the buffer
  size_t unit_size;   // Size of each unit of data in bytes
} MRC_Scroll;

/**
 * @brief Error codes returned by the Scroll API
 */
typedef enum {
  SCROLL_OK = 0,            ///< Operation completed successfully
  SCROLL_ERR_OOM,           ///< Out of memory (allocation failed)
  SCROLL_ERR_OVERFLOW,      ///< Requestedallocation size sxceeds MAX_SIZE limit
  SCROLL_ERR_SIZE_INVALID,  ///< Requested capacity size is out of acceptable boudns
  SCROLL_ERR_ARG_INVALID,   ///< A passed argument pointer was NULL
  SCROLL_ERR_SIZE_ZERO,     ///< The unit size cannot be zero
  SCROLL_ERR_BOUNDS,        ///< Attempted to access an index out of bounds
} MRC_ScrollStatus;

/**
 * @brief Initiazlies a scroll struct and allocates its backing buffer
 *
 * @pre scroll must point to a valid, allocated memory location
 * @post On success, scroll->data points to a buffer of size (capacity * unit_size)
 *       On failure, the struct members are cleared or left unchanged
 *
 * @param[in,out] scroll        The address of an unitialized scroll created by the user
 * @param[in]     capacity      The starting capacity of the scroll will default to 2 if one is not provided or if the value provided is < 2
 * @param[in]     unit_size     The size of a single element in bytes. Must be > 0
 *
 * @return 0 on success, or a non-zero SCROLL_ERR error code on failure
 */
MRC_ScrollStatus mrc_scroll_init(MRC_Scroll *scroll, size_t capacity, size_t unit_size);

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
