#include <string>
#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    testing::GTEST_FLAG(filter) = "test_parser.*:test_terms.*";
    return RUN_ALL_TESTS();
}