
#include <pybind11/pybind11.h>
// #include "Narsese/include/Narsese.h"
#include "Interpreter/include/Interpreter.hpp"
#include "Narsese/Parser/NarseseParser.h"
#include "Narsese/include/Term.h"
#include <functional>
#include <iostream>

namespace py = pybind11;
using COMPOUND::Compound;
using COMPOUND::pCompound;
using SENTENCE::pSentence;
using SENTENCE::Sentence;
using STATEMENT::pStatement;
using STATEMENT::Statement;
using TASK::pTask;
using TASK::Task;
using TERM::pTerm;
using TERM::Term;

PYBIND11_MODULE(narsese, m)
{
    m.doc() = R"pbdoc(
        Narsese module
    )pbdoc";

    COPULA::pybind_copula(m);
    CONNECTOR::pybind_connnector(m);

    NARSESEPARSER::pybind_parse(m);
    TERM::pybind_term(m);
    STATEMENT::pybind_statement(m);
    COMPOUND::pybind_compound(m);

    TASK::pybind_task(m);
    SENTENCE::pybind_sentence(m);
}
