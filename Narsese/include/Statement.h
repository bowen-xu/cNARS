#ifndef _STATEMENT_H
#define _STATEMENT_H

#include <unordered_set>
#include "Copula.h"
#include "Term.h"
#include "../utils/hash.h"
#include "../utils/defines.h"

namespace STATEMENT
{
    using TermType = TERM::TermType;
    using COPULA::Copula;
    using std::string;
    using std::unordered_set;
    using TERM::Term;
    using UTILS::hash_str;

    class Statement : public Term
    {

    public:
        
        // bool is_commutative;
        // bool is_higher_order;

        Term& subject;
        Term& predicate;
        // Copula copula;

        unordered_set<Term*> components;


    public:
        // Statement(Term &_subject, Copula &_copula, Term &_predicate) : subject(_subject), predicate(_predicate), copula(_copula) {}
        Statement(Term& _subject, Copula _copula, Term& _predicate);
        // Statement();

        // const char* operator () ()
        // {
        //     return "statement";
        // }

    //     bool __eq__(Statement o)
    //     {   if (o.type == TermType::STATEMENT)
    //             if (not is_commutative) return subject == o.subject and predicate == o.predicate;
    //             else return (subject == o.subject and predicate == o.predicate) or (subject == o.predicate and predicate == o.subject);
    //         else return false;
    //     }
    //     inline bool operator ==(Statement& term)
    //     {
    //         return __eq__(term);
    //     }

    };
} // namespace STATEMENT


#endif // _STATEMENT_H