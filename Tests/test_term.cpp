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

// TEST(test_term, test_term_equal1)
// {
//     // GTEST_ASSERT_EQ(test_parse_line("A.", true), 0);
//     // NarseseParser parser = NarseseParser();
//     auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
//     auto task1 = parser->parse_task("robin.");
//     GTEST_ASSERT_NE(task1, nullptr);
//     auto term1 = *task1->sentence->term;
//     auto task2 = parser->parse_task("robin.");
//     GTEST_ASSERT_NE(task2, nullptr);
//     auto term2 = *task2->sentence->term;
//     GTEST_ASSERT_TRUE(term1 == term2);
// }

// TEST(test_term, test_term_equal2)
// {
//     auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
//     auto task1 = parser->parse_task("<robin-->bird>.");
//     GTEST_ASSERT_NE(task1, nullptr);
//     auto term1 = *task1->sentence->term;
//     auto task2 = parser->parse_task("<robin-->bird>.");
//     GTEST_ASSERT_NE(task2, nullptr);
//     auto term2 = *task2->sentence->term;
//     GTEST_ASSERT_TRUE(term1 == term2);
// }

// TEST(test_term, test_term_equal3)
// {
//     auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);
//     auto task1 = parser->parse_task("(&&, A, B).");
//     GTEST_ASSERT_NE(task1, nullptr);
//     auto term1 = *task1->sentence->term;
//     auto task2 = parser->parse_task("(&&, A, B).");
//     GTEST_ASSERT_NE(task2, nullptr);
//     auto term2 = *task2->sentence->term;
//     GTEST_ASSERT_TRUE(term1 == term2);
// }

// TEST(test_term, test_clone_variable)
// {
//     auto var1 = VARIABLE::Variable(VARIABLE::VarPrefix::Independent, "x");
//     auto var2 = VARIABLE::Variable(var1);
//     bool is_true = (var1._vars_independent.get() == var2._vars_independent.get());
//     GTEST_ASSERT_TRUE(!(var1._vars_independent == var2._vars_independent));
// }

// TEST(test_term, test_clone_statement)
// {
//     using COPULA::Copula;
//     using STATEMENT::Statement;
//     using TERM::Term;

//     auto task = NARSESEPARSER::parser->parse_task("<(&&, <#x-->A>, <#x-->B>, <$y-->C>, <$z-->D>) ==> (&&, <$y-->D>, <$z-->E>)>.");
//     auto stat1 = task.term();
//     auto stat2 = Statement((Statement &)*stat1, true);
//     auto str1 = interpreter.interpret(*stat1);
//     std::cout << str1 << std::endl;
//     auto str2 = interpreter.interpret(stat2);
//     std::cout << str2 << std::endl;
//     GTEST_ASSERT_EQ(str1, str2);
//     GTEST_ASSERT_NE(stat1->_vars_independent.get(), stat2._vars_independent.get());

//     size_t sum = 0;
//     for (auto i = 0; i < 2.5e5; i++)
//     {
//         auto stat3 = Statement((Statement &)*stat1, true);
//         sum += stat3.complexity;
//     }
//     std::cout << sum << std::endl;
// }

// TEST(test_term, test_clone_statement2)
// {
//     using COPULA::Copula;
//     using STATEMENT::Statement;
//     using TERM::Term;

//     auto task = NARSESEPARSER::parser->parse_task("<robin --> bird>.");
//     auto stat1 = task.term();
//     auto stat2 = Statement((Statement &)*stat1, true);
//     auto str1 = interpreter.interpret(*stat1);
//     std::cout << str1 << std::endl;
//     auto str2 = interpreter.interpret(stat2);
//     std::cout << str2 << std::endl;
//     GTEST_ASSERT_EQ(str1, str2);
//     GTEST_ASSERT_NE(stat1->_vars_independent.get(), stat2._vars_independent.get());

//     size_t sum = 0;
//     for (auto i = 0; i < 2.5e5; i++)
//     {
//         auto stat3 = Statement((Statement &)*stat1, true);
//         sum += stat3.complexity;
//     }
//     std::cout << sum << std::endl;
// }

// TEST(test_term, test_clone_statement3)
// {
//     using COPULA::Copula;
//     using STATEMENT::Statement;
//     using TERM::Term;

