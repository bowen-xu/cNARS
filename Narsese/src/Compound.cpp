#include "../include/Compound.h"

using namespace COMPOUND;

Compound::Compound(Connector connector, pTerms terms) : terms(terms)
{
    this->type = TermType::COMPOUND;
    this->connector = connector;
}

Compound::Compound(Connector connector, std::list<pTerm> &terms) : Compound::Compound(connector, pTerms(new Terms(terms)))
{

}

Compound::Compound(Connector connector, std::initializer_list<pTerm> terms) : Compound::Compound(connector, pTerms(new Terms(terms)))
{
    
}


