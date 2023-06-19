#include "./include/Variable.h"

namespace VARIABLE
{
    string _repr_prefix[] = {"$", "#", "?"};

    Variable::Variable(VarPrefix _prefix, string _name, bool do_hashing, bool is_input) 
    {
        // word = _repr_prefix[_prefix];
        prefix = _prefix;
        name = _name;

        is_ivar = prefix == VarPrefix::Independent;
        is_dvar = prefix == VarPrefix::Dependent;
        is_qvar = prefix == VarPrefix::Qeury;
    }
    
} // namespace VARIABLE
