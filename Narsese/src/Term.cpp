#include "../include/Term.h"
#include "../include/Copula.h"
#include "../utils/hash.h"
#include "Interpreter/include/Interpreter.hpp"
#include <list>
#include <string>

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

    std::string pTerm::__repr__(void *interpreter = nullptr) const
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
}
