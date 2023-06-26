#include "Term.h"
#include <vector>
// #include <list>
#include <memory>
#include <iterator>
#include "Config.h"
#if SRC_LIST == LIST_BOOST
#include <boost/container/list.hpp>
using boost::container::list;
#elif SRC_LIST == _LIST_STD
#include <list>
using std::list;
#endif

namespace TERMS
{
    

    using TERM::pTerm;
    using TERM::Term;

    class Terms
    {
    public:
        std::vector<pTerm> terms;

        Terms(){};
        Terms(list<pTerm> &terms)
        {
            auto it = terms.begin();
            for (auto it = terms.begin(); it != terms.end(); it++)
            {
                this->terms.push_back((*it));
            }
        };

        Terms(std::vector<pTerm> &terms)
        {
            auto it = terms.begin();
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
