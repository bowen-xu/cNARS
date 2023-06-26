#include "./NarseseParser.h"
#include "Config.h"
#include "Interpreter/include/Interpreter.hpp"
#include "Narsese/include/Budget.h"
#include "Narsese/include/Compound.h"
#include "Narsese/include/Copula.h"
#include "Narsese/include/Sentence.h"
#include "Narsese/include/Statement.h"
#include "Narsese/include/Task.h"
#include "Narsese/include/Term.h"
#include "Narsese/include/Truth.h"
#include "Narsese/include/Variable.h"
#include <functional> // std::reference_wrapper
#include <iostream>
#include <memory>
// #include <list>
#include <vector>
// #include <boost/container/list.hpp>

// using std::list;

using std::shared_ptr;

// using CONFIG::Config;
using BUDGET::Budget;
using BUDGET::pBudget;
using COMPOUND::Compound;
using COMPOUND::Connector;
using COPULA::Copula;
using SENTENCE::Goal;
using SENTENCE::Judgement;
using SENTENCE::pSentence;
using SENTENCE::Quest;
using SENTENCE::Question;
using SENTENCE::Sentence;
using STATEMENT::Statement;
using TASK::Task;
using TERM::pTerm;
using TERM::Term;
using TRUTH::pTruth;
using TRUTH::Truth;
using VARIABLE::Variable;
// using namespace COPULA::COPULA;

using namespace NARSESEPARSER;

// extern INTERPRETER::Interpreter INTERPRETER::interpreter;

/*definitions*/
void *NARSESEPARSER::task(const Args &args)
{
	void *ret;
	auto n_args = args.size();
	Budget &budget = (n_args == 1) ? *(new Budget(CONFIG::priority, CONFIG::durability, CONFIG::quality)) : *((Budget *)args[0]);
	Sentence &sentence = (n_args == 1) ? *((Sentence *)args[0]) : *((Sentence *)args[1]);
	if (sentence.is_judgement())
	{
		if (budget.priority < -0.5)
			budget.priority = CONFIG::p_judgement;
		if (budget.durability < -0.5)
			budget.durability = CONFIG::d_judgement;
		if (budget.quality < -0.5)
			budget.quality = Budget::quality_from_truth(*sentence.truth);
	}
	else if (sentence.is_goal())
	{
		if (budget.priority < -0.5)
			budget.priority = CONFIG::p_goal;
		if (budget.durability < -0.5)
			budget.durability = CONFIG::d_goal;
		if (budget.quality < -0.5)
			budget.quality = Budget::quality_from_truth(*sentence.truth);
	}
	else if (sentence.is_question())
	{
		if (budget.priority < -0.5)
			budget.priority = CONFIG::p_question;
		if (budget.durability < -0.5)
			budget.durability = CONFIG::d_question;
		if (budget.quality < -0.5)
			budget.quality = 1.0;
	}
	else if (sentence.is_quest())
	{
		if (budget.priority < -0.5)
			budget.priority = CONFIG::p_quest;
		if (budget.durability < -0.5)
			budget.durability = CONFIG::d_quest;
		if (budget.quality < -0.5)
			budget.quality = 1.0;
	}
	else
	{
		throw std::runtime_error("Sentence type is invalid.");
	}

	Task &task = *(new Task(pBudget(&budget), pSentence(&sentence)));
	ret = &task;
	return ret;
}

void *NARSESEPARSER::judgement(const Args &args)
{
	void *ret;
	auto n_args = args.size();
	Term &term = *(Term *)args[0];
	Truth *truth;
	if (n_args >= 2)
	{
		truth = (Truth *)args[1];
		if (truth->f < -0.5)
			truth->f = CONFIG::f;
		if (truth->c < -0.5)
			truth->c = CONFIG::c_judgement;
		if (truth->k < -0.5)
			truth->k = CONFIG::k;
	}
	else
	{
		truth = new Truth(CONFIG::f, CONFIG::c, CONFIG::k);
	}
	auto &judgement = *(new Judgement(pTerm(&term), pTruth(truth)));
	ret = &judgement;
	return ret;
}

void *NARSESEPARSER::question(const Args &args)
{
	void *ret;
	auto n_args = args.size();
	Term &term = *(Term *)args[0];

	auto &question = *(new Question(pTerm(&term)));
	ret = &question;
	return ret;
}

