#include "./NarseseParser.h"
#include "Config.h"
#include "Interpreter/include/Interpreter.hpp"
// #include "Narsese/include/Budget.h"
// #include "Narsese/include/Compound.h"
// #include "Narsese/include/Copula.h"
// #include "Narsese/include/Interval.h"
// #include "Narsese/include/Operation.h"
// #include "Narsese/include/Sentence.h"
// #include "Narsese/include/Statement.h"
// #include "Narsese/include/Task.h"
// #include "Narsese/include/Term.h"
// #include "Narsese/include/Truth.h"
// #include "Narsese/include/Variable.h"
#include "Narsese/include/Narsese.h"
#include <functional> // std::reference_wrapper
#include <iostream>
#include <memory>
// #include <list>
#include <tuple>
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
using INTERVAL::Interval;
using INTERVAL::pInterval;
using OPERATION::Operation;
using OPERATION::pOperation;
using SENTENCE::Goal;
using SENTENCE::Judgement;
using SENTENCE::pSentence;
using SENTENCE::pStamp;
using SENTENCE::Quest;
using SENTENCE::Question;
using SENTENCE::Sentence;
using SENTENCE::Stamp;
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

template <typename _T = pTerm>
inline _T get(void *obj)
{
	_T ret = _T(*(_T *)obj);
	delete (_T *)obj;
	return ret;
}

/*definitions*/
void *NARSESEPARSER::task(Parser *self, const Args &args)
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

void *NARSESEPARSER::judgement(Parser *self, const Args &args)
{
	void *ret;
	auto n_args = args.size();
	pTerm term = get(args[0]);
	Truth *truth = nullptr;
	Stamp *stamp = nullptr;

	for (auto it = args.begin() + 1; it != args.end(); it++)
	{
		auto &arg = *it;
		void *ptr;
		int mark;
		std::tie(mark, ptr) = *(std::tuple<int, void *> *)arg;
		delete (std::tuple<int, void *> *)arg;
		if (mark == 0) // tense
		{
			auto time = *(signed int *)ptr;
			delete (signed int *)ptr;
			stamp = new Stamp(time, GLOBAL::time, -1, nullptr, false);
		}
		else if (mark == 1)
		{
			truth = (Truth *)ptr;
		}
	}

	if (stamp == nullptr)
	{
		stamp = new Stamp(true);
	}

	if (truth == nullptr)
	{
		truth = new Truth(CONFIG::f, CONFIG::c, CONFIG::k);
	}
	else
	{
		if (truth->f < -0.5)
			truth->f = CONFIG::f;
		if (truth->c < -0.5)
			truth->c = CONFIG::c_judgement;
		if (truth->k < -0.5)
			truth->k = CONFIG::k;
	}

	auto &judgement = *(new Judgement(term, pTruth(truth), pStamp(stamp)));
	ret = &judgement;
	return ret;
}

void *NARSESEPARSER::question(Parser *self, const Args &args)
{
	void *ret;
	auto n_args = args.size();
	pTerm term = get(args[0]);
	Stamp *stamp = nullptr;
	for (auto it = args.begin() + 1; it != args.end(); it++)
	{
		auto &arg = *it;
		void *ptr;
		int mark;

		std::tie(mark, ptr) = *(std::tuple<int, void *> *)arg;
		delete (std::tuple<int, void *> *)arg;
		if (mark == 0) // tense
		{
			auto time = *(signed int *)ptr;
			delete (signed int *)ptr;
			stamp = new Stamp(time, GLOBAL::time, -1, nullptr, false);
		}
	}

	if (stamp == nullptr)
	{
		stamp = new Stamp(true);
	}

	auto &question = *(new Question(term, pStamp(stamp)));
	ret = &question;
	return ret;
}

