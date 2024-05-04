//
// Created by Alex on 19.04.2024.
//

#include "gtest/gtest.h"
extern "C" {
#include "node/bdlist.h"
}
TEST(bdlist, testEmpty) {
  bdlist_handle_t bdlist = bdlist_init();
  ASSERT_EQ(bdlist_is_empty(bdlist), true);
  bdlist_destroy(bdlist);
}
TEST(bdlist, testPushPopBackOne) {
  bdlist_handle_t bdlist = bdlist_init();
  bdlist_push_back(bdlist, 0);

  ASSERT_EQ(bdlist_is_empty(bdlist), false);
  ASSERT_EQ(bdlist_pop_back(bdlist), 0);

  ASSERT_EQ(bdlist_is_empty(bdlist), true);
}
TEST(bdlist, testPushPopBackMany) {
  bdlist_handle_t bdlist = bdlist_init();
  for (int i = 0; i < 100; i++) {
    bdlist_push_back(bdlist, i);
  }
  ASSERT_EQ(bdlist_is_empty(bdlist), false);
  for(int i = 99; i >= 0; i--) {
    ASSERT_EQ(bdlist_pop_back(bdlist), i);
  }
  ASSERT_EQ(bdlist_is_empty(bdlist), true);
}
TEST(bdlist, testPushPopFrontOne) {
  bdlist_handle_t bdlist = bdlist_init();
  bdlist_push_back(bdlist, 0);

  ASSERT_EQ(bdlist_is_empty(bdlist), false);
  ASSERT_EQ(bdlist_pop_back(bdlist), 0);

  ASSERT_EQ(bdlist_is_empty(bdlist), true);
}
TEST(bdlist, testPushPopFrontMany) {
  bdlist_handle_t bdlist = bdlist_init();
  for (int i = 0; i < 100; i++) {
    bdlist_push_front(&bdlist, i);
  }
  ASSERT_EQ(bdlist_is_empty(bdlist), false);
  for(int i = 99; i >= 0; i--) {
    ASSERT_EQ(bdlist_pop_front(&bdlist), i);
  }
  ASSERT_EQ(bdlist_is_empty(bdlist), true);
}
