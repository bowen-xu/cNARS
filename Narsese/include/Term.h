#ifndef _TERM_H
#define _TERM_H

#include <string>
#include <unordered_set>
#include "Copula.h"
#include "Connector.h"
#include "../utils/hash.h"
#include <memory>

// #include "../utils/repr.h"

namespace TERM
{
    using COPULA::Copula;
    using CONNECTOR::Connector;
    // using REPR::repr;
    using std::string;
    using std::unordered_set;
    using UTILS::hash_str;

    enum TermType
    {
        ATOM = 0,
        STATEMENT = 1,
        COMPOUND = 2
    };

    class Term
    {
    public:
        TermType type = TermType::ATOM;
        Copula copula = COPULA::None;
        Connector connector = CONNECTOR::None;

        // bool has_var = false; // Whether the term contains variable(s).
        // bool has_ivar = false; // Whether the term contains independent variable(s).
        // bool has_dvar = false; // Whether the term contains dependent variable(s).
        // bool has_qvar = false; // Whether the term contains query variable(s).
        bool is_var : 1 = false;
        bool is_ivar : 1 = false;
        bool is_dvar : 1 = false;
        bool is_qvar : 1 = false;

        bool is_closed : 1 = true;  // Whether the term is closed or open in terms of variable.
        bool is_interval : 1 = false;
        bool is_operation : 1 = false;

        bool is_hashed : 1 = false;
        unsigned int hash_value = 0;

        int complexity = 1; // The complexity of the term. Read only.

        // Term(int hash_value);
        // Term(char *_word);
        // string word;
        Term() : hash_value((size_t)this){};
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

    };

    typedef std::shared_ptr<Term> pTerm;
} // namespace Term




#endif // _TERM_H