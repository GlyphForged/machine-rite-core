/**
 * @brief A Scroll struct
 */
typedef struct{
  void* data;         // Address of the data backing buffer
  size_t span;        // Current length of the data
  size_t limit;       // Maximum length of the current buffer
  size_t unit_size;   // Size of each unit of data
} MRC_Scroll;

enum {
  SCROLL_OK = 0,
  SCROL_ERR_OOM,
  SCROLL_ERR_OVERLFOW,
  SCROLL_ERR_SIZE_INVALID,
  SCROLL_ERR_ARG_INVALID,
  SCROLL_ERR_SIZE_ZERO,
  SRCOLL_ERR_BOUNDS,
};

/**
 * @brief Initializes a scroll.
 * @param[in] scroll The address of an unitialized scroll created by the user
 * @param[in] capacity The starting capacity of the scroll
 * @param[in] unit_size The 'width' of a unit of data
 * @usage MRC_Scroll* myscroll = mrc_scroll_init(10, sizeof(myStruct))
 */
int mrc_scroll_init(Scroll *scroll, size_t capacity, size_t unit_size);