void *NARSESEPARSER::goal(Parser *self, const Args &args)
{
	void *ret;
	auto n_args = args.size();
	pTerm term = get(args[0]);
	// Truth &desire = (n_args >= 2) ? *(Truth *)args[1] : *(new Truth(CONFIG::f, CONFIG::c, CONFIG::k));
	Truth *desire = nullptr;
	Stamp *stamp = nullptr;
	for (auto it = args.begin() + 1; it != args.end(); it++)
	{
		auto &arg = *it;
		void *ptr;
		int mark;
		std::tie(mark, ptr) = *(std::tuple<int, void *> *)arg;
		delete (std::tuple<int, void *> *)arg;
		if (mark == 0) // tense
		{
			auto time = *(signed int *)ptr;
			delete (signed int *)ptr;
			stamp = new Stamp(time, GLOBAL::time, -1, nullptr, false);
		}
		else if (mark == 1)
		{
			desire = (Truth *)ptr;
		}
	}

	if (stamp == nullptr)
	{
		stamp = new Stamp(true);
	}

	if (desire == nullptr)
	{
		desire = new Truth(CONFIG::f, CONFIG::c, CONFIG::k);
	}
	else
	{
		if (desire->f < -0.5)
			desire->f = CONFIG::f;
		if (desire->c < -0.5)
			desire->c = CONFIG::c_goal;
		if (desire->k < -0.5)
			desire->k = CONFIG::k;
	}

	auto &goal = *(new Goal(term, pTruth(desire), pStamp(stamp)));
	ret = &goal;
	return ret;
}

void *NARSESEPARSER::quest(Parser *self, const Args &args)
{
	void *ret;
	auto n_args = args.size();
	pTerm term = get(args[0]);

	Stamp *stamp = nullptr;
	for (auto it = args.begin() + 1; it != args.end(); it++)
	{
		auto &arg = *it;
		void *ptr;
		int mark;

		std::tie(mark, ptr) = *(std::tuple<int, void *> *)arg;
		delete (std::tuple<int, void *> *)arg;
		if (mark == 0) // tense
		{
			auto time = *(signed int *)ptr;
			delete (signed int *)ptr;
			stamp = new Stamp(time, GLOBAL::time, -1, nullptr, false);
		}
	}

	if (stamp == nullptr)
	{
		stamp = new Stamp(true);
	}

	auto &quest = *(new Quest(term, pStamp(stamp)));
	ret = &quest;
	return ret;
}

void *NARSESEPARSER::statement(Parser *self, const Args &args)
{
	void *ret;
	pTerm subject = get(args[0]);
	Copula &copula = *(Copula *)args[1];
	pTerm predicate = get(args[2]);
	Statement *statement;
	if (copula == Copula::Instance)
	{
		auto instance = Compound::ExtensionalSet({subject});
		statement = new Statement(instance, Copula::Inheritance, predicate, true);
	}
	else if (copula == Copula::Property)
	{
		auto property = Compound::IntensionalSet({predicate});
		statement = new Statement(subject, Copula::Inheritance, property, true);
	}
	else if (copula == Copula::InstanceProperty)
	{
		auto instance = Compound::ExtensionalSet({subject});
		auto property = Compound::IntensionalSet({predicate});
		statement = new Statement(instance, Copula::Inheritance, property, true);
	}
	else
	{
		statement = new Statement(subject, copula, predicate, true);
	}
	ret = new pTerm(statement);
	return ret;
}

