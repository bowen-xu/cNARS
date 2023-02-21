#include <string>
#include <vector>
#include "../include/Statement.h"

using string = std::string;
using std::unordered_set;
using TERM::Term;

using namespace STATEMENT;

Statement::Statement(Term& _subject, Copula _copula, Term& _predicate) : subject(_subject), predicate(_predicate)
{
    this->type = TermType::STATEMENT;
    this->copula = _copula;
    // copula = _copula;
    // is_commutative = COPULA::is_commutative(copula);
    // word = string("<") + _subject.word + COPULA::Repr[_copula] + _predicate.word + string(">");
    // word_sorted = subject.hash_value > predicate.hash_value ? word: (string("<") + predicate.word + COPULA::Repr[_copula] + subject.word + string(">"));

    // components = unordered_set<Term*>{&subject, &predicate};

    // is_higher_order = COPULA::is_higher_order(copula);
    // is_operation = predicate.is_operation;
    // complexity += (subject.complexity + predicate.complexity);
}