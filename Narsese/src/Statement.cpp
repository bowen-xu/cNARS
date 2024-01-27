#include "../include/Statement.h"
#include "../include/Term.h"
#include "Interpreter/include/Interpreter.hpp"
#include <string>
#include <vector>

using string = std::string;
using std::unordered_set;
using TERM::Term;
using UTILS::hash;

namespace STATEMENT
{

    void pybind_statement(py::module &m)
    {
        py::class_<STATEMENT::pStatement, TERM::pTerm>(m, "Statement")
            .def(py::init(
                [](TERM::pTerm subject, COPULA::Copula copula, TERM::pTerm predicate)
                {
                    return STATEMENT::Statement::create(subject, copula, predicate);
                }))
            // .def("__repr__", &TERM::pTerm::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);
            .def("__repr__", [](const pStatement &self, void* interpreter=nullptr){
                if (interpreter == nullptr)
                    interpreter = (void *)&INTERPRETER::interpreter;
                return self.__repr__(interpreter);
            });
    }
}
