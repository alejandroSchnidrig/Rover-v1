#include <gtest/gtest.h>

TEST(TestName, Subtest_1){
    ASSERT_FALSE(1==2);
}

int main(int argc, char **argv){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}