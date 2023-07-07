#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "Term.h"
#include "utils/hash.h"

namespace VARIABLE
{
    using std::string;
    using TERM::Term;
    using UTILS::Hash;

    enum VarPrefix
    {
        Independent = 0,
        Dependent = 1,
        Qeury = 2
    };

    const string Repr[] = {string("$"), string("#"), string("?")};

    class Variable : public Term
    {
    public:
        string name;
        VarPrefix prefix;

    public:
        Variable(VarPrefix _prefix, string _name);

        virtual size_t do_hashing()
        {
            this->hash_value = Hash{}(std::initializer_list<size_t>{(size_t)(TERM::TermType::VARIABLE),(size_t)(this->prefix)});
            this->is_hashed = true;
            return this->hash_value;
        }

    // public:
    //     operator string () const {
    //         return string("<Variable: ") + word + name + string(">");
    //     }
    };
} // namespace VARIABLE

#endif // _VARIABLE_H
