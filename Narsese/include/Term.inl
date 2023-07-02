#ifndef _TERM_INL
#define _TERM_INL

#include "./Term.h"
namespace TERM
{
    inline void Term::_init_indexvars(const std::array<pIndexVar, 3> &variables, const Terms &terms)
    {
        for (auto term : terms)
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
}

#endif //_TERM_INL