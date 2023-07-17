// #ifdef _VARIABLE_H
#ifndef _VARIABLE_INL
#define _VARIABLE_INL

#include "./Compound.h"
#include "./Statement.h"
#include "./Term.h"
#include "./Variable.h"

// namespace TERM
// {
//     class Term;
// }

namespace VARIABLE
{
    inline Variable::Variable(const Variable &other) : name(other.name), prefix(other.prefix), TERM::Term(other)
    {
        this->subject = nullptr;
        this->predicate = nullptr;
        this->copula = COPULA::None;
        this->connector = CONNECTOR::None;
        // this->type = TERM::TermType::ATOM;
        this->terms = nullptr;
        this->is_operation = false;
        this->is_interval = false;
        this->is_higher_order = false;
        this->complexity = 1;
        this->_vars_independent = INDEXVAR::IndexVar::clone(other._vars_independent);
        this->_vars_dependent = INDEXVAR::IndexVar::clone(other._vars_dependent);
        this->_vars_query = INDEXVAR::IndexVar::clone(other._vars_query);
    }

    inline Variable::Variable(VarPrefix _prefix, string _name) : prefix(_prefix), name(_name), TERM::Term(TERM::TermType::ATOM)
    {
        // word = _repr_prefix[_prefix];
        prefix = _prefix;
        name = _name;

        if (prefix == VarPrefix::Independent)
        {
            is_ivar = true;
            has_ivar = true;
        }
        else if (prefix == VarPrefix::Dependent)
        {
            is_dvar = true;
            has_dvar = true;
        }
        else if (prefix == VarPrefix::Qeury)
        {
            is_qvar = true;
            has_qvar = true;
        }

        is_var = true;
        has_var = true;

        this->hash_value = Hash{}(std::initializer_list<size_t>{(size_t)(TERM::TermType::VARIABLE), (size_t)(this->prefix)});
        this->is_hashed = true;
    }

}
#endif // _VARIABLE_INL
// #endif // _VARIABLE_H