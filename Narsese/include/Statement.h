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

    class Statement : public Term
    {

    public:
        bool _is_commutative;
        // bool is_higher_order;

        pTerm subject;
        pTerm predicate;
        Copula copula;

        unordered_set<pTerm> components;

    public:
        Statement(pTerm _subject, Copula _copula, pTerm _predicate);

        virtual size_t __hash__()
        {
            return Hash{}({(size_t)copula, subject->hash_value, predicate->hash_value});
        }
    };

} // namespace STATEMENT

#endif // _STATEMENT_H