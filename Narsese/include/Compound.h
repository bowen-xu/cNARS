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
    using TERM::Term;
    using TERM::TermType;
    using TERMS::Terms;

    class Compound : public Term
    {
    public:

        string word_sorted;

        Compound(Connector connector, Terms &terms);
        Compound(Connector connector, std::list<Term*> &terms);
        // Compound(Connector connector, std::initializer_list<Term&> terms);
        Compound(Connector connector, std::initializer_list<Term*> terms);

    private:
        Compound(Connector &connector)
        {
            this->type = TermType::COMPOUND;
            this->connector = connector;
        }
    };

} // namespace COMPOUND

#endif // _COMPOUND_H