void *NARSESEPARSER::goal(const Args &args)
{
	void *ret;
	auto n_args = args.size();
	Term &term = *(Term *)args[0];
	// Truth &desire = (n_args >= 2) ? *(Truth *)args[1] : *(new Truth(CONFIG::f, CONFIG::c, CONFIG::k));
	Truth *desire;
	if (n_args >= 2)
	{
		desire = (Truth *)args[1];
		if (desire->f < -0.5)
			desire->f = CONFIG::f;
		if (desire->c < -0.5)
			desire->c = CONFIG::c_goal;
		if (desire->k < -0.5)
			desire->k = CONFIG::k;
	}
	else
	{
		desire = new Truth(CONFIG::f, CONFIG::c, CONFIG::k);
	}

	auto &goal = *(new Goal(pTerm(&term), pTruth(desire)));
	ret = &goal;
	return ret;
}

void *NARSESEPARSER::quest(const Args &args)
{
	void *ret;
	auto n_args = args.size();
	Term &term = *(Term *)args[0];

	auto &quest = *(new Quest(pTerm(&term)));
	ret = &quest;
	return ret;
}

void *NARSESEPARSER::statement(const Args &args)
{
	void *ret;
	Term &subject = *(Term *)args[0];
	Copula &copula = *(Copula *)args[1];
	Term &predicate = *(Term *)args[2];
	Statement *statement;
	if (copula == Copula::Instance)
	{
		auto instance = Compound::ExtensionalSet({pTerm(&subject)});
		statement = new Statement(instance, Copula::Inheritance, pTerm(&predicate));
	}
	else if (copula == Copula::Property)
	{
		auto property = Compound::IntensionalSet({pTerm(&predicate)});
		statement = new Statement(pTerm(&subject), Copula::Inheritance, property);
	}
	else if (copula == Copula::InstanceProperty)
	{
		auto instance = Compound::ExtensionalSet({pTerm(&subject)});
		auto property = Compound::IntensionalSet({pTerm(&predicate)});
		statement = new Statement(instance, Copula::Inheritance, property);
	}
	else
	{
		statement = new Statement(pTerm(&subject), copula, pTerm(&predicate));
	}
	ret = statement;
	return ret;
}

