#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "kmeans.hpp"

TEST(thisPasses, helloHello) {
    ASSERT_EQ("hello", "hello");
}
TEST(thisFails,helloWorld) {
    ASSERT_EQ("hello", "world");
}