#include "../include/Term.h"
#include "../include/Copula.h"
#include "../include/Term.inl"
#include "Interpreter/include/Interpreter.hpp"
#include "utils/hash.h"
#include <list>
#include <pybind11/stl.h>
#include <string>
#include <vector>

// using namespace TERM;
using INTERPRETER::Interpreter;
using std::string;
using TERM::pTerm;

namespace TERM
{
    pTerm Term::create(const char *word, void *interpreter)
    {
        if (interpreter == nullptr)
        {
            interpreter = &INTERPRETER::interpreter;
        }
        auto &_interpreter = *(Interpreter *)interpreter;

        pTerm *term;
        auto str = std::string(word);
        if (_interpreter.check_by_name(str) > 0)
        {
            auto key = _interpreter.get_by_name(str);
            term = (pTerm *)_interpreter.get_object(key);
            // std::cout << "create Term " << (size_t)term << std::endl;
        }
        else
        {
            term = new pTerm(new Term(), &_interpreter);
            _interpreter.put((*term)->hash_value, str, (void *)term);
        }
        return *term;
    }

    void pTerm::_free_from_interpreter()
    {
        auto &interpreter = *(Interpreter *)this->_interpreter;
        const auto &term = **this;
        interpreter.remove(term.hash_value);
    }

    std::string pTerm::__repr__(void *interpreter) const
    {
        std::string mark;
        if ((*this)->is_atom())
        {
            if ((*this)->is_var)
                mark = "Variable";
            else
                mark = "Term";
        }
        else if ((*this)->is_statement())
            mark = "Statement";
        else if ((*this)->is_compound())
            mark = "Compound";
        else
            throw std::runtime_error("Unknown type of the term.");

        if (interpreter == nullptr)
        {
            if (this->_interpreter == nullptr)
                return fmt::format("<{} at {:x}>", mark, (size_t)this->get());
            else
                interpreter = this->_interpreter;
        }
        auto &_interpreter = *(Interpreter *)interpreter;

        return fmt::format("<{}: {}>", mark, _interpreter.interpret(**this));
    }

    void pybind_term(py::module &m)
    {
        py::class_<pTerm>(m, "Term")
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
            .def_property_readonly(
                "subject",
                [](const pTerm &self) -> py::object
                {
                    if (self->subject == nullptr)
                        return py::none();
                    return py::cast(self->subject);
                })
            .def_property_readonly(
                "predicate",
                [](const pTerm &self) -> py::object
                {
                    if (self->predicate == nullptr)
                        return py::none();
                    return py::cast(self->predicate);
                })
            .def_property_readonly(
                "terms",
                [](const pTerm &self) -> py::object
                {
                    if (self->is_atom())
                        return py::none();
                    else if (self->is_statement())
                        return py::iter(py::cast(std::vector<pTerm>{self->subject, self->predicate}));
                    else if (self->is_compound())
                        return py::make_iterator(self->terms->begin(), self->terms->end());
                    else
                    {
                        PyErr_SetString(PyExc_TypeError, fmt::format("In file <{}> line <{}>: Invalid TermType", __FILE__, __LINE__).c_str());
                        return py::none();
                    }
                })
            .def_property_readonly(
                "copula",
                [](const pTerm &self) -> py::object
                {
                    if (self->copula == Copula::None)
                        return py::none();
                    return py::cast(self->copula);
                })
            .def("__repr__", [](const pTerm &self, void* interpreter=nullptr){
                if (interpreter == nullptr)
                    interpreter = (void *)&INTERPRETER::interpreter;
                return self.__repr__(interpreter);
            });
    }

    void pybind_terms(py::module &m)
    {
    }

}
