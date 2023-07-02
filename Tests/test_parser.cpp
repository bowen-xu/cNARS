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
#include <unordered_map>

using INTERPRETER::interpreter;
using NARSESEPARSER::NarseseParser;
using TASK::Task;

using std::string;

auto root = string("../examples/single_step");

bool isdigits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

int test_parse_nal(int i, bool colored=true)
{
    NarseseParser *parser = new NarseseParser;

    glob_t globbuf;
    int err = glob(fmt::format((root + "/nal{}/*.nal"), i).c_str(), 0, NULL, &globbuf);
    if (err == 0)
    {
        for (size_t i = 0; i < globbuf.gl_pathc; i++)
        {
            auto path = globbuf.gl_pathv[i];
            printf("Parsing \"%s\" ...\n", path);
            std::ifstream file(path); // 替换为实际文件路径

            if (file.is_open())
            {
                std::string line;
                while (std::getline(file, line))
                {
                    std::string input(line);
                    boost::algorithm::trim(input);
                    if (isdigits(input))
                    {
                    }
                    else if (input.starts_with('\''))
                    {
                    }
                    else
                    {
                        boost::trim(input);
                        if (input.length() > 0)
                        {
                            auto task = parser->parse_task(input);
                            auto str = interpreter.interpret(*task, colored);
                            printf("%s\n", str.c_str());
                        }
                    }
                }
                file.close();
            }
            else
            {
                std::cout << "Unable to open the file." << std::endl;
            }
        }
        globfree(&globbuf);
    }
    else
    {
        printf("error\n");
        delete parser;
        return 1;
    }
    delete parser;
    return 0;
}

int test_parse_line(string line, bool colored=true)
{
    NarseseParser *parser = new NarseseParser;
    try
    {
        auto task = parser->parse_task(line);
        // auto& term = task->term();
        // std::cout << term << std::endl;;
        if (task != nullptr)
        {
            auto str = interpreter.interpret(*task, colored);
            printf("%s\n", str.c_str());
        }
        else
        {
            printf("Parse failed.\n");
        }
    }
    catch (void *)
    {
        delete parser;
        return 1;
    }
    delete parser;
    return 0;
}

// TEST(test_parser, test_parse_nal1)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(1), 0);
// }

// TEST(test_parser, test_parse_nal2)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(2), 0);
// }

// TEST(test_parser, test_parse_nal3)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(3), 0);
// }

// TEST(test_parser, test_parse_nal4)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(4), 0);
// }

// TEST(test_parser, test_parse_nal5)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(5), 0);
// }

// TEST(test_parser, test_parse_nal6)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(6), 0);
// }

// TEST(test_parser, test_parse_nal7)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(7), 0);
// }

// TEST(test_parser, test_parse_nal8)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(8), 0);
// }

// TEST(test_parser, test_parse_nal9)
// {
//     GTEST_ASSERT_EQ(test_parse_nal(9), 0);
// }


TEST(test_parser, test_parse_line)
{
    // GTEST_ASSERT_EQ(test_parse_line("<robin{-]bird>."), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((a & b).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((a | b).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((a &| b).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((a &/ b).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((a && b).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((a || b).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((a * b).)"), 0);

    GTEST_ASSERT_EQ(test_parse_line(R"((a * b * c).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"(((h && a) * b * f * (g || (c & d & e))).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"(((h && (a * b * f * g)) || (c & d & e)).)"), 0);
}