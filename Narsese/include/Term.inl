#ifndef _TERM_INL
#define _TERM_INL

#include "./Term.h"
// #include "./Statement.h"
// #include "./Compound.h"


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

        if (this->is_atom())
        {
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
        if (hash(*this) != hash(other))
            return hash(*this) < hash(other);

        if (this->type != other.type)
            return this->type < other.type;

        if (this->is_atom())
        {
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

}

#endif //_TERM_INL