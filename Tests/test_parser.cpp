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

int test_parse_nal(int i, bool colored = true)
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

int test_parse_line(string line, bool colored = true)
{
    auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
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
        return 1;
    }
    return 0;
}

TEST(test_parser, test_parse_nal1)
{
    GTEST_ASSERT_EQ(test_parse_nal(1), 0);
}

TEST(test_parser, test_parse_nal2)
{
    GTEST_ASSERT_EQ(test_parse_nal(2), 0);
}

TEST(test_parser, test_parse_nal3)
{
    GTEST_ASSERT_EQ(test_parse_nal(3), 0);
}

TEST(test_parser, test_parse_nal4)
{
    GTEST_ASSERT_EQ(test_parse_nal(4), 0);
}

TEST(test_parser, test_parse_nal5)
{
    GTEST_ASSERT_EQ(test_parse_nal(5), 0);
}

TEST(test_parser, test_parse_nal6)
{
    GTEST_ASSERT_EQ(test_parse_nal(6), 0);
}

TEST(test_parser, test_parse_nal7)
{
    GTEST_ASSERT_EQ(test_parse_nal(7), 0);
}

TEST(test_parser, test_parse_nal8)
{
    GTEST_ASSERT_EQ(test_parse_nal(8), 0);
}

TEST(test_parser, test_parse_nal9)
{
    GTEST_ASSERT_EQ(test_parse_nal(9), 0);
}

TEST(test_parser, test_parse_line1)
{
    GTEST_ASSERT_EQ(test_parse_line(R"((&/, a, b, (&/, c, d)).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((&/, a, b, (&/, c, d), e, (&|, f, g)).)"), 0);
    GTEST_ASSERT_EQ(test_parse_line(R"((&/, a, b, (&/, c, d), e, (&|, f, g, (&/, h, i), j), (&/, k, l, (&/, m, n, (&/, o, p)))).)"), 0);
}

TEST(test_parser, test_parse_line2)
{
    GTEST_ASSERT_EQ(test_parse_line("<(*, (*, (*, 0))) --> num>."), 0);
}

TEST(test_parser, test_parse_line3)
{
    GTEST_ASSERT_EQ(test_parse_line("(a - (b - c))."), 0);
    GTEST_ASSERT_EQ(test_parse_line("((a ~ b) ~ c)."), 0);
}

TEST(test_parser, test_parse_line4)
{
    GTEST_ASSERT_EQ(test_parse_line("(--, --a)."), 0);
    GTEST_ASSERT_EQ(test_parse_line("{{A}}."), 0);
    GTEST_ASSERT_EQ(test_parse_line("({A} | {B})."), 0);
    GTEST_ASSERT_EQ(test_parse_line("{{A}, {B}, {C}}."), 0);
}

TEST(test_parser, test_parse_line5)
{
    GTEST_ASSERT_EQ(test_parse_line("{{<$x-->A>}, {<$x-->B>}}."), 0);
    GTEST_ASSERT_EQ(test_parse_line("<(&&,<#1 --> lock>,<#1 --> (/,open,$2,_)>) ==> <$2 --> key>>. %1.00;0.90%"), 0);
    GTEST_ASSERT_EQ(test_parse_line("<<(*,$1,$2) --> like> <=> <(*,$2,$1) --> like>>?"), 0);
    GTEST_ASSERT_EQ(test_parse_line("(&&, <#x-->A>, <#x-->A>)."), 0);
    GTEST_ASSERT_EQ(test_parse_line("(&&, A, B)."), 0);
    GTEST_ASSERT_EQ(test_parse_line("(&&, B, A). %1.0;0.9%"), 0);
    GTEST_ASSERT_EQ(test_parse_line("(&&, B, A, A)."), 0);
}

TEST(test_parser, test_parse_line6)
{
    GTEST_ASSERT_EQ(test_parse_line("A.", true), 0);
    GTEST_ASSERT_EQ(test_parse_line("(A & B).", true), 0);
}

TEST(test_parser, test_parse_line7)
{
    auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
    GTEST_ASSERT_EQ(test_parse_line("(&&, <#x-->A>, <#x-->A>)."), 0);
    auto task = parser->parse_task("(&&, <#x-->A>, <#x-->A>).");
    GTEST_ASSERT_NE(task->sentence->term->terms, nullptr);
    GTEST_ASSERT_EQ(task->sentence->term->terms->size(), 1);
}

TEST(test_parser, test_parse_line8)
{
    auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
    auto task = parser->parse_task("((h && a) * b * f * (g || (c & d & e))).");
    // auto task = parser->parse_task("(g ||(c & d & e)).");
    GTEST_ASSERT_NE(task, nullptr);
    GTEST_ASSERT_EQ(test_parse_line("((h && a) * b * f * (g || (c & d & e)))."), 0);
}

TEST(test_parser, test_parse_line9)
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

TEST(test_parser, test_parse_line10)
{
    // std::cout << "(&, {<$x-->A>, <$x-->B>, <$y-->A>}, {<$y-->B>, <$y-->A>}, [<$x-->A>, <$x-->B>, <$y-->A>], [<$y-->B>, <$y-->A>])." << std::endl << "|- " << "(&, {<$y-->A>}, [<$x-->A>, <$x-->B>, <$y-->A>, <$y-->B>])." << std::endl;
    // GTEST_ASSERT_EQ(test_parse_line("(&, {<$x-->A>, <$x-->B>, <$y-->A>}, {<$y-->B>, <$y-->A>}, [<$x-->A>, <$x-->B>, <$y-->A>], [<$y-->B>, <$y-->A>])."), 0);
    // GTEST_ASSERT_EQ(test_parse_line("(&&, <$x-->A>, <$y-->A>)."), 0);

    // auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
    // auto task = parser->parse_task("(&&, <$x-->A>, <$y-->A>).");
    // GTEST_ASSERT_NE(task, nullptr);
    GTEST_ASSERT_EQ(test_parse_line("(&, {<$x-->A>, <$x-->B>, <$y-->A>}, {<$y-->B>, <$y-->A>}, [<$x-->A>, <$x-->B>, <$y-->A>], [<$y-->B>, <$y-->A>])."), 0);
    // GTEST_ASSERT_EQ(test_parse_line("(&, {<$x-->A1>, <$x-->B1>, <$y-->A>}, {<$y-->B2>, <$y-->A>})."), 0);

}

TEST(test_parser, test_parse_line11)
{
    auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
    auto task = parser->parse_task("<A-->B>.");
    GTEST_ASSERT_EQ(test_parse_line("<A-->B>."), 0);
    GTEST_ASSERT_NE(task, nullptr);
}