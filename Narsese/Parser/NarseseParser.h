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
	extern void* task(const Args &args);
	extern void* judgement(const Args &args);
	extern void* question(const Args &args);
	extern void* goal(const Args &args);
	extern void* quest(const Args &args);
	extern void* statement(const Args &args);
	extern void* statement_operation1(const Args &args);
	extern void* statement_operation2(const Args &args);
	extern void* inheritance(const Args &args);
	extern void* similarity(const Args &args);
	extern void* instance(const Args &args);
	extern void* property(const Args &args);
	extern void* instance_property(const Args &args);
	extern void* implication(const Args &args);
	extern void* predictive_implication(const Args &args);
	extern void* concurrent_implication(const Args &args);
	extern void* retrospective_implication(const Args &args);
	extern void* equivalence(const Args &args);
	extern void* predictive_equivalence(const Args &args);
	extern void* concurrent_equivalence(const Args &args);
	extern void* variable_term(const Args &args);
	extern void* atom_term(const Args &args);
	extern void* compound_term(const Args &args);
	extern void* statement_term(const Args &args);
	extern void* op(const Args &args);
	extern void* interval(const Args &args);
	extern void* set(const Args &args);
	extern void* negation(const Args &args);
	extern void* int_image(const Args &args);
	extern void* ext_image(const Args &args);
	extern void* multi_prefix_product(const Args &args);
	extern void* multi_prefix(const Args &args);
	extern void* single_prefix(const Args &args);
	extern void* single_infix(const Args &args);
	extern void* multi_prod_expr(const Args &args);
	extern void* multi_disj_expr(const Args &args);
	extern void* multi_conj_expr(const Args &args);
	extern void* multi_sequential_expr(const Args &args);
	extern void* multi_parallel_expr(const Args &args);
	extern void* multi_intint_expr(const Args &args);
	extern void* multi_extint_expr(const Args &args);
	extern void* con_conjunction(const Args &args);
	extern void* con_disjunction(const Args &args);
	extern void* con_parallel_events(const Args &args);
	extern void* con_sequential_events(const Args &args);
	extern void* con_intensional_intersection(const Args &args);
	extern void* con_extensional_intersection(const Args &args);
	extern void* con_extensional_difference(const Args &args);
	extern void* con_intensional_difference(const Args &args);
	extern void* con_int_set(const Args &args);
	extern void* con_ext_set(const Args &args);
	extern void* con_negation(const Args &args);
	extern void* con_int_image(const Args &args);
	extern void* con_ext_image(const Args &args);
	extern void* con_product(const Args &args);
	extern void* independent_var(const Args &args);
	extern void* dependent_var(const Args &args);
	extern void* query_var(const Args &args);
	extern void* tense_time(const Args &args);
	extern void* tense_future(const Args &args);
	extern void* tense_present(const Args &args);
	extern void* tense_past(const Args &args);
	extern void* truth(const Args &args);
	extern void* budget(const Args &args);
	extern void* string_raw(const Args &args);
	extern void* string(const Args &args);
	extern void* quality(const Args &args);
	extern void* durability(const Args &args);
	extern void* priority(const Args &args);
	extern void* k_evidence(const Args &args);
	extern void* confidence(const Args &args);
	extern void* frequency(const Args &args);
	extern void* integer(const Args &args);



} // namespace NARSESEPARSER


#endif // _NARSESE_PARSER_H_