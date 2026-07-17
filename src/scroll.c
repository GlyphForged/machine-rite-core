#include "../include/mrc/scroll.h"
#include <string.h>

static void wipe_scroll(MRC_Scroll *scroll);

//=================================================================================================
// METHODS
//=================================================================================================

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

MRC_ScrollStatus mrc_scroll_push(MRC_Scroll *scroll, void *data)
{
  if (scroll == NULL || data == NULL) return SCROLL_ERR_ARG_INVALID;
  if (scroll -> span >= scroll -> limit) {
    size_t new_limit = scroll -> limit * 2;
    if (new_limit > SIZE_MAX / scroll -> unit_size) return SCROLL_ERR_OVERFLOW;
    void *new_buffer = realloc(scroll -> data, new_limit * scroll -> unit_size);
    if (new_buffer == NULL) return SCROLL_ERR_OOM;
    scroll -> data = new_buffer;
    scroll -> limit = new_limit;
  }
  char *dest = (char *)scroll -> data + (scroll -> span * scroll -> unit_size);
  memcpy(dest, data, scroll -> unit_size);
  scroll -> span++;   // Don't forget to increment the span, pendejo
  return SCROLL_OK;
}

MRC_ScrollStatus mrc_scroll_pop(MRC_Scroll *scroll, void *dest)
{
  if (scroll == NULL || dest == NULL) return  SCROLL_ERR_ARG_INVALID;
  if (scroll -> span < 1) return SCROLL_ERR_BOUNDS;
  char *src = (char *)scroll -> data + (scroll -> span * scroll -> unit_size);
  memcpy(dest, src, scroll -> unit_size);
  scroll -> span--;
  return SCROLL_OK;
}

//=================================================================================================
// STATIC METHODS
//=================================================================================================

/**
 * @brief Sets all int values to zero and sets the data pointer to NULL
 * 
 * The purpose of this helper method is primarily during initialization
 * and deletion of a scroll. The goal here is to ensure no junk data exists
 * within the struct on init, and that we clear any potential hanging
 * data/pointers on destruction. Maybe unnececssary, but cheap and safe.
 * 
 * @pre scroll must point to a valid MRC_Scroll struct
 * 
 * @param[in] scroll The address of the scroll to wipe
 */
static void wipe_scroll(MRC_Scroll *scroll)
{
  scroll -> data = NULL;
  scroll -> span = 0;
  scroll -> limit = 0;
  scroll -> unit_size = 0;
}