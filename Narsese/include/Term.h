#ifndef _TERM_H
#define _TERM_H

#include "../utils/IndexVar.h"
#include "../utils/hash.h"
#include "Connector.h"
#include "Copula.h"
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <unordered_set>

// #include "../utils/repr.h"

namespace TERM
{
    using CONNECTOR::Connector;
    using COPULA::Copula;
    // using REPR::repr;
    using INDEXVAR::IndexVar;
    using INDEXVAR::pIndexVar;
    using std::string;
    using std::unordered_set;
    using UTILS::Hash;

    class Term;
    typedef std::shared_ptr<Term> pTerm;

    enum TermType
    {
        ATOM = 0,
        STATEMENT = 1,
        COMPOUND = 2,
        INTERVAL = -1,
        OPERATION = -2
    };

    class Term
    {
    public:
        TermType type = TermType::ATOM;
        Copula copula = COPULA::None;
        Connector connector = CONNECTOR::None;

        bool is_var : 1 = false;
        bool is_ivar : 1 = false;
        bool is_dvar : 1 = false;
        bool is_qvar : 1 = false;
        bool has_var : 1 = false;  // Whether the term contains variable(s).
        bool has_ivar : 1 = false; // Whether the term contains independent variable(s).
        bool has_dvar : 1 = false; // Whether the term contains dependent variable(s).
        bool has_qvar : 1 = false; // Whether the term contains query variable(s).

        bool is_closed : 1 = true; // Whether the term is closed or open in terms of variable.
        bool is_interval : 1 = false;
        bool is_operation : 1 = false;

        bool is_higher_order : 1 = false;

        bool is_hashed : 1 = false;
        size_t hash_value = 0;

        int complexity = 1; // The complexity of the term. Read only.

        pIndexVar _vars_independent = IndexVar::create();
        pIndexVar _vars_dependent = IndexVar::create();
        pIndexVar _vars_query = IndexVar::create();

        // Term(int hash_value);
        // Term(char *_word);
        // string word;
        Term() : hash_value(Hash{}(std::initializer_list<size_t>{(size_t)TermType::ATOM, (size_t)this})){};
        // Term(std::string _word) : word(_word) {}

        // bool __eq__(Term o)
        // {
        //     if (o.type == TermType::ATOM) return hash_value == o.hash_value;
        //     else return false;
        // }

        // inline bool operator ==(Term& term)
        // {
        //     return __eq__(term);
        // }

        virtual size_t __hash__()
        {
            return this->hash_value;
        }

        inline bool is_atom() { return this->type == TermType::ATOM; }
        inline bool is_statement() { return this->type == TermType::STATEMENT; }
        inline bool is_compound() { return this->type == TermType::COMPOUND; }

    protected:
        template <typename _Container>
        void _refresh_var_status(const _Container &terms)
        {
            this->has_var = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                        { return term->has_var; });
            this->has_ivar = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                         { return term->has_ivar; });
            this->has_dvar = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                         { return term->has_dvar; });
            this->has_qvar = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                         { return term->has_qvar; });
        }

        void _init_indexvars(const std::array<pIndexVar, 3> &variables, const std::vector<pTerm> &terms)
        {

            for (auto &term : terms)
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

        void _build_indexvars()
        {
            if (this->has_ivar)
                this->_vars_independent->build();
            else
                this->_vars_independent->_is_built = true;
            if (this->has_dvar)
                this->_vars_dependent->build();
            else
                this->_vars_dependent->_is_built = true;
            if (this->has_qvar)
                this->_vars_query->build();
            else
                this->_vars_query->_is_built = true;
        }

        std::array<pIndexVar, 3> _index_vars() const
        {
            return {this->_vars_independent, this->_vars_dependent, this->_vars_query};
        }
    };

} // namespace Term

#endif // _TERM_H