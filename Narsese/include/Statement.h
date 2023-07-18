#ifndef _STATEMENT_H
#define _STATEMENT_H

#include "../utils/defines.h"
#include "../utils/hash.h"
#include "Copula.h"
#include "Term.h"
#include <memory>
#include <unordered_set>
#include <pybind11/pybind11.h>

namespace TERM
{
    class Term;
    class pTerm;
}

namespace STATEMENT
{
    namespace py = pybind11;
    
    using TermType = TERM::TermType;
    using COPULA::Copula;
    using std::string;
    using std::unordered_set;
    using TERM::pTerm;
    using TERM::Term;
    using UTILS::Hash;
    using UTILS::hash;

    class pStatement : public pTerm
    {
    public:
        pStatement(Term *term, void *interpreter = nullptr) : pTerm(term, interpreter) {}
        pStatement() : pTerm() {}
    };

    class Statement : public Term
    {

    public:
        // const TermType Term::type = TermType::ATOM;
        bool is_commutative;
        // bool is_higher_order;

    public:
        Statement(pTerm _subject, Copula _copula, pTerm _predicate, bool is_input = false);

        Statement(const Statement &other, bool deep);

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

        static pStatement create(pTerm subject, Copula copula, pTerm predicate)
        {
            auto statement = new Statement(subject, copula, predicate, false);
            return pStatement(statement);
        }
    };

    void pybind_statement(py::module &m);
} // namespace STATEMENT
// #include "Statement.inl"

#endif // _STATEMENT_H