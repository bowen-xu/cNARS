
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

    // m.def("Term", py::overload_cast<char *, void *>(&TERM::Term::create), py::arg("word"), py::arg("interpreter") = (void *)&INTERPRETER::interpreter);

    // m.def("Statement", &STATEMENT::Statement::create);

    py::enum_<COPULA::Copula>(m, "Copula")
        .value("Inheritance", COPULA::Copula::Inheritance, "-->")
        .value("Similarity", COPULA::Copula::Similarity, "<->")
        .value("Instance", COPULA::Copula::Instance, "{--")
        .value("Property", COPULA::Copula::Property, "--]")
        .value("InstanceProperty", COPULA::Copula::InstanceProperty, "{-]")
        .value("Implication", COPULA::Copula::Implication, "==>")
        .value("PredictiveImplication", COPULA::Copula::PredictiveImplication, "=/>")
        .value("ConcurrentImplication", COPULA::Copula::ConcurrentImplication, "=|>")
        .value("RetrospectiveImplication", COPULA::Copula::RetrospectiveImplication, "=\\>")
        .value("Equivalence", COPULA::Copula::Equivalence, "<=>")
        .value("PredictiveEquivalence", COPULA::Copula::PredictiveEquivalence, "</>")
        .value("ConcurrentEquivalence", COPULA::Copula::ConcurrentEquivalence, "<|>");

    py::enum_<CONNECTOR::Connector>(m, "Connector")
        .value("Conjunction", CONNECTOR::Connector::Conjunction, "&&")
        .value("Disjunction", CONNECTOR::Connector::Disjunction, "||")
        .value("Product", CONNECTOR::Connector::Product, "*")
        .value("ParallelEvents", CONNECTOR::Connector::ParallelEvents, "&|")
        .value("SequentialEvents", CONNECTOR::Connector::SequentialEvents, "&/")
        .value("IntensionalIntersection", CONNECTOR::Connector::IntensionalIntersection, "|")
        .value("ExtensionalIntersection", CONNECTOR::Connector::ExtensionalIntersection, "&")
        .value("ExtensionalDifference", CONNECTOR::Connector::ParallelEvents, "-")
        .value("IntensionalDifference", CONNECTOR::Connector::IntensionalDifference, "~")
        .value("Negation", CONNECTOR::Connector::Negation, "--")
        .value("IntensionalSet", CONNECTOR::Connector::IntensionalSet, "[")
        .value("ExtensionalSet", CONNECTOR::Connector::ExtensionalSet, "{")
        .value("IntensionalImage", CONNECTOR::Connector::IntensionalImage, "\\")
        .value("ExtensionalImage", CONNECTOR::Connector::ExtensionalImage, "/")
        .value("List", CONNECTOR::Connector::List, "#");

    m.def(
        "parse",
        [](std::string line) -> py::object
        {
            try
            {
                auto task = NARSESEPARSER::parser->parse_task(line);
                if (task == nullptr)
                    throw std::runtime_error("Parsing error - Please check the syntax.");
                return py::cast(task);
            }
            catch (std::exception &e)
            {
                // std::cout << e.what() << std::endl;
                PyErr_SetString(PyExc_RuntimeError, e.what());
                return py::none();
            }
            catch (...)
            {
                PyErr_SetString(PyExc_RuntimeError, "Unknown error occurred.");
                return pybind11::none();
            }
        },
        py::arg("line"));

    py::class_<TERM::pTerm>(m, "Term")
        .def(py::init(
            []()
            {
                return TERM::Term::create();
            }))
        .def(py::init(
            [](std::string word)
            {
                return TERM::Term::create((char *)word.c_str(), nullptr);
            }))
        .def("__repr__", &TERM::pTerm::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);

    py::class_<STATEMENT::pStatement, TERM::pTerm>(m, "Statement")
        .def(py::init(
            [](TERM::pTerm subject, COPULA::Copula copula, TERM::pTerm predicate)
            {
                return STATEMENT::Statement::create(subject, copula, predicate);
            }))
        .def("__repr__", &TERM::pTerm::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);

    py::class_<COMPOUND::pCompound, TERM::pTerm>(m, "Compound")
        .def(py::init(
            [](CONNECTOR::Connector connector, py::args args)
            {
                std::vector<TERM::pTerm> terms{};
                for (auto arg : args)
                    terms.push_back(py::cast<TERM::pTerm>(arg));
                return COMPOUND::Compound::create(connector, terms);
            }))
        .def("__repr__", &TERM::pTerm::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);

    py::class_<TASK::pTask>(m, "Task")
        .def_property_readonly("term", &TASK::pTask::term)
        .def_property_readonly("sentence", &TASK::pTask::sentence)
        .def("__repr__", &TASK::pTask::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);

    py::class_<pSentence>(m, "Sentence")
        .def("__repr__", &pSentence::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);
}
