#include "scroll.c"
#include <stdio.h>

int main() {
  printf("%s\n", "Praise the Omnissiah!");

  MRC_Scroll scroll;

  int scroll_init = mrc_scroll_init(&scroll, 10, sizeof(int));

  if (scroll_init == SCROLL_OK) {
    printf("Scroll created successfully.\n");
  } else {
    printf("Something went wrong.\n");
  }

  int push_int = 42;
  int test_push = mrc_scroll_push(&scroll, &push_int);
  if (test_push != SCROLL_OK) {
    printf("Something went wrong with push. Error code: %d\n", test_push);
  } else {
    printf("Data pushed to scroll: %d\n", push_int);
  }

  int scan_res;
  int test_scan = mrc_scroll_scan(&scroll, &scan_res, 0);
  if (test_scan != SCROLL_OK) {
    printf("Something went wrong. Error code: %d\n", test_scan);
  }

  printf("Data at index %d was %d\n", 0, scan_res);

  int ins_res;
  push_int = 69;
  int test_insert = mrc_scroll_insert(&scroll, &push_int, 0);
  if (test_insert != SCROLL_OK) {
    printf("Something went wrong. Error code: %d\n", test_insert);
  } else {
    printf("Data pushed to scroll: %d\n", push_int);
  }

  push_int = 420;
  test_push = mrc_scroll_push(&scroll, &push_int);
  
  push_int = 80085;
  test_push = mrc_scroll_push(&scroll, &push_int);

  test_scan = mrc_scroll_scan(&scroll, &ins_res, 0);
  printf("Data at index %d was %d\n", 0, ins_res);
  test_scan = mrc_scroll_scan(&scroll, &ins_res, 1);
  printf("Data at index %d was %d\n", 1, ins_res);

  int rem_res;
  int test_remove = mrc_scroll_remove(&scroll, &rem_res, 0);
  if (test_remove != SCROLL_OK) {
    printf("Something went wrong. Error code: %d\n", test_remove);
  }
  printf("Data removed from scroll at index %d: %d\n", 0, rem_res);

  for (size_t i = 0; i < scroll.span; i++) {
    int scn, res;
    res = mrc_scroll_scan(&scroll, &scn, i);
    if (res == SCROLL_OK) {
      printf("scroll[%d] = %d\n", (int)i, scn);
    }
  }
  printf("scroll.span = %d\nscroll.limit = %d\nscroll.data = %p\n",
         (int)scroll.span, (int)scroll.limit, scroll.data);
}
