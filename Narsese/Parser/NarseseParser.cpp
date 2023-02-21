#include "./NarseseParser.h"
#include "Narsese/include/Term.h"
#include "Narsese/include/Copula.h"
#include "Narsese/include/Statement.h"
#include "Narsese/include/Compound.h"
#include "Narsese/include/Truth.h"
#include "Narsese/include/Sentence.h"
#include "Narsese/include/Task.h"
#include "Config.h"
#include "Narsese/include/Budget.h"
#include "Narsese/include/Task.h"
#include <iostream>
#include <list>
#include <functional>   // std::reference_wrapper
// using CONFIG::Config;
using BUDGET::Budget;
using COMPOUND::Compound;
using COMPOUND::Connector;
using COPULA::Copula;
using SENTENCE::Goal;
using SENTENCE::Judgement;
using SENTENCE::Quest;
using SENTENCE::Question;
using SENTENCE::Sentence;
using STATEMENT::Statement;
using TASK::Task;
using TERM::Term;
using TRUTH::Truth;
// using namespace COPULA::COPULA;

using namespace NARSESEPARSER;



/*definitions*/
void* NARSESEPARSER::task(Args& args)
{
    void* ret;
    auto n_args = args.size();
    Budget &budget = (n_args == 1) ? *(new Budget(CONFIG::priority, CONFIG::durability, CONFIG::quality)) : *((Budget *)args[0]);
    Sentence& sentence = (n_args == 1) ? *((Sentence *)args[0]) : *((Sentence *)args[1]);
    Task &task = *(new Task(budget, sentence));
    ret = &task;
    return ret;
}

void* NARSESEPARSER::judgement(Args& args)
{
    void* ret;
    auto n_args = args.size();
    Term &term = *(Term *)args[0];
    Truth &truth = (n_args >= 2) ? *(Truth *)args[1] : *(new Truth(CONFIG::f, CONFIG::c, CONFIG::k));

    auto &judgement = *(new Judgement(term, truth));
    ret = &judgement;
    return ret;
}

void* NARSESEPARSER::question(Args& args)
{
    void* ret;
    auto n_args = args.size();
    Term &term = *(Term *)args[0];

    auto &question = *(new Question(term));
    ret = &question;
    return ret;
}

void* NARSESEPARSER::goal(Args& args)
{
    void* ret;
    auto n_args = args.size();
    Term &term = *(Term *)args[0];
    Truth &desire = (n_args >= 2) ? *(Truth *)args[1] : *(new Truth(CONFIG::f, CONFIG::c, CONFIG::k));

    auto &goal = *(new Goal(term, desire));
    ret = &goal;
    return ret;
}

void* NARSESEPARSER::quest(Args& args)
{
    void* ret;
    auto n_args = args.size();
    Term &term = *(Term *)args[0];

    auto &quest = *(new Quest(term));
    ret = &quest;
    return ret;
}

void* NARSESEPARSER::statement(Args& args)
{
    void* ret;
    Term & subject = *(Term*)args[0];
    Copula & copula = *(Copula*)args[1];
    Term & predicate = *(Term*)args[2];
    Statement &statement = *(new Statement(subject, copula, predicate));
    ret = &statement;
    return ret;
}

