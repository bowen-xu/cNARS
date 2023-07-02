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
#include <vector>

using INTERPRETER::interpreter;
using NARSESEPARSER::NarseseParser;
using TASK::Task;

using std::string;

TEST(test_terms, test_terms0)
{
    using TERM::pTerm;
    using TERM::Term;
    using TERM::Terms;
    std::vector<pTerm> terms_vec{Term::create(), Term::create()};
    Terms terms((std::vector<pTerm> &)terms_vec, true);
    for (auto it = terms.begin(); it != terms.end(); it++)
    {
        auto &term = *it;
        std::cout << term->hash_value << std::endl;
    }
    for (auto &term : terms)
    {
        std::cout << term->hash_value << std::endl;
    }
}
