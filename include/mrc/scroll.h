#include <stdint.h>
#include <stdlib.h>

/**
 * @brief A Scroll struct
 */
typedef struct{
  void *data;         // Address of the data backing buffer
  size_t span;        // Current length of the data
  size_t limit;       // Maximum length of the current buffer
  size_t unit_size;   // Size of each unit of data
} MRC_Scroll;

enum {
  SCROLL_OK = 0,
  SCROLL_ERR_OOM,
  SCROLL_ERR_OVERFLOW,
  SCROLL_ERR_SIZE_INVALID,
  SCROLL_ERR_ARG_INVALID,
  SCROLL_ERR_SIZE_ZERO,
  SCROLL_ERR_BOUNDS,
};

/**
 * @brief Initializes a an uninitialized scroll
 *
 * @pre pointer must be an uninitialized MRC_Scroll
 *
 * @param[in] scroll The address of an unitialized scroll created by the user
 * @param[in] capacity The starting capacity of the scroll will default to 2 if one is not provided or if the value provided is <2.
 * @param[in] unit_size The 'width' of the data being stored.
 *
 * @return An int indicating success/failure. (0 = success, else failure code)
 */
int mrc_scroll_init(MRC_Scroll *scroll, size_t capacity, size_t unit_size);

/**
 * @brief Delete a scroll, freeing its backing buffer.
 *
 * @pre pointer must be to an initialized MRC_Scroll
 *
 * @param[in] scroll The address of the scroll to be deleted.
 *
 * @return An int indicating success/failure. (0 = success, else failure code)
 */
int mrc_scroll_purge(MRC_Scroll *scroll);
