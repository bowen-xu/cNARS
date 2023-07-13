#ifndef _NARSESE_PARSER_H_
#define _NARSESE_PARSER_H_

#include "./Parser.h"

namespace NARSESEPARSER
{
	using PARSER::Args;
	using PARSER::Parser;
	class NarseseParser : protected Parser
	{
	public:
		NarseseParser();
		TASK::pTask parse_task(std::string &input)
		{
			names_ivar.clear();
			names_dvar.clear();
			names_qvar.clear();
			TASK::Task *task = ((TASK::Task *)this->parse_string(input));
			return TASK::pTask(task);
		}
		TASK::pTask parse_task(const char *input)
		{
			auto str = std::string(input);
			return parse_task(str);
		}
	};

	static auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);

	/*prototypes*/
	extern void *task(Parser *self, const Args &args);
	extern void *judgement(Parser *self, const Args &args);
	extern void *question(Parser *self, const Args &args);
	extern void *goal(Parser *self, const Args &args);
	extern void *quest(Parser *self, const Args &args);
	extern void *statement(Parser *self, const Args &args);
	extern void *statement_operation1(Parser *self, const Args &args);
	extern void *statement_operation2(Parser *self, const Args &args);
	extern void *inheritance(Parser *self, const Args &args);
	extern void *similarity(Parser *self, const Args &args);
	extern void *instance(Parser *self, const Args &args);
	extern void *property(Parser *self, const Args &args);
	extern void *instance_property(Parser *self, const Args &args);
	extern void *implication(Parser *self, const Args &args);
	extern void *predictive_implication(Parser *self, const Args &args);
	extern void *concurrent_implication(Parser *self, const Args &args);
	extern void *retrospective_implication(Parser *self, const Args &args);
	extern void *equivalence(Parser *self, const Args &args);
	extern void *predictive_equivalence(Parser *self, const Args &args);
	extern void *concurrent_equivalence(Parser *self, const Args &args);
	extern void *variable_term(Parser *self, const Args &args);
	extern void *atom_term(Parser *self, const Args &args);
	extern void *compound_term(Parser *self, const Args &args);
	extern void *statement_term(Parser *self, const Args &args);
	extern void *operation(Parser *self, const Args &args);
	extern void *interval(Parser *self, const Args &args);
	extern void *set(Parser *self, const Args &args);
	extern void *negation(Parser *self, const Args &args);
	extern void *int_image(Parser *self, const Args &args);
	extern void *ext_image(Parser *self, const Args &args);
	extern void *multi_infix(Parser *self, const Args &args);
	extern void *multi_prefix_product(Parser *self, const Args &args);
	extern void *multi_prefix(Parser *self, const Args &args);
	extern void *single_prefix(Parser *self, const Args &args);
	extern void *single_infix(Parser *self, const Args &args);
	extern void *multi_prod_expr(Parser *self, const Args &args);
	extern void *multi_disj_expr(Parser *self, const Args &args);
	extern void *multi_conj_expr(Parser *self, const Args &args);
	extern void *multi_sequential_expr(Parser *self, const Args &args);
	extern void *multi_parallel_expr(Parser *self, const Args &args);
	extern void *multi_intint_expr(Parser *self, const Args &args);
	extern void *multi_extint_expr(Parser *self, const Args &args);
	extern void *con_conjunction(Parser *self, const Args &args);
	extern void *con_disjunction(Parser *self, const Args &args);
	extern void *con_parallel_events(Parser *self, const Args &args);
	extern void *con_sequential_events(Parser *self, const Args &args);
	extern void *con_intensional_intersection(Parser *self, const Args &args);
	extern void *con_extensional_intersection(Parser *self, const Args &args);
	extern void *con_extensional_difference(Parser *self, const Args &args);
	extern void *con_intensional_difference(Parser *self, const Args &args);
	extern void *con_int_set(Parser *self, const Args &args);
	extern void *con_ext_set(Parser *self, const Args &args);
	extern void *con_negation(Parser *self, const Args &args);
	extern void *con_int_image(Parser *self, const Args &args);
	extern void *con_ext_image(Parser *self, const Args &args);
	extern void *con_product(Parser *self, const Args &args);
	extern void *independent_var(Parser *self, const Args &args);
	extern void *dependent_var(Parser *self, const Args &args);
	extern void *query_var(Parser *self, const Args &args);
	extern void *tense_time(Parser *self, const Args &args);
	extern void *tense_future(Parser *self, const Args &args);
	extern void *tense_present(Parser *self, const Args &args);
	extern void *tense_past(Parser *self, const Args &args);
	extern void *truth(Parser *self, const Args &args);
	extern void *budget(Parser *self, const Args &args);
	extern void *string_raw(Parser *self, const Args &args);
	extern void *string(Parser *self, const Args &args);
	extern void *quality(Parser *self, const Args &args);
	extern void *durability(Parser *self, const Args &args);
	extern void *priority(Parser *self, const Args &args);
	extern void *k_evidence(Parser *self, const Args &args);
	extern void *confidence(Parser *self, const Args &args);
	extern void *frequency(Parser *self, const Args &args);
	extern void *integer(Parser *self, const Args &args);

} // namespace NARSESEPARSER

#endif // _NARSESE_PARSER_H_