void *NARSESEPARSER::statement_operation1(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::statement_operation2(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::inheritance(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::INHERITANCE;
	return ret;
}
void *NARSESEPARSER::similarity(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::SIMILARITY;
	return ret;
}
void *NARSESEPARSER::instance(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::INSTANCE;
	return ret;
}
void *NARSESEPARSER::property(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::PROPERTY;
	return ret;
}
void *NARSESEPARSER::instance_property(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::INSTANCEPROPERTY;
	return ret;
}
void *NARSESEPARSER::implication(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::IMPLICATION;
	return ret;
}
void *NARSESEPARSER::predictive_implication(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::PREDICTIVEIMPLICATION;
	return ret;
}
void *NARSESEPARSER::concurrent_implication(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::CONCURRENTIMPLICATION;
	return ret;
}
void *NARSESEPARSER::retrospective_implication(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::RETROSPECTIVEIMPLICATION;
	return ret;
}
void *NARSESEPARSER::equivalence(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::EQUIVALENCE;
	return ret;
}
void *NARSESEPARSER::predictive_equivalence(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::PREDICTIVEEQUIVALENCE;
	return ret;
}
void *NARSESEPARSER::concurrent_equivalence(const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::CONCURRENTEQUIVALENCE;
	return ret;
}
void *NARSESEPARSER::variable_term(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::atom_term(const Args &args)
{
	void *ret;
	auto &str = *((std::string *)args[0]);
	Term *term;
	if (INTERPRETER::interpreter.check_by_name(str) > 0)
	{
		auto key = INTERPRETER::interpreter.get_by_name(str);
		term = (Term*)INTERPRETER::interpreter.get_object(key);
	}
	else
	{
		term = (new Term());
		INTERPRETER::interpreter.put(term->hash_value, str, (void*)term);
	}

	delete &str;
	ret = term;
	return ret;
}
void *NARSESEPARSER::compound_term(const Args &args)
{
	void *ret;
	auto &compound = *(Compound *)args[0];
	ret = &compound;
	return ret;
}
void *NARSESEPARSER::statement_term(const Args &args)
{
	void *ret;
	auto &statement = *(Statement *)args[0];
	ret = &statement;
	return ret;
}
void *NARSESEPARSER::op(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::interval(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::set(const Args &args)
{
	void *ret;
	auto it = args.begin();
	auto &connector = *((Connector *)*it);
	list<pTerm> terms;

	for (it++; it != args.end(); it++)
	{
		terms.push_back(pTerm((Term *)*it));
	}
	auto &compound = *(new Compound(connector, terms));
	ret = &compound;
	return ret;
}
void *NARSESEPARSER::negation(const Args &args)
{
	void *ret;
	auto &connector = *((Connector *)args[0]);
	auto &term = *(Term *)args[1];
	auto &compound = *(new Compound(connector, pTerm(&term)));
	ret = &compound;
	return ret;
}
void *NARSESEPARSER::int_image(const Args &args)
{
	void *ret;
	ret = multi_prefix(args);
	return ret;
}

void *NARSESEPARSER::ext_image(const Args &args)
{
	void *ret;
	ret = multi_prefix(args);
	return ret;
}
void *NARSESEPARSER::multi_prefix_product(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::multi_prefix(const Args &args)
{
	void *ret;
	auto it = args.begin();
	auto &connector = *((Connector *)*it);
	list<pTerm> terms;
	// boost::container::list<int> terms2;
	// auto it2 = terms2.begin();
	// std::list<pTerm> terms;

	for (it++; it != args.end(); it++)
	{
		terms.push_back(pTerm((Term *)*it));
	}
	auto &compound = *(new Compound(connector, terms));
	// Compound(connector, {(Term *)args[1], (Term *)args[1]});
	ret = &compound;
	return ret;
}
void *NARSESEPARSER::single_prefix(const Args &args)
{
	void *ret;
	auto &connector = *((Connector *)args[0]);
	auto &compound = *(new Compound(connector, {pTerm((Term *)args[1]), pTerm((Term *)args[2])}));
	ret = &compound;
	return ret;
}
void *NARSESEPARSER::single_infix(const Args &args)
{
	void *ret;
	auto &connector = *((Connector *)args[1]);
	auto &compound = *(new Compound(connector, {pTerm((Term *)args[0]), pTerm((Term *)args[2])}));
	ret = &compound;
	return ret;
}
void *NARSESEPARSER::multi_prod_expr(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::multi_disj_expr(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::multi_conj_expr(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::multi_sequential_expr(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::multi_parallel_expr(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::multi_intint_expr(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::multi_extint_expr(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::con_conjunction(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::CONJUNCTION;
	return ret;
}
void *NARSESEPARSER::con_disjunction(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::DISJUNCTION;
	return ret;
}
void *NARSESEPARSER::con_parallel_events(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::PARALLEL_EVENTS;
	return ret;
}
void *NARSESEPARSER::con_sequential_events(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::SEQUENTIAL_EVENTS;
	return ret;
}
void *NARSESEPARSER::con_intensional_intersection(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_INTERSECTION;
	return ret;
}
void *NARSESEPARSER::con_extensional_intersection(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_INTERSECTION;
	return ret;
}
void *NARSESEPARSER::con_extensional_difference(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_DIFFERENCE;
	return ret;
}
void *NARSESEPARSER::con_intensional_difference(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_DIFFERENCE;
	return ret;
}
void *NARSESEPARSER::con_int_set(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_SET;
	return ret;
}
void *NARSESEPARSER::con_ext_set(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_SET;
	return ret;
}
void *NARSESEPARSER::con_negation(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::NEGATION;
	return ret;
}
void *NARSESEPARSER::con_int_image(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_IMAGE;
	return ret;
}
void *NARSESEPARSER::con_ext_image(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_IMAGE;
	return ret;
}
void *NARSESEPARSER::con_product(const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::PRODUCT;
	return ret;
}
void *NARSESEPARSER::independent_var(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::dependent_var(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::query_var(const Args &args)
{
	void *ret;
	auto name = std::string((char *)args[0]);
	auto var = Variable(VARIABLE::VarPrefix::Qeury, name);
	
	return ret;
}
void *NARSESEPARSER::tense_time(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::tense_future(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::tense_present(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::tense_past(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::truth(const Args &args)
{
	void *ret;
	double f, c, k;
	f = args.size() >= 1 ? std::stod((char *)args[0]) : -1.0;
	c = args.size() >= 2 ? std::stod((char *)args[1]) : -1.0;
	k = args.size() >= 3 ? std::stod((char *)args[2]) : CONFIG::k;

	// ret = (void *)value;
	auto &truth = *(new Truth(f, c, k));
	ret = &truth;
	return ret;
}
void *NARSESEPARSER::budget(const Args &args)
{
	void *ret;
	double p, d, q;
	p = args.size() >= 1 ? std::stod((char *)args[0]) : -1.0;
	d = args.size() >= 2 ? std::stod((char *)args[1]) : -1.0;
	q = args.size() >= 3 ? std::stod((char *)args[2]) : -1.0;

	// ret = (void *)value;
	auto &budget = *(new Budget(p, d, q));
	ret = &budget;
	return ret;
}
void *NARSESEPARSER::string_raw(const Args &args)
{
	void *ret;
	auto &str = *(new std::string((char *)args[0]));
	ret = &str;
	return ret;
}
void *NARSESEPARSER::string(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::quality(const Args &args)
{
	void *ret;
	ret = args[0];
	return ret;
}
void *NARSESEPARSER::durability(const Args &args)
{
	void *ret;
	ret = args[0];
	return ret;
}
void *NARSESEPARSER::priority(const Args &args)
{
	void *ret;
	ret = args[0];
	return ret;
}
void *NARSESEPARSER::k_evidence(const Args &args)
{
	void *ret;
	return ret;
}
void *NARSESEPARSER::confidence(const Args &args)
{
	void *ret;
	ret = args[0]; // e.g., "0.90"
	return ret;
}
void *NARSESEPARSER::frequency(const Args &args)
{
	void *ret;
	ret = args[0]; // e.g., "0.90"
	return ret;
}
void *NARSESEPARSER::integer(const Args &args)
{
	void *ret;
	ret = args[0]; // e.g., 123
	return ret;
}

NarseseParser::NarseseParser() : Parser()
{
	/*register*/
	regist("task", task);
	regist("judgement", judgement);
	regist("question", question);
	regist("goal", goal);
	regist("quest", quest);
	regist("statement", statement);
	regist("statement_operation1", statement_operation1);
	regist("statement_operation2", statement_operation2);
	regist("inheritance", inheritance);
	regist("similarity", similarity);
	regist("instance", instance);
	regist("property", property);
	regist("instance_property", instance_property);
	regist("implication", implication);
	regist("predictive_implication", predictive_implication);
	regist("concurrent_implication", concurrent_implication);
	regist("retrospective_implication", retrospective_implication);
	regist("equivalence", equivalence);
	regist("predictive_equivalence", predictive_equivalence);
	regist("concurrent_equivalence", concurrent_equivalence);
	regist("variable_term", variable_term);
	regist("atom_term", atom_term);
	regist("compound_term", compound_term);
	regist("statement_term", statement_term);
	regist("op", op);
	regist("interval", interval);
	regist("set", set);
	regist("negation", negation);
	regist("int_image", int_image);
	regist("ext_image", ext_image);
	regist("multi_prefix_product", multi_prefix_product);
	regist("multi_prefix", multi_prefix);
	regist("single_prefix", single_prefix);
	regist("single_infix", single_infix);
	regist("multi_prod_expr", multi_prod_expr);
	regist("multi_disj_expr", multi_disj_expr);
	regist("multi_conj_expr", multi_conj_expr);
	regist("multi_sequential_expr", multi_sequential_expr);
	regist("multi_parallel_expr", multi_parallel_expr);
	regist("multi_intint_expr", multi_intint_expr);
	regist("multi_extint_expr", multi_extint_expr);
	regist("con_conjunction", con_conjunction);
	regist("con_disjunction", con_disjunction);
	regist("con_parallel_events", con_parallel_events);
	regist("con_sequential_events", con_sequential_events);
	regist("con_product", con_product);
	regist("con_intensional_intersection", con_intensional_intersection);
	regist("con_extensional_intersection", con_extensional_intersection);
	regist("con_extensional_difference", con_extensional_difference);
	regist("con_intensional_difference", con_intensional_difference);
	regist("con_int_set", con_int_set);
	regist("con_ext_set", con_ext_set);
	regist("con_negation", con_negation);
	regist("con_int_image", con_int_image);
	regist("con_ext_image", con_ext_image);
	regist("independent_var", independent_var);
	regist("dependent_var", dependent_var);
	regist("query_var", query_var);
	regist("tense_time", tense_time);
	regist("tense_future", tense_future);
	regist("tense_present", tense_present);
	regist("tense_past", tense_past);
	regist("truth", truth);
	regist("budget", budget);
	regist("string_raw", string_raw);
	regist("string", string);
	regist("quality", quality);
	regist("durability", durability);
	regist("priority", priority);
	regist("k_evidence", k_evidence);
	regist("confidence", confidence);
	regist("frequency", frequency);
	regist("integer", integer);
}
