#include <stdio.h>
#include "container/list.h"

int main(void) {
  printf("Hello, World!\n");
  list_handle_t list = list_init();
  for (int i = 0; i < 100; i++) {
    list_push_back(list, i);
  }

  for(int i = 0; i < 100; i++) {
    printf("%lf %d", list_remove(list_end(list)), i);
  }
  list_destroy(list);
  return 0;
}
