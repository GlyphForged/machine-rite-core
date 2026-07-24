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

  test_scan = mrc_scroll_scan(&scroll, &ins_res, 0);
  printf("Data at index %d was %d\n", 0, ins_res);
  test_scan = mrc_scroll_scan(&scroll, &ins_res, 1);
  printf("Data at index %d was %d\n", 1, ins_res);
}
