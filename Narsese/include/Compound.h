#ifndef _COMPOUND_H
#define _COMPOUND_H
#include <string>
#include "./Term.h"
#include "./Connector.h"
#include "./Terms.h"
#include <list>
#include <functional>

namespace COMPOUND
{
    using CONNECTOR::Connector;
    using std::string;
    using TERM::pTerm;
    using TERM::Term;
    using TERM::TermType;
    using TERMS::pTerms;
    using TERMS::Terms;

    class Compound : public Term
    {
    public:

        string word_sorted;
        pTerms terms;

        inline auto& components() { return terms->terms; }

        Compound(Connector connector, pTerms terms);
        Compound(Connector connector, std::list<pTerm> &terms);
        // Compound(Connector connector, std::initializer_list<Term&> terms);
        Compound(Connector connector, std::initializer_list<pTerm> terms);
        Compound(Connector connector, pTerm term) : Compound(connector, {term}) {};

        static auto ExtensionalSet(std::initializer_list<pTerm> terms)
        {
            return pTerm(new Compound(Connector::ExtensionalSet, terms));
        }
        static auto IntensionalSet(std::initializer_list<pTerm> terms)
        {
            return pTerm(new Compound(Connector::IntensionalSet, terms));
        }
        // static auto 

    private:
        Compound(Connector &connector) : terms(pTerms(new Terms))
        {
            this->type = TermType::COMPOUND;
            this->connector = connector;
        }
    };


} // namespace COMPOUND

#endif // _COMPOUND_H
