#ifndef _NARSESE_PARSER_H_
#define _NARSESE_PARSER_H_

#include "./Parser.h"

namespace NARSESEPARSER
{
    using PARSER::Args;
    using PARSER::Parser;
    class NarseseParser : public Parser
    {
    public:
        NarseseParser();
    };


    /*prototypes*/
	extern void* task(Args &args);
	extern void* judgement(Args &args);
	extern void* question(Args &args);
	extern void* goal(Args &args);
	extern void* quest(Args &args);
	extern void* statement(Args &args);
	extern void* statement_operation1(Args &args);
	extern void* statement_operation2(Args &args);
	extern void* inheritance(Args &args);
	extern void* similarity(Args &args);
	extern void* instance(Args &args);
	extern void* property(Args &args);
	extern void* instance_property(Args &args);
	extern void* implication(Args &args);
	extern void* predictive_implication(Args &args);
	extern void* concurrent_implication(Args &args);
	extern void* retrospective_implication(Args &args);
	extern void* equivalence(Args &args);
	extern void* predictive_equivalence(Args &args);
	extern void* concurrent_equivalence(Args &args);
	extern void* variable_term(Args &args);
	extern void* atom_term(Args &args);
	extern void* compound_term(Args &args);
	extern void* statement_term(Args &args);
	extern void* op(Args &args);
	extern void* interval(Args &args);
	extern void* set(Args &args);
	extern void* negation(Args &args);
	extern void* int_image(Args &args);
	extern void* ext_image(Args &args);
	extern void* multi_prefix_product(Args &args);
	extern void* multi_prefix(Args &args);
	extern void* single_prefix(Args &args);
	extern void* single_infix(Args &args);
	extern void* multi_prod_expr(Args &args);
	extern void* multi_disj_expr(Args &args);
	extern void* multi_conj_expr(Args &args);
	extern void* multi_sequential_expr(Args &args);
	extern void* multi_parallel_expr(Args &args);
	extern void* multi_intint_expr(Args &args);
	extern void* multi_extint_expr(Args &args);
	extern void* con_conjunction(Args &args);
	extern void* con_disjunction(Args &args);
	extern void* con_parallel_events(Args &args);
	extern void* con_sequential_events(Args &args);
	extern void* con_intensional_intersection(Args &args);
	extern void* con_extensional_intersection(Args &args);
	extern void* con_extensional_difference(Args &args);
	extern void* con_intensional_difference(Args &args);
	extern void* con_int_set(Args &args);
	extern void* con_ext_set(Args &args);
	extern void* con_negation(Args &args);
	extern void* con_int_image(Args &args);
	extern void* con_ext_image(Args &args);
	extern void* independent_var(Args &args);
	extern void* dependent_var(Args &args);
	extern void* query_var(Args &args);
	extern void* tense_time(Args &args);
	extern void* tense_future(Args &args);
	extern void* tense_present(Args &args);
	extern void* tense_past(Args &args);
	extern void* truth(Args &args);
	extern void* budget(Args &args);
	extern void* string_raw(Args &args);
	extern void* string(Args &args);
	extern void* quality(Args &args);
	extern void* durability(Args &args);
	extern void* priority(Args &args);
	extern void* k_evidence(Args &args);
	extern void* confidence(Args &args);
	extern void* frequency(Args &args);
	extern void* integer(Args &args);



} // namespace NARSESEPARSER


#endif // _NARSESE_PARSER_H_