#include "../include/Term.h"
#include "../include/Copula.h"
#include "../utils/hash.h"
#include <string>
#include <list>

using namespace TERM;
using TERM::pTerm;
using std::list;
using std::string;

void Term::_init_indexvars(const std::array<pIndexVar, 3> &variables, Terms *terms)
{
    for (auto term : *terms)
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


