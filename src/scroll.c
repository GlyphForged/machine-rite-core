#include "../include/mrc/scroll.h"

static void wipe_scroll(MRC_Scroll *scroll)
{
  scroll -> data = NULL;
  scroll -> span = 0;
  scroll -> limit = 0;
  scroll -> unit_size = 0;
}

int mrc_scroll_init(MRC_Scroll *scroll, size_t capacity, size_t u_size)
{
  // Check for immediate fail states
  if (scroll == NULL) return SCROLL_ERR_ARG_INVALID;
  if (capacity > SIZE_MAX / u_size) return SCROLL_ERR_OVERFLOW;
  
  // Ensure clean starting point.
  wipe_scroll(scroll);

  // Configure the scroll
  if (capacity < 2) {
    scroll -> limit = 2;
      } else {
    scroll -> limit = capacity;
  }
  scroll -> unit_size = u_size;
  void *buffer = malloc(capacity * u_size);
  if (buffer == NULL) return SCROLL_ERR_OOM;
  scroll -> data = buffer;
  return SCROLL_OK;
}

int mrc_scroll_purge(MRC_Scroll *scroll)
{
  if (scroll == NULL) return SCROLL_ERR_ARG_INVALID;
  free(scroll -> data);
  wipe_scroll(scroll);
  return SCROLL_OK;
}
