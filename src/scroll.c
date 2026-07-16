#include "../include/mrc/scroll.h"

static void wipe_scroll(MRC_Scroll *scroll)
{
  scroll -> data = NULL;
  scroll -> span = 0;
  scroll -> limit = 0;
  scroll -> unit_size = 0;
}

MRC_ScrollStatus mrc_scroll_init(MRC_Scroll *scroll, size_t capacity, size_t u_size)
{
  // Check for immediate fail states
  if (scroll == NULL) return SCROLL_ERR_ARG_INVALID;
  if (capacity > SIZE_MAX / u_size) return SCROLL_ERR_OVERFLOW;
  if (u_size == 0) return SCROLL_ERR_SIZE_INVALID;
  
  // Ensure clean starting point.
  wipe_scroll(scroll);

  // Configure the scroll
  if (capacity < 2) {
    capacity = 2;
  }
  void *buffer = malloc(capacity * u_size);
  if (buffer == NULL) return SCROLL_ERR_OOM;
  scroll -> limit = capacity;
  scroll -> unit_size = u_size;
  scroll -> data = buffer;
  return SCROLL_OK;
}

MRC_ScrollStatus mrc_scroll_purge(MRC_Scroll *scroll)
{
  if (scroll == NULL) return SCROLL_ERR_ARG_INVALID;
  free(scroll -> data);
  wipe_scroll(scroll);
  return SCROLL_OK;
}
