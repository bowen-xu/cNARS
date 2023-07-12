#include <string>
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    // testing::GTEST_FLAG(filter) = "test_parser.*:test_terms.*:test_term.*";
    testing::GTEST_FLAG(filter) = "test_parser.*";
    // testing::GTEST_FLAG(filter) = "test_term.*";
    // testing::GTEST_FLAG(filter) = "test_terms.test_insert";
    return RUN_ALL_TESTS();
}