#include "./include/Variable.h"

namespace VARIABLE
{
    // string _repr_prefix[] = {"$", "#", "?"};

    Variable::Variable(VarPrefix _prefix, string _name) : Term()
    {
        // word = _repr_prefix[_prefix];
        prefix = _prefix;
        name = _name;

        if (prefix == VarPrefix::Independent)
        {
            is_ivar = true;
            has_ivar = true;
        }
        else if (prefix == VarPrefix::Dependent)
        {
            is_dvar = true;
            has_dvar = true;
        }
        else if (prefix == VarPrefix::Qeury)
        {
            is_qvar = true;
            has_qvar = true;
        }

        is_var = true;
        has_var = true;
    }
    
} // namespace VARIABLE
