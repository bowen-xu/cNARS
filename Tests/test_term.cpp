#include <fmt/core.h>
#include <fstream>
#include <glob.h>
#include <gtest/gtest.h>
#include <iostream>
#include <string>

#include "Interpreter/include/Interpreter.hpp"
#include "Narsese/Parser/NarseseParser.h"
#include "Narsese/include/Task.h"
#include <boost/algorithm/string.hpp>

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <map>
#include <memory>
#include <unordered_map>

using INTERPRETER::interpreter;
using NARSESEPARSER::NarseseParser;
using TASK::Task;

using std::string;

TEST(test_term, test_term_equal1)
{
    // GTEST_ASSERT_EQ(test_parse_line("A.", true), 0);
    // NarseseParser parser = NarseseParser();
    auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
    auto task1 = parser->parse_task("robin.");
    GTEST_ASSERT_NE(task1, nullptr);
    auto term1 = *task1->sentence->term;
    auto task2 = parser->parse_task("robin.");
    GTEST_ASSERT_NE(task2, nullptr);
    auto term2 = *task2->sentence->term;
    GTEST_ASSERT_TRUE(term1 == term2);
}

TEST(test_term, test_term_equal2)
{
    auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
    auto task1 = parser->parse_task("<robin-->bird>.");
    GTEST_ASSERT_NE(task1, nullptr);
    auto term1 = *task1->sentence->term;
    auto task2 = parser->parse_task("<robin-->bird>.");
    GTEST_ASSERT_NE(task2, nullptr);
    auto term2 = *task2->sentence->term;
    GTEST_ASSERT_TRUE(term1 == term2);
}

TEST(test_term, test_term_equal3)
{
    auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
    auto task1 = parser->parse_task("(&&, A, B).");
    GTEST_ASSERT_NE(task1, nullptr);
    auto term1 = *task1->sentence->term;
    auto task2 = parser->parse_task("(&&, A, B).");
    GTEST_ASSERT_NE(task2, nullptr);
    auto term2 = *task2->sentence->term;
    GTEST_ASSERT_TRUE(term1 == term2);
}