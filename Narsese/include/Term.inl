// #ifdef _TERM_H
#ifndef _TERM_INL
#define _TERM_INL

#include "./Term.h"
#include "./Statement.h"
#include "./Compound.h"
#include "./Variable.h"

// #include "Compound.inl"
// #include "Statement.inl"


namespace TERM
{

    inline void Term::_init_indexvars(const std::array<pIndexVar, 3> &variables, const Terms &terms)
    {
        for (auto term : terms)
        {
            auto indexvars2 = term->_index_vars();
            auto it = indexvars2.begin();
            for (const auto indexvar1 : variables)
            {
                auto indexvar2 = *it;
                IndexVar::connect(indexvar1, indexvar2, false);
            }
        }
    }

    inline void Term::_init_indexvars(const std::array<pIndexVar, 3> &variables, std::initializer_list<pTerm> terms)
    {
        for (auto term : terms)
        {
            auto indexvars2 = term->_index_vars();
            auto it = indexvars2.begin();
            for (const auto indexvar1 : variables)
            {
                auto indexvar2 = *it;
                IndexVar::connect(indexvar1, indexvar2, false);
            }
        }
    }

    inline pTerm::~pTerm()
    {
        if (*this != nullptr && (*this)->is_atom() && this->_interpreter != nullptr && this->use_count() == 2)
        {
            // std::cout << "free Term from the interpreter." << std::endl;
            this->_free_from_interpreter();
        }
    }

    inline bool Term::operator==(Term &other)
    {
        if (this->type != other.type)
            return false;
        if (hash(*this) != hash(other))
            return false;
        // if (hash(*this) == hash(other))
        // {
        //     if (!this->has_var && !other.has_var)
        //         return true;
        //     else if (!(this->has_var && other.has_var))
        //         return false;
        // }
        if (this->is_atom())
        {
            if (this->is_var || other.is_var)
            {
                if (this->is_qvar && other.is_qvar)
                    return *(this->_vars_independent->indices[0]) == *(other._vars_query->indices[0]);
                else if (this->is_dvar && other.is_dvar)
                    return *(this->_vars_independent->indices[0]) == *(other._vars_dependent->indices[0]);
                else if (this->is_ivar && other.is_ivar)
                    return *(this->_vars_independent->indices[0]) == *(other._vars_independent->indices[0]);
            }
            return hash(*this) == hash(other);
        }
        else if (this->is_statement())
        {
            auto &term1 = *this;
            auto &term2 = other;
            if (hash(term1) != hash(term2))
                return false;

            return (((*(term1.subject)) == (*(term2.subject))) && *(term1.predicate) == *(term2.predicate) && term1.copula == term2.copula);
            // return false;
        }
        else if (this->is_compound())
        {
            auto &term1 = *this;
            auto &term2 = other;
            if (hash(term1) != hash(term2))
                return false;
            if (term1.terms->size() != term2.terms->size())
                return false;
            if (term1.connector != term2.connector)
                return false;
            for (auto it1 = term1.terms->begin(), it2 = term2.terms->begin(); it1 != term1.terms->end() && it2 != term2.terms->end(); it1++, it2++)
            {
                auto &term1 = **it1;
                auto &term2 = **it2;
                if (!(term1 == term2))
                    return false;
            }
            return true;
            // throw std::logic_error("TODO");
            // return false;
        }
        return false;
    }

    inline bool Term::operator<(Term &other)
    {
        /*
        Note:
        This function is used to compare two terms, especially those with variables.
        When computing intersection, union, and difference of two (ordered) `set`s of terms, this function should be used for comparison-sorting.
        */
        if (hash(*this) != hash(other))
            return hash(*this) < hash(other);

        if (!this->has_var && !other.has_var)
            return hash(*this) < hash(other);
        else if (!this->has_var && other.has_var)
            return false;
        else if (this->has_var && !other.has_var)
            return true;

        if (this->type != other.type)
            return this->type < other.type;

        if (this->is_atom())
        {
            if (this->is_var || other.is_var)
            {
                if (this->is_qvar && other.is_qvar)
                    return *(this->_vars_query->indices[0]) < *(other._vars_query->indices[0]);
                else if (this->is_dvar && other.is_dvar)
                    return *(this->_vars_dependent->indices[0]) < *(other._vars_dependent->indices[0]);
                else if (this->is_ivar && other.is_ivar)
                    return *(this->_vars_independent->indices[0]) < *(other._vars_independent->indices[0]);
            }
            return hash(*this) < hash(other);
        }
        else if (this->is_statement())
        {
            auto &term1 = *this;
            auto &term2 = other;

            if (*(term1.subject) < *(term2.subject))
                return true;
            if (*(term1.predicate) < *(term2.predicate))
                return true;
            if (term1.copula < term2.copula)
                return true;
            return false;
        }
        else if (this->is_compound())
        {
            auto &term1 = *this;
            auto &term2 = other;
            if (term1.terms->size() != term2.terms->size())
                return term1.terms->size() < term2.terms->size();
            if (term1.connector != term2.connector)
                return term1.connector < term2.connector;
            for (auto it1 = term1.terms->begin(), it2 = term2.terms->begin(); it1 != term1.terms->end() && it2 != term2.terms->end(); it1++, it2++)
            {
                auto &term1 = **it1;
                auto &term2 = **it2;
                if ((term1 < term2))
                    return true;
            }
            return false;
            // throw std::logic_error("TODO");
            // return false;
        }
        return false;
    }

    inline pTerm Term::clone(pTerm term)
    {
        using VARIABLE::Variable;
        using STATEMENT::Statement;
        using COMPOUND::Compound;
        if (term->has_var)
        {
            if (term->is_atom())
            {
                if (term->is_var)
                {
                    return pTerm(new Variable((Variable &)*term));
                }
                else
                {
                    throw std::runtime_error("The type of the term is invalid.");
                }
                // return pTerm(new T)
            }
            else if (term->is_statement())
            {
                return pTerm(new Statement((Statement &)*term, true));
            }
            else if (term->is_compound())
            {
                return pTerm(new Compound((Compound &)*term, true));
            }
            else
            {
                throw std::runtime_error("Invalid TermType.");
            }
        }
        // else
        // {
        //     return term;
        // }
        return term;
    }
}

#endif //_TERM_INL
// #endif // _TERM_H