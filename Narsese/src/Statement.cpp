#include "../include/Statement.h"
#include <string>
#include <vector>

using string = std::string;
using std::unordered_set;
using TERM::Term;
using UTILS::hash;

using namespace STATEMENT;

Statement::Statement(pTerm _subject, Copula _copula, pTerm _predicate) : subject(_subject), predicate(_predicate)
{
    this->type = TermType::STATEMENT;
    this->copula = _copula;
    this->_is_commutative = COPULA::is_commutative(_copula);
    this->hash_value = hash(*this);
    this->complexity += (subject->complexity + predicate->complexity);
    // word = string("<") + _subject.word + COPULA::Repr[_copula] + _predicate.word + string(">");
    // word_sorted = subject.hash_value > predicate.hash_value ? word: (string("<") + predicate.word + COPULA::Repr[_copula] + subject.word + string(">"));

    // components = unordered_set<Term*>{&subject, &predicate};

    this->is_higher_order = COPULA::is_higher_order(copula);
    this->is_operation = _predicate->is_operation;

    // is_operation = predicate.is_operation;
    auto terms = {this->subject, this->predicate};
    this->_refresh_var_status(terms);
    this->_init_indexvars(this->_index_vars(), terms);
    this->_build_indexvars();
}