void* NARSESEPARSER::statement_operation1(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::statement_operation2(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::inheritance(Args& args)
{
    void* ret;
    ret = (void*)&COPULA::INHERITANCE;
    return ret;
}
void* NARSESEPARSER::similarity(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::instance(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::property(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::instance_property(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::implication(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::predictive_implication(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::concurrent_implication(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::retrospective_implication(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::equivalence(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::predictive_equivalence(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::concurrent_equivalence(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::variable_term(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::atom_term(Args& args)
{
    void* ret;
    auto& str = *((std::string*)args[0]);
    auto& term = *(new Term(str));

    delete &str;
    ret = &term;
    return ret;
}
void* NARSESEPARSER::compound_term(Args& args)
{
	void* ret;
    auto &compound = *(Compound *)args[0];
    ret = &compound;
    return ret;
}
void* NARSESEPARSER::statement_term(Args& args)
{
    void* ret;
    return ret;
}
void* NARSESEPARSER::op(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::interval(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::set(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::negation(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::int_image(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::ext_image(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_prefix_product(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_prefix(Args& args)
{
	void* ret;
    auto it = args.begin();
    auto& connector = *((Connector *)*it);
    std::list<Term*> terms;
    
    for (it++; it != args.end(); it++)
    {
        terms.push_back((Term *)*it);
    }
    auto &compound = *(new Compound(connector, terms));
    // Compound(connector, {(Term *)args[1], (Term *)args[1]});
    ret = &compound;
    return ret;
}
void* NARSESEPARSER::single_prefix(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::single_infix(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_prod_expr(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_disj_expr(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_conj_expr(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_sequential_expr(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_parallel_expr(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_intint_expr(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::multi_extint_expr(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::con_conjunction(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::CONJUNCTION;
    return ret;
}
void* NARSESEPARSER::con_disjunction(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::DISJUNCTION;
	return ret;
}
void* NARSESEPARSER::con_parallel_events(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::PARALLEL_EVENTS;
	return ret;
}
void* NARSESEPARSER::con_sequential_events(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::SEQUENTIAL_EVENTS;
	return ret;
}
void* NARSESEPARSER::con_intensional_intersection(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::INTENSIONAL_INTERSECTION;
	return ret;
}
void* NARSESEPARSER::con_extensional_intersection(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::EXTENSIONAL_INTERSECTION;
	return ret;
}
void* NARSESEPARSER::con_extensional_difference(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::EXTENSIONAL_DIFFERENCE;
	return ret;
}
void* NARSESEPARSER::con_intensional_difference(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::INTENSIONAL_DIFFERENCE;
	return ret;
}
void* NARSESEPARSER::con_int_set(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::INTENSIONAL_SET;
	return ret;
}
void* NARSESEPARSER::con_ext_set(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::EXTENSIONAL_SET;
	return ret;
}
void* NARSESEPARSER::con_negation(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::NEGATION;
	return ret;
}
void* NARSESEPARSER::con_int_image(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::INTENSIONAL_IMAGE;
	return ret;
}
void* NARSESEPARSER::con_ext_image(Args& args)
{
	void* ret;
    ret = (void*)&CONNECTOR::EXTENSIONAL_IMAGE;
	return ret;
}
void* NARSESEPARSER::independent_var(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::dependent_var(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::query_var(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::tense_time(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::tense_future(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::tense_present(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::tense_past(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::truth(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::budget(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::string_raw(Args& args)
{
    void* ret;
    auto& str = *(new std::string((char*)args[0]));
    ret = &str;
    return ret;
}
void* NARSESEPARSER::string(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::quality(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::durability(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::priority(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::k_evidence(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::confidence(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::frequency(Args& args)
{
	void* ret;
	return ret;
}
void* NARSESEPARSER::integer(Args& args)
{
	void* ret;
	return ret;
}

NarseseParser::NarseseParser() : Parser()
{
    /*register*/
	regist(                         "task",                          task );
	regist(                    "judgement",                     judgement );
	regist(                     "question",                      question );
	regist(                         "goal",                          goal );
	regist(                        "quest",                         quest );
	regist(                    "statement",                     statement );
	regist(         "statement_operation1",          statement_operation1 );
	regist(         "statement_operation2",          statement_operation2 );
	regist(                  "inheritance",                   inheritance );
	regist(                   "similarity",                    similarity );
	regist(                     "instance",                      instance );
	regist(                     "property",                      property );
	regist(            "instance_property",             instance_property );
	regist(                  "implication",                   implication );
	regist(       "predictive_implication",        predictive_implication );
	regist(       "concurrent_implication",        concurrent_implication );
	regist(    "retrospective_implication",     retrospective_implication );
	regist(                  "equivalence",                   equivalence );
	regist(       "predictive_equivalence",        predictive_equivalence );
	regist(       "concurrent_equivalence",        concurrent_equivalence );
	regist(                "variable_term",                 variable_term );
	regist(                    "atom_term",                     atom_term );
	regist(                "compound_term",                 compound_term );
	regist(               "statement_term",                statement_term );
	regist(                           "op",                            op );
	regist(                     "interval",                      interval );
	regist(                          "set",                           set );
	regist(                     "negation",                      negation );
	regist(                    "int_image",                     int_image );
	regist(                    "ext_image",                     ext_image );
	regist(         "multi_prefix_product",          multi_prefix_product );
	regist(                 "multi_prefix",                  multi_prefix );
	regist(                "single_prefix",                 single_prefix );
	regist(                 "single_infix",                  single_infix );
	regist(              "multi_prod_expr",               multi_prod_expr );
	regist(              "multi_disj_expr",               multi_disj_expr );
	regist(              "multi_conj_expr",               multi_conj_expr );
	regist(        "multi_sequential_expr",         multi_sequential_expr );
	regist(          "multi_parallel_expr",           multi_parallel_expr );
	regist(            "multi_intint_expr",             multi_intint_expr );
	regist(            "multi_extint_expr",             multi_extint_expr );
	regist(              "con_conjunction",               con_conjunction );
	regist(              "con_disjunction",               con_disjunction );
	regist(          "con_parallel_events",           con_parallel_events );
	regist(        "con_sequential_events",         con_sequential_events );
	regist( "con_intensional_intersection",  con_intensional_intersection );
	regist( "con_extensional_intersection",  con_extensional_intersection );
	regist(   "con_extensional_difference",    con_extensional_difference );
	regist(   "con_intensional_difference",    con_intensional_difference );
	regist(                  "con_int_set",                   con_int_set );
	regist(                  "con_ext_set",                   con_ext_set );
	regist(                 "con_negation",                  con_negation );
	regist(                "con_int_image",                 con_int_image );
	regist(                "con_ext_image",                 con_ext_image );
	regist(              "independent_var",               independent_var );
	regist(                "dependent_var",                 dependent_var );
	regist(                    "query_var",                     query_var );
	regist(                   "tense_time",                    tense_time );
	regist(                 "tense_future",                  tense_future );
	regist(                "tense_present",                 tense_present );
	regist(                   "tense_past",                    tense_past );
	regist(                        "truth",                         truth );
	regist(                       "budget",                        budget );
	regist(                   "string_raw",                    string_raw );
	regist(                       "string",                        string );
	regist(                      "quality",                       quality );
	regist(                   "durability",                    durability );
	regist(                     "priority",                      priority );
	regist(                   "k_evidence",                    k_evidence );
	regist(                   "confidence",                    confidence );
	regist(                    "frequency",                     frequency );
	regist(                      "integer",                       integer );
}