//     auto task = NARSESEPARSER::parser->parse_task("<<$x-->robin> ==> <$x-->bird>>.");
//     auto stat1 = task.term();
//     auto stat2 = Statement((Statement &)*stat1, true);
//     auto str1 = interpreter.interpret(*stat1);
//     std::cout << str1 << std::endl;
//     auto str2 = interpreter.interpret(stat2);
//     std::cout << str2 << std::endl;
//     GTEST_ASSERT_EQ(str1, str2);
//     GTEST_ASSERT_NE(stat1->_vars_independent.get(), stat2._vars_independent.get());

//     size_t sum = 0;
//     for (auto i = 0; i < 2.5e5; i++)
//     {
//         auto stat3 = Statement((Statement &)*stat1, true);
//         // auto stat3 = Statement::deepcopy((Statement &)*stat1);
//         sum += stat3.complexity;
//     }
//     std::cout << sum << std::endl;
// }


// TEST(test_term, test_clone_compound1)
// {
//     // TODO: Continue here.
//     using COPULA::Copula;
//     using COMPOUND::Compound;
//     using TERM::Term;

//     auto task = NARSESEPARSER::parser->parse_task("(&&, <$x-->robin>, <$x-->bird>).");
//     auto cmpd1 = task.term();
//     auto cmpd2 = Compound((Compound &)*cmpd1, true);
//     auto str1 = interpreter.interpret(*cmpd1);
//     std::cout << str1 << std::endl;
//     auto str2 = interpreter.interpret(cmpd2);
//     std::cout << str2 << std::endl;
//     GTEST_ASSERT_EQ(str1, str2);
//     GTEST_ASSERT_NE(cmpd1->_vars_independent.get(), cmpd2._vars_independent.get());

//     size_t sum = 0;
//     for (auto i = 0; i < 2.5e5; i++)
//     {
//         auto cmpd3 = Compound((Compound &)*cmpd1, true);
//         // auto stat3 = Statement::deepcopy((Statement &)*stat1);
//         sum += cmpd3.complexity;
//     }
//     std::cout << sum << std::endl;
// }


TEST(test_term, test_clone)
{
    // TODO: Continue here.
    using COPULA::Copula;
    using COMPOUND::Compound;
    using TERM::Term;

    auto task = NARSESEPARSER::parser->parse_task("(&&, <$x-->robin>, <$x-->bird>).");
    auto cmpd1 = task.term();
    auto cmpd2 = Term::clone(cmpd1);
    auto str1 = interpreter.interpret(*cmpd1);
    std::cout << str1 << std::endl;
    auto str2 = interpreter.interpret(*cmpd2);
    std::cout << str2 << std::endl;
    GTEST_ASSERT_EQ(str1, str2);
    GTEST_ASSERT_NE(cmpd1->_vars_independent.get(), cmpd2->_vars_independent.get());
    GTEST_ASSERT_NE(cmpd1.get(), cmpd2.get());
    
    auto stat1 = *cmpd1->terms->begin();
    auto stat2 = *cmpd2->terms->begin();
    str1 = interpreter.interpret(*stat1);
    std::cout << str1 << std::endl;
    str2 = interpreter.interpret(*stat2);
    std::cout << str2 << std::endl;
    GTEST_ASSERT_EQ(str1, str2);
    GTEST_ASSERT_NE(stat1.get(), stat2.get());

    auto term1 = stat1->predicate;
    auto term2 = stat2->predicate;
    str1 = interpreter.interpret(*term1);
    std::cout << str1 << std::endl;
    str2 = interpreter.interpret(*term2);
    std::cout << str2 << std::endl;
    GTEST_ASSERT_EQ(str1, str2);
    GTEST_ASSERT_EQ(term1.get(), term2.get());

    auto var1 = stat1->subject;
    auto var2 = stat2->subject;
    str1 = interpreter.interpret(*var1);
    std::cout << str1 << std::endl;
    str2 = interpreter.interpret(*var2);
    std::cout << str2 << std::endl;
    GTEST_ASSERT_EQ(str1, str2);
    GTEST_ASSERT_NE(var1.get(), var2.get());

    // size_t sum = 0;
    // for (auto i = 0; i < 2.5e5; i++)
    // {
    //     auto cmpd3 = Compound((Compound &)*cmpd1, true);
    //     // auto stat3 = Statement::deepcopy((Statement &)*stat1);
    //     sum += cmpd3.complexity;
    // }
    // std::cout << sum << std::endl;
}
