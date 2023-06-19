#include "Term.h"
#include <vector>
#include <list>
#include <memory>

namespace TERMS
{
    using TERM::pTerm;
    using TERM::Term;

    class Terms
    {
    public:
        std::vector<pTerm> terms;

        Terms(){};
        Terms(std::list<pTerm> &terms)
        {
            for (auto it = terms.begin(); it != terms.end(); it++)
            {
                this->terms.push_back((*it));
            }
        };

        Terms(std::initializer_list<pTerm> terms)
        {
            for (auto it = terms.begin(); it != terms.end(); it++)
            {
                this->terms.push_back((*it));
            }
        };
    };

    typedef std::shared_ptr<Terms> pTerms;
} // namespace TERMS
