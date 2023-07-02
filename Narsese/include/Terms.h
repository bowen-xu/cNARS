#include "Term.h"
#include <vector>
// #include <list>
#include "../utils/IndexVar.h"
#include "Config.h"
#include <iterator>
#include <memory>
#include <set>

#if SRC_LIST == LIST_BOOST
#include <boost/container/list.hpp>
using boost::container::list;
#elif SRC_LIST == _LIST_STD
#include <list>
using std::list;
#endif

namespace TERMS
{
    using TERM::Terms;
    using TERM::pTerms;
} // namespace TERMS
