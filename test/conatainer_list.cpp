//
// Created by Alex on 19.04.2024.
//

#include "gtest/gtest.h"

extern "C" {
#include "container/list.h"
}

TEST(containerList, testEmpty) {
  list_handle_t list = list_init();
  ASSERT_EQ(list_is_empty(list), true);
  list_destroy(list);
}
TEST(containerList, testPushPopBackOne) {
  list_handle_t list = list_init();
  list_push_back(list, 0);

  ASSERT_EQ(list_is_empty(list), false);
  ASSERT_EQ(list_remove(list_end(list)), 0);

  ASSERT_EQ(list_is_empty(list), true);
  list_destroy(list);
}
TEST(containerList, testPushPopMany) {
  list_handle_t list = list_init();
  for (int i = 0; i < 100; i++) {
    list_push_back(list, i);
  }
  ASSERT_EQ(list_is_empty(list), false);
  int i = 0;
  for (list_iter_t iter = list_begin(list); list_iter_equal(iter, list_iter_null(list)); iter = list_iter_next(iter)) {
    ASSERT_EQ(list_iter_val(iter), i);
    i++;
  }
  list_destroy(list);
}
TEST(containerList, testPushPopBackMany) {
  list_handle_t list = list_init();
  for (int i = 0; i < 100; i++) {
    list_push_back(list, i);
  }
  ASSERT_EQ(list_is_empty(list), false);
  for (int i = 99; i >= 0; i--) {
    ASSERT_EQ(list_remove(list_end(list)), i);
  }
  ASSERT_EQ(list_is_empty(list), true);
  list_destroy(list);
}

TEST(containerList, testReverse) {
  list_handle_t list = list_init();
  for (int i = 0; i < 100; i++) {
    list_push_back(list, i);
  }
  ASSERT_EQ(list_is_empty(list), false);
  list_reverse(list);
  for (int i = 0; i < 100; i++) {
    ASSERT_EQ(list_remove(list_end(list)), i);
  }
  ASSERT_EQ(list_is_empty(list), true);
  list_destroy(list);
}

TEST(containerList, testComplexRemove) {
  list_handle_t list = list_init();
  for (int i = 0; i < 100; i++) {
    list_push_back(list, i);
  }
  ASSERT_EQ(list_is_empty(list), false);
  list_iter_t iter = list_begin(list);
  for (int i = 0; i < 100; i++) {
    list_iter_t tmp = iter;
    iter = list_iter_next(iter);
    if (i % 2 == 0) {
      list_remove(tmp);
    }
  }
  int i = 1;
  for (iter = list_begin(list); list_iter_equal(iter, list_iter_null(list)); iter = list_iter_next(iter)) {
    ASSERT_EQ(list_iter_val(iter), i);
    i += 2;
  }
  for (i = 100; i < 200; i++) {
    list_push_back(list, i);
  }
  i = 1;
  for (iter = list_begin(list); list_iter_equal(iter, list_iter_null(list)); iter = list_iter_next(iter)) {
    if (i <= 99) {
      ASSERT_EQ(list_iter_val(iter), i);
      i += 2;
    } else {
      ASSERT_EQ(list_iter_val(iter), i - 1);
      i++;
    }
  }

  list_destroy(list);

}
