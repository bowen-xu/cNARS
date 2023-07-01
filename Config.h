#ifndef _CONFIG_H
#define _CONFIG_H

#define _LIST_BOOST 0
#define _LIST_STD 1
#define SRC_LIST _LIST_BOOST //_LIST_STD

namespace CONFIG
{

    extern float priority; // = 0.8
    extern float durability; // = 0.8
    extern float quality; // = 0.5

    extern unsigned int num_buckets; // = 100
    extern unsigned int max_duration; // = 10000
    extern float f;// =1.0
    extern float c; //=0.9
    extern float c_judgement; //=0.9
    extern float c_goal; // =0.9
    extern float k; //=1
    extern float p_judgement; //=0.8
    extern float d_judgement; //=0.5
    extern float p_question; //=0.9
    extern float d_question; //=0.9
    extern float p_quest; //=0.9
    extern float d_quest; //=0.9
    extern float p_goal; //=0.9
    extern float d_goal; //=0.9
    
    extern float p_feedback; // = 0.9
    extern float d_feedback;// = 0.5

    extern float budget_thresh; //=0.01

    extern unsigned int nlevels_task_link; //=10
    extern unsigned int capacity_task_link; //=100
    extern unsigned int nlevels_term_link; //=10
    extern unsigned int capacity_term_link; //=100
    extern unsigned int capacity_table; //=100

    // extern float complexity_unit; //=1.0 # 1.0 - oo

    extern float quality_min; //=0.3
    extern unsigned int cycles_per_duration; //=5
    extern unsigned int n_forget_durations; //=2
    extern unsigned int cycles_forget; // = cycles_per_duration*n_forget_durations

    extern unsigned int revision_max_occurence_distance; //=10

    extern float truth_epsilon; // = 0.01
    extern float budget_epsilon; // = 0.0001
    extern float complexity_unit; // = 1.0
    

    extern bool variable_repr_normalized; // = False

    extern float rate_discount_c; // = 0.5

    extern float rate_discount_p_internal_exp; // = 0.1
    extern float rate_discount_d_internal_exp; // = 0.1

    extern unsigned int temporal_duration; // = 5
    extern unsigned int n_sequence_attempts; // = 10
    extern unsigned int n_op_condition_attempts; // = 10

    extern unsigned int maximum_evidential_base_length;

} // namespace CONFIG


#endif // _CONFIG_H