#ifndef _STATEMENT_H
#define _STATEMENT_H

#include "../utils/defines.h"
#include "../utils/hash.h"
#include "Copula.h"
#include "Term.h"
#include <memory>
#include <unordered_set>

namespace STATEMENT
{
    using TermType = TERM::TermType;
    using COPULA::Copula;
    using std::string;
    using std::unordered_set;
    using TERM::pTerm;
    using TERM::Term;
    using UTILS::Hash;
    using UTILS::hash;

    class Statement : public Term
    {

    public:
        bool _is_commutative;
        // bool is_higher_order;

    public:
        Statement(pTerm _subject, Copula _copula, pTerm _predicate, bool is_input = false)
        {
            this->is_hashed = false;
            this->type = TermType::STATEMENT;
            this->subject = is_input ? _subject : Term::clone(_subject);
            this->predicate = is_input ? _predicate : Term::clone(_predicate);
            this->copula = _copula;
            this->_is_commutative = COPULA::is_commutative(_copula);
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

        virtual size_t do_hashing()
        {
            std::vector<size_t> values{(size_t)TermType::STATEMENT, (size_t)'<', hash(*subject), (size_t)copula, hash(*predicate), (size_t)'<'};

            auto &vars_independent = *this->_vars_independent->indices_normalized();
            auto &vars_dependent = *this->_vars_dependent->indices_normalized();
            auto &vars_query = *this->_vars_query->indices_normalized();
            values.push_back((size_t)'(');
            values.insert(values.end(), vars_independent.begin(), vars_independent.end());
            values.push_back((size_t)')');
            values.push_back((size_t)'(');
            values.insert(values.end(), vars_dependent.begin(), vars_dependent.end());
            values.push_back((size_t)')');
            values.push_back((size_t)'(');
            values.insert(values.end(), vars_query.begin(), vars_query.end());
            values.push_back((size_t)')');

            this->hash_value = Hash{}(values);
            this->is_hashed = true;

            return this->hash_value;
        }
    };

} // namespace STATEMENT

#endif // _STATEMENT_H