#include "scroll.c"
#include <stdio.h>

int main()
{
  printf("%s\n", "Praise the Omnissiah!");

  MRC_Scroll scroll;

  int scroll_init = mrc_scroll_init(&scroll, 10, sizeof(int));
  if (scroll_init == SCROLL_OK)
  {
    printf("Scroll created successfully.\n");
  } else {
    printf("Something went wrong.\n");
  }
}
