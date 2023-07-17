// #ifdef _COMPOUND_H
#ifndef _COMPOUND_INL
#define _COMPOUND_INL

#include "./Compound.h"
#include "./Term.h"

namespace COMPOUND
{
    using TERM::Term;

    inline Compound::Compound(const Compound &other, bool deep) : Term(TermType::COMPOUND)
    {
        if (deep == false)
        {
            *this = other;
            return;
        }

        using INDEXVAR::IndexVar;
        if (TermType::COMPOUND != other.type)
            throw std::runtime_error("The type should be COMPOUND.");
        this->is_hashed = false;
        // this->type = TermType::COMPOUND;
        // this->terms = Term::clone(other.subject);

        this->connector = other.connector;
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


        if (!this->has_var)
            this->terms = other.terms;
        else
        {
            this->terms = pTerms(new Terms(CONNECTOR::is_commutative(connector)));
            for (auto term : *other.terms)
                this->terms->push_back(Term::clone(term));
        }
        

        

        // auto terms = this->terms;
        // this->_refresh_var_status(terms);
        this->_init_indexvars(this->_index_vars(), *this->terms);
        this->_build_indexvars();
    }

} // namespace COMPOUND

#endif // _COMPOUND_INL
// #endif // _COMPOUND_H