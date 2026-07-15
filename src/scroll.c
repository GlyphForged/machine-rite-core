#include "vectrum.h"
#include <stdint.h>
#include <stdlib.h>

int mrc_scroll_init(Scroll *scroll, size_t capacity, size_t u_size)
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
  scroll -> span = capacity;
  scroll -> unit_size = u_size;
  void* buffer = malloc(capacity * u_size);
  if (buffer == NULL) return VECTRUM_ERR_OOM;
  scroll -> data = buffer;
  return SCROLL_OK;
}
