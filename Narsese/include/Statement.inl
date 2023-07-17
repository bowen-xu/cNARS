// #ifdef _STATEMENT_H
#ifndef _STATEMENT_INL
#define _STATEMENT_INL

#include "Statement.h"
#include "Term.h"

namespace STATEMENT
{
    inline Statement::Statement(TERM::pTerm _subject, Copula _copula, TERM::pTerm _predicate, bool is_input) : Statement::Term(TermType::STATEMENT)
    {
        this->is_hashed = false;
        // this->type = TermType::STATEMENT;
        this->subject = is_input ? _subject : Term::clone(_subject);
        this->predicate = is_input ? _predicate : Term::clone(_predicate);
        this->copula = _copula;
        this->is_commutative = COPULA::is_commutative(_copula);
        this->hash_value = hash(*this);
        this->complexity += (subject->complexity + predicate->complexity);
        // word = string("<") + _subject.word + COPULA::Repr[_copula] + _predicate.word + string(">");
        // word_sorted = subject.hash_value > predicate.hash_value ? word: (string("<") + predicate.word + COPULA::Repr[_copula] + subject.word + string(">"));

        // components = unordered_set<Term*>{&subject, &predicate};

        this->is_higher_order = COPULA::is_higher_order(copula);
        this->is_operation = _predicate->is_operation;

        if (this->predicate->is_atom() && this->predicate->is_operation && this->subject->is_compound() && this->subject->connector == CONNECTOR::PRODUCT)
            this->is_operation = true;

        // is_operation = predicate.is_operation;
        auto terms = {this->subject, this->predicate};
        this->_refresh_var_status(terms);
        this->_init_indexvars(this->_index_vars(), terms);
        this->_build_indexvars();
    }

    inline Statement::Statement(const Statement &other, bool deep) : Statement::Term(TermType::STATEMENT)
    {
        if (deep == false)
        {
            *this = other;
            return;
        }

        using INDEXVAR::IndexVar;
        if (TermType::STATEMENT != other.type)
            throw std::runtime_error("The type should be STATEMENT.");
        // this->type = TermType::STATEMENT;
        
        this->copula = other.copula;
        this->is_commutative = other.is_commutative;
        this->is_hashed = other.is_hashed;
        this->hash_value = other.hash_value;
        this->complexity = other.complexity;

        this->is_higher_order = other.is_higher_order;
        this->is_operation = other.is_operation;

        this->has_var = other.has_var;
        this->has_dvar = other.has_dvar;
        this->has_ivar = other.has_ivar;
        this->has_qvar = other.has_qvar;
        this->is_var = other.is_var;
        this->is_dvar = other.is_dvar;
        this->is_ivar = other.is_ivar;
        this->is_qvar = other.is_qvar;

        this->subject = Term::clone(other.subject);
        this->predicate = Term::clone(other.predicate);

        // auto terms = {this->subject, this->predicate};
        // this->_refresh_var_status(terms);
        this->_init_indexvars(this->_index_vars(), {this->subject, this->predicate});
        this->_build_indexvars();
    }

    
} // namespace STATEMENT

#endif // _STATEMENT_INL