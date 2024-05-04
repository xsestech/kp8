//
// Created by Alex on 16.03.2024.
//
#include "gtest/gtest.h"
extern "C" {
  void __ubsan_on_report() {
    FAIL() << "Encountered an undefined behavior sanitizer error";
  }
  void __asan_on_error() {
    FAIL() << "Encountered an address sanitizer error";
  }
  void __tsan_on_report() {
    FAIL() << "Encountered a thread sanitizer error";
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}