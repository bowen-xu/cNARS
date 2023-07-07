#include "../include/Term.h"
#include "../include/Copula.h"
#include "../utils/hash.h"
#include "Interpreter/include/Interpreter.hpp"
#include <list>
#include <string>

using namespace TERM;
using INTERPRETER::Interpreter;
using std::string;
using TERM::pTerm;

void pTerm::_free_from_interpreter()
{
    auto &interpreter = *(Interpreter *)this->_interpreter;
    const auto &term = **this;
    interpreter.remove(term.hash_value);
}
