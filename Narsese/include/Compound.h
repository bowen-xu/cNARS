#ifndef _COMPOUND_H
#define _COMPOUND_H
#include "./Connector.h"
#include "./Term.h"
#include "./Terms.h"
#include <string>
// #include <list>
#include "Config.h"
#include <functional>
#include <vector>
#include "../utils/hash.h"

#if SRC_LIST == LIST_BOOST
#include <boost/container/list.hpp>
using boost::container::list;
#elif SRC_LIST == _LIST_STD
#include <list>
using std::list;
#endif

namespace COMPOUND
{

    using CONNECTOR::Connector;
    using std::string;
    using TERM::pTerm;
    using TERM::Term;
    using TERM::TermType;
    using TERMS::pTerms;
    using TERMS::Terms;
    using UTILS::Hash;

    class Compound : public Term
    {
    public:
        string word_sorted;
        pTerms terms;
        bool _is_commutative : 1 = false;

        inline auto &components() { return terms->terms; }

        Compound(Connector connector, pTerms terms);
        Compound(Connector connector, list<pTerm> &terms);
        Compound(Connector connector, std::vector<pTerm> &terms);
        // Compound(Connector connector, std::initializer_list<Term&> terms);
        Compound(Connector connector, std::initializer_list<pTerm> terms);
        Compound(Connector connector, pTerm term) : Compound(connector, {term}){};

        static auto ExtensionalSet(std::initializer_list<pTerm> terms)
        {
            return pTerm(new Compound(Connector::ExtensionalSet, terms));
        }
        static auto IntensionalSet(std::initializer_list<pTerm> terms)
        {
            return pTerm(new Compound(Connector::IntensionalSet, terms));
        }
        // static auto

        virtual size_t __hash__()
        {
            std::vector<size_t> values;
            values.push_back((size_t)connector);
            for (auto it : terms->terms)
            {
                values.push_back((*it).hash_value);
            }
            return Hash{}(values);
        }

    private:
        Compound(Connector &connector) : terms(pTerms(new Terms(CONNECTOR::is_commutative(connector))))
        {
            this->type = TermType::COMPOUND;
            this->connector = connector;
        }
    };

} // namespace COMPOUND

#endif // _COMPOUND_H
