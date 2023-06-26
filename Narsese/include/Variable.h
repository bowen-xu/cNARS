#ifndef _VARIABLE_H
#define _VARIABLE_H

#include "Term.h"

namespace VARIABLE
{
    using std::string;
    using TERM::Term;

    enum VarPrefix
    {
        Independent = 0,
        Dependent = 1,
        Qeury = 2
    };

    extern string Repr[];


    class Variable : public Term
    {
    public:
        bool is_var = true;
        bool has_var = true;

        string name;
        VarPrefix prefix;

    public:
        Variable(VarPrefix _prefix, string _name);

    // public:
    //     operator string () const {
    //         return string("<Variable: ") + word + name + string(">");
    //     }
    };
} // namespace VARIABLE

#endif // _VARIABLE_H