void *NARSESEPARSER::statement_operation1(Parser *self, const Args &args)
{
	void *ret;
	// void *term_op = *args.begin();
	std::vector<pTerm> terms;
	for (auto it = args.begin() + 1; it != args.end(); it++)
	{
		auto term = get(*it);
		terms.push_back(term);
	}
	auto op = get(args[0]);
	auto &stat = *new pTerm(new Statement(pTerm(new Compound(CONNECTOR::PRODUCT, terms, true)), COPULA::INHERITANCE, op, true));
	ret = &stat;
	return ret;
}
void *NARSESEPARSER::statement_operation2(Parser *self, const Args &args)
{
	void *ret;
	auto term_op = NARSESEPARSER::operation(self, {args[0]});
	Args args2 = {term_op};
	args2.insert(args2.end(), args.begin() + 1, args.end());
	ret = NARSESEPARSER::statement_operation1(self, args2);
	return ret;
}
void *NARSESEPARSER::inheritance(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::INHERITANCE;
	return ret;
}
void *NARSESEPARSER::similarity(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::SIMILARITY;
	return ret;
}
void *NARSESEPARSER::instance(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::INSTANCE;
	return ret;
}
void *NARSESEPARSER::property(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::PROPERTY;
	return ret;
}
void *NARSESEPARSER::instance_property(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::INSTANCEPROPERTY;
	return ret;
}
void *NARSESEPARSER::implication(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::IMPLICATION;
	return ret;
}
void *NARSESEPARSER::predictive_implication(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::PREDICTIVEIMPLICATION;
	return ret;
}
void *NARSESEPARSER::concurrent_implication(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::CONCURRENTIMPLICATION;
	return ret;
}
void *NARSESEPARSER::retrospective_implication(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::RETROSPECTIVEIMPLICATION;
	return ret;
}
void *NARSESEPARSER::equivalence(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::EQUIVALENCE;
	return ret;
}
void *NARSESEPARSER::predictive_equivalence(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::PREDICTIVEEQUIVALENCE;
	return ret;
}
void *NARSESEPARSER::concurrent_equivalence(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&COPULA::CONCURRENTEQUIVALENCE;
	return ret;
}
void *NARSESEPARSER::variable_term(Parser *self, const Args &args)
{
	void *ret;
	auto var = (pTerm *)args[0];
	ret = var;
	return ret;
}
void *NARSESEPARSER::atom_term(Parser *self, const Args &args)
{
	void *ret;
	auto &str = *((std::string *)args[0]);
	pTerm *term;
	if (INTERPRETER::interpreter.check_by_name(str) > 0)
	{
		auto key = INTERPRETER::interpreter.get_by_name(str);
		term = (pTerm *)INTERPRETER::interpreter.get_object(key);
	}
	else
	{
		term = new pTerm(new Term(), &INTERPRETER::interpreter);
		INTERPRETER::interpreter.put((*term)->hash_value, str, (void *)term);
	}

	delete &str;
	ret = new pTerm(*term);
	return ret;
}
void *NARSESEPARSER::compound_term(Parser *self, const Args &args)
{
	void *ret;
	auto compound = (pTerm *)args[0];
	ret = compound;
	return ret;
}
void *NARSESEPARSER::statement_term(Parser *self, const Args &args)
{
	void *ret;
	auto statement = (pTerm *)args[0];
	ret = statement;
	return ret;
}
void *NARSESEPARSER::operation(Parser *self, const Args &args)
{
	void *ret;
	auto &str = *((std::string *)args[0]);
	auto str_op = "^" + str;
	pTerm *term;
	if (INTERPRETER::interpreter.check_by_name(str) > 0)
	{
		auto key = INTERPRETER::interpreter.get_by_name(str_op);
		term = (pTerm *)INTERPRETER::interpreter.get_object(key);
	}
	else
	{
		term = new pTerm(new Operation(), &INTERPRETER::interpreter);
		INTERPRETER::interpreter.put((*term)->hash_value, str_op, (void *)term);
	}

	delete &str;
	ret = new pTerm(*term);
	return ret;
}
void *NARSESEPARSER::interval(Parser *self, const Args &args)
{
	void *ret;
	double dt = *(double *)args[0];
	auto interval = (new pTerm(new Interval((signed int)dt)));
	ret = interval;
	delete (double *)args[0];
	return ret;
}
void *NARSESEPARSER::set(Parser *self, const Args &args)
{
	void *ret;
	auto it = args.begin();
	auto &connector = *((Connector *)*it);
	std::list<pTerm> terms;

	for (it++; it != args.end(); it++)
	{
		auto term = get(*it);
		terms.push_back(term);
	}
	auto compound = (new pTerm(new Compound(connector, terms, true)));
	ret = compound;
	return ret;
}
void *NARSESEPARSER::negation(Parser *self, const Args &args)
{
	void *ret;
	auto &connector = *((Connector *)args[0]);
	auto term = get(args[1]);
	auto compound = (new pTerm(new Compound(connector, term, true)));
	ret = compound;
	return ret;
}
void *NARSESEPARSER::int_image(Parser *self, const Args &args)
{
	void *ret;
	ret = multi_prefix(self, args);
	return ret;
}

