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

using INTERPRETER::interpreter;
using NARSESEPARSER::NarseseParser;
using TASK::Task;

using std::string;

auto root = string("../examples/single_step");

bool isdigits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

int test_parse_nal(int i)
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
                    // std::cout << line << std::endl;
                    std::string input(line);
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
                            auto str = interpreter.interpret(*task);
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

int test_parse_line(string line)
{
    NarseseParser *parser = new NarseseParser;
    try
    {
        auto task = parser->parse_task(line);
        auto str = interpreter.interpret(*task);
        printf("%s\n", str.c_str());
    }
    catch(void*)
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


TEST(test_parser, test_parse_line)
{
    GTEST_ASSERT_EQ(test_parse_line("<(*,bird,plant) --> ?x>? "), 0);
}