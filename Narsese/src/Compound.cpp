#include "../include/Compound.h"
#include <numeric>

using namespace COMPOUND;
using UTILS::hash;

Compound::Compound(Connector connector, pTerms terms) : terms(terms)
{
    this->type = TermType::COMPOUND;
    this->connector = connector;
    this->_is_commutative = CONNECTOR::is_commutative(connector);
    this->hash_value = hash(*this);
    this->complexity = std::accumulate(terms->begin(), terms->end(), 0,
    [](int sum, const auto& term) { return sum + term->complexity; });


    this->_refresh_var_status(*this->terms);
    this->_init_indexvars(this->_index_vars(), this->terms.get());
    this->_build_indexvars();

}

Compound::Compound(Connector connector, std::list<pTerm> &terms) : Compound::Compound(connector, pTerms(new Terms(terms, CONNECTOR::is_commutative(connector))))
{

}

Compound::Compound(Connector connector, std::vector<pTerm> &terms) : Compound::Compound(connector, pTerms(new Terms(terms, CONNECTOR::is_commutative(connector))))
{

}

Compound::Compound(Connector connector, std::initializer_list<pTerm> terms) : Compound::Compound(connector, pTerms(new Terms(terms, CONNECTOR::is_commutative(connector))))
{
    
}