void *NARSESEPARSER::ext_image(Parser *self, const Args &args)
{
	void *ret;
	ret = multi_prefix(self, args);
	return ret;
}
void *NARSESEPARSER::multi_infix(Parser *self, const Args &args)
{
	void *ret;
	ret = args[0];
	return ret;
}
void *NARSESEPARSER::multi_prefix_product(Parser *self, const Args &args)
{
	void *ret;
	Args args2 = {(void *)&CONNECTOR::PRODUCT};
	args2.insert(args2.end(), args.begin(), args.end());
	ret = multi_prefix(self, args2);
	return ret;
}
void *NARSESEPARSER::multi_prefix(Parser *self, const Args &args)
{
	void *ret;
	auto it = args.begin();
	auto &connector = *((Connector *)*it);
	std::list<pTerm> terms;

	for (it++; it != args.end(); it++)
	{
		auto term = get(*it);
		terms.push_back(term);
	}
	auto compound = (new pTerm(new Compound(connector, terms, true)));
	ret = compound;
	return ret;
}
void *NARSESEPARSER::single_prefix(Parser *self, const Args &args)
{
	void *ret;
	auto &connector = *((Connector *)args[0]);
	auto term1 = get(args[1]);
	auto term2 = get(args[2]);
	auto compound = (new pTerm(new Compound(connector, {term1, term2}, true)));
	ret = compound;
	return ret;
}
void *NARSESEPARSER::single_infix(Parser *self, const Args &args)
{
	void *ret;
	auto &connector = *((Connector *)args[1]);
	auto term1 = get(args[0]);
	auto term2 = get(args[2]);
	auto compound = (new pTerm(new Compound(connector, {term1, term2}, true)));
	ret = compound;
	return ret;
}
void *NARSESEPARSER::multi_prod_expr(Parser *self, const Args &args)
{
	void *ret;
	ret = NARSESEPARSER::multi_prefix_product(self, args);
	return ret;
}
void *NARSESEPARSER::multi_disj_expr(Parser *self, const Args &args)
{
	void *ret;
	auto connector = (void *)&CONNECTOR::DISJUNCTION;
	Args args2{connector};
	args2.insert(args2.end(), args.begin(), args.end());
	ret = NARSESEPARSER::multi_prefix(self, args2);
	return ret;
}
void *NARSESEPARSER::multi_conj_expr(Parser *self, const Args &args)
{
	void *ret;
	auto connector = (void *)&CONNECTOR::CONJUNCTION;
	Args args2{connector};
	args2.insert(args2.end(), args.begin(), args.end());
	ret = NARSESEPARSER::multi_prefix(self, args2);
	return ret;
}
void *NARSESEPARSER::multi_sequential_expr(Parser *self, const Args &args)
{
	void *ret;
	auto connector = (void *)&CONNECTOR::SEQUENTIAL_EVENTS;
	Args args2{connector};
	args2.insert(args2.end(), args.begin(), args.end());
	ret = NARSESEPARSER::multi_prefix(self, args2);
	return ret;
}
void *NARSESEPARSER::multi_parallel_expr(Parser *self, const Args &args)
{
	void *ret;
	auto connector = (void *)&CONNECTOR::PARALLEL_EVENTS;
	Args args2{connector};
	args2.insert(args2.end(), args.begin(), args.end());
	ret = NARSESEPARSER::multi_prefix(self, args2);
	return ret;
}
void *NARSESEPARSER::multi_intint_expr(Parser *self, const Args &args)
{
	void *ret;
	auto connector = (void *)&CONNECTOR::INTENSIONAL_INTERSECTION;
	Args args2{connector};
	args2.insert(args2.end(), args.begin(), args.end());
	ret = NARSESEPARSER::multi_prefix(self, args2);
	return ret;
}
void *NARSESEPARSER::multi_extint_expr(Parser *self, const Args &args)
{
	void *ret;
	auto connector = (void *)&CONNECTOR::EXTENSIONAL_INTERSECTION;
	Args args2{connector};
	args2.insert(args2.end(), args.begin(), args.end());
	ret = NARSESEPARSER::multi_prefix(self, args2);
	return ret;
}
void *NARSESEPARSER::con_conjunction(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::CONJUNCTION;
	return ret;
}
void *NARSESEPARSER::con_disjunction(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::DISJUNCTION;
	return ret;
}
void *NARSESEPARSER::con_parallel_events(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::PARALLEL_EVENTS;
	return ret;
}
void *NARSESEPARSER::con_sequential_events(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::SEQUENTIAL_EVENTS;
	return ret;
}
void *NARSESEPARSER::con_intensional_intersection(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_INTERSECTION;
	return ret;
}
void *NARSESEPARSER::con_extensional_intersection(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_INTERSECTION;
	return ret;
}
void *NARSESEPARSER::con_extensional_difference(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_DIFFERENCE;
	return ret;
}
void *NARSESEPARSER::con_intensional_difference(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_DIFFERENCE;
	return ret;
}
void *NARSESEPARSER::con_int_set(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_SET;
	return ret;
}
void *NARSESEPARSER::con_ext_set(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_SET;
	return ret;
}
void *NARSESEPARSER::con_negation(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::NEGATION;
	return ret;
}
void *NARSESEPARSER::con_int_image(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::INTENSIONAL_IMAGE;
	return ret;
}
void *NARSESEPARSER::con_ext_image(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::EXTENSIONAL_IMAGE;
	return ret;
}
void *NARSESEPARSER::con_product(Parser *self, const Args &args)
{
	void *ret;
	ret = (void *)&CONNECTOR::PRODUCT;
	return ret;
}
void *NARSESEPARSER::independent_var(Parser *self, const Args &args)
{
	void *ret;
	auto word = (std::string *)args[0];
	auto name = VARIABLE::Repr[VARIABLE::VarPrefix::Independent] + *word;
	delete word;
	auto &var = *(new pTerm(new Variable(VARIABLE::VarPrefix::Independent, name)));
	auto &names_map = self->names_ivar;
	auto str = name.c_str();
	if (names_map.count(str) == 0)
		names_map[str] = names_map.size();
	auto idx = names_map[name.c_str()];
	var->_vars_independent->add(idx, {});
	ret = &var;
	return ret;
}
void *NARSESEPARSER::dependent_var(Parser *self, const Args &args)
{
	void *ret;
	auto word = (std::string *)args[0];
	auto name = VARIABLE::Repr[VARIABLE::VarPrefix::Dependent] + *word;
	delete word;
	auto &var = *(new pTerm(new Variable(VARIABLE::VarPrefix::Dependent, name)));
	auto &names_map = self->names_dvar;
	auto str = name.c_str();
	if (names_map.count(str) == 0)
		names_map[str] = names_map.size();
	auto idx = names_map[name.c_str()];
	var->_vars_dependent->add(idx, {});
	ret = &var;
	return ret;
}
void *NARSESEPARSER::query_var(Parser *self, const Args &args)
{
	void *ret;
	auto word = (std::string *)args[0];
	auto name = VARIABLE::Repr[VARIABLE::VarPrefix::Qeury] + *word;
	delete word;
	auto &var = *(new pTerm(new Variable(VARIABLE::VarPrefix::Qeury, name)));
	auto &names_map = self->names_qvar;
	auto str = name.c_str();
	if (names_map.count(str) == 0)
		names_map[str] = names_map.size();
	auto idx = names_map[name.c_str()];
	var->_vars_query->add(idx, {});
	ret = &var;
	return ret;
}
void *NARSESEPARSER::tense_time(Parser *self, const Args &args)
{
	void *ret;
	double t = *(double *)args[0];
	ret = new std::tuple(0, (new (signed int)(t)));
	delete (double *)args[0];
	return ret;
}
void *NARSESEPARSER::tense_future(Parser *self, const Args &args)
{
	void *ret;
	ret = new std::tuple(0, (new (signed int)(CONFIG::temporal_duration)));
	return ret;
}
void *NARSESEPARSER::tense_present(Parser *self, const Args &args)
{
	void *ret;
	ret = new std::tuple(0, (new (signed int)(0)));

	return ret;
}
void *NARSESEPARSER::tense_past(Parser *self, const Args &args)
{
	void *ret;
	ret = new std::tuple(0, (new (signed int)(-CONFIG::temporal_duration)));
	return ret;
}
void *NARSESEPARSER::truth(Parser *self, const Args &args)
{
	void *ret;
	double f, c, k;
	if (args.size() >= 1)
	{
		f = *(double *)args[0];
		delete (double *)args[0];
	}
	else
		f = -1.0;
	if (args.size() >= 2)
	{
		c = *(double *)args[1];
		delete (double *)args[1];
	}
	else
		c = -1.0;
	if (args.size() >= 3)
	{
		k = *(double *)args[2];
		delete (double *)args[2];
	}
	else
		k = CONFIG::k;

	// ret = (void *)value;
	auto &truth = *(new Truth(f, c, k));
	ret = new std::tuple(1, &truth);
	return ret;
}
void *NARSESEPARSER::budget(Parser *self, const Args &args)
{
	void *ret;
	double p, d, q;
	
	if (args.size() >= 1)
	{
		p = *(double *)args[0];
		delete (double *)args[0];
	}
	else
		p = -1.0;
	if (args.size() >= 2)
	{
		d = *(double *)args[1];
		delete (double *)args[1];
	}
	else
		d = -1.0;
	if (args.size() >= 3)
	{
		q = *(double *)args[2];
		delete (double *)args[2];
	}
	else
		q = -1.0;

	// ret = (void *)value;
	auto &budget = *(new Budget(p, d, q));
	ret = &budget;
	return ret;
}
void *NARSESEPARSER::string_raw(Parser *self, const Args &args)
{
	void *ret;
	auto &str = *(new std::string((char *)args[0]));
	ret = &str;
	return ret;
}
void *NARSESEPARSER::string(Parser *self, const Args &args)
{
	void *ret;
	auto &str = *(new std::string((char *)args[0]));
	ret = &str;
	return ret;
}
void *NARSESEPARSER::quality(Parser *self, const Args &args)
{
	void *ret;
	ret = new double(std::stod((char *)args[0]));
	return ret;
}
void *NARSESEPARSER::durability(Parser *self, const Args &args)
{
	void *ret;
	ret = new double(std::stod((char *)args[0]));
	return ret;
}
void *NARSESEPARSER::priority(Parser *self, const Args &args)
{
	void *ret;
	ret = new double(std::stod((char *)args[0]));
	return ret;
}
void *NARSESEPARSER::k_evidence(Parser *self, const Args &args)
{
	void *ret;
	ret = new double(std::stod((char *)args[0])); // e.g., "1"
	return ret;
}
void *NARSESEPARSER::confidence(Parser *self, const Args &args)
{
	void *ret;
	ret = new double(std::stod((char *)args[0])); // e.g., "0.90"
	return ret;
}
void *NARSESEPARSER::frequency(Parser *self, const Args &args)
{
	void *ret;
	ret = new double(std::stod((char *)args[0])); // e.g., "0.90"
	return ret;
}
void *NARSESEPARSER::integer(Parser *self, const Args &args)
{
	void *ret;
	ret = new double(std::stod((char *)args[0])); // e.g., 123
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
	regist("operation", operation);
	regist("interval", interval);
	regist("set", set);
	regist("negation", negation);
	regist("int_image", int_image);
	regist("ext_image", ext_image);
	regist("multi_infix", multi_infix);
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
