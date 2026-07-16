#include "../include/mrc/scroll.h"

int mrc_scroll_init(MRC_Scroll *scroll, size_t capacity, size_t u_size)
{
  // Check for immediate fail states
  if (scroll == NULL) return SCROLL_ERR_ARG_INVALID;
  if (capacity < 1) return SCROLL_ERR_SIZE_INVALID;
  if (capacity > SIZE_MAX / u_size) return SCROLL_ERR_OVERFLOW;
  
  // Ensure clean starting point.
  scroll -> data = NULL;
  scroll -> span = 0;
  scroll -> limit = 0;
  scroll -> unit_size = 0;

  // Set the settings
  scroll -> limit = capacity;
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
  scroll -> span = NULL;
  scroll -> limit = NULL;
  scroll -> unit_size = NULL;
  return SCROLL_OK;
}
