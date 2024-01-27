
#include <pybind11/pybind11.h>
#include "Narsese/include/Narsese.h"
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

    TERM::pybind_term(m);
    COPULA::pybind_copula(m);
    CONNECTOR::pybind_connnector(m);

    NARSESEPARSER::pybind_parse(m);
    STATEMENT::pybind_statement(m);
    COMPOUND::pybind_compound(m);

    TASK::pybind_task(m);
    TRUTH::pybind_truth(m);
    BUDGET::pybind_budget(m);
    SENTENCE::pybind_sentence(m);

    py::class_<NARSESEPARSER::NarseseParser, std::shared_ptr<NARSESEPARSER::NarseseParser>>(m, "NarseseParser");
    // .def_property_readonly("term", &TASK::pTask::term)
    // .def_property_readonly("sentence", &TASK::pTask::sentence)
    // .def("__repr__", [](){return ("<NarseseParser>");});

    m.attr("parser") = NARSESEPARSER::parser;
    // m.def
}
