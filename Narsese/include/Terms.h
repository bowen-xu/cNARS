#include "Term.h"
#include <vector>
// #include <list>
#include "../utils/IndexVar.h"
#include "Config.h"
#include <iterator>
#include <memory>
#if SRC_LIST == LIST_BOOST
#include <boost/container/list.hpp>
using boost::container::list;
#elif SRC_LIST == _LIST_STD
#include <list>
using std::list;
#endif

namespace TERMS
{

    using INDEXVAR::IndexVar;
    using INDEXVAR::pIndexVar;
    using TERM::pTerm;
    using TERM::Term;

    class Terms
    {
    public:
        std::vector<pTerm> terms;

        IndexVar _vars_independent = IndexVar();
        IndexVar _vars_dependent = IndexVar();
        IndexVar _vars_query = IndexVar();

        bool _is_commutative;

        Terms(bool is_commutative): _is_commutative(is_commutative){};
        Terms(list<pTerm> &terms, bool is_commutative) : Terms(is_commutative)
        {
            auto it = terms.begin();
            for (auto it = terms.begin(); it != terms.end(); it++)
            {
                this->terms.push_back((*it));
            }
        };

        Terms(std::vector<pTerm> &terms, bool is_commutative) : Terms(is_commutative)
        {
            auto it = terms.begin();
            for (auto it = terms.begin(); it != terms.end(); it++)
            {
                this->terms.push_back((*it));
            }
        };

        Terms(std::initializer_list<pTerm> terms, bool is_commutative) : Terms(is_commutative)
        {
            for (auto it = terms.begin(); it != terms.end(); it++)
            {
                this->terms.push_back((*it));
            }
        };
    };

    typedef std::shared_ptr<Terms> pTerms;
} // namespace TERMS
