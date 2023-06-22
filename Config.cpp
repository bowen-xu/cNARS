#include "Config.h"

namespace CONFIG
{
    float priority = 0.8;
    float durability = 0.8;
    float quality = 0.5;

    unsigned int num_buckets = 100;
    unsigned int max_duration = 10000;
    float f =1.0;
    float c =0.9;
    float c_judgement =0.9;
    float c_goal =0.9;
    unsigned int k =1;
    float p_judgement =0.8;
    float d_judgement =0.5;
    float p_question =0.9;
    float d_question =0.9;
    float p_quest =0.9;
    float d_quest =0.9;
    float p_goal =0.9;
    float d_goal =0.9;

    float p_feedback = 0.9;
    float d_feedback = 0.5;

    float budget_thresh =0.01;

    unsigned int nlevels_task_link =10;
    unsigned int capacity_task_link =100;
    unsigned int nlevels_term_link =10;
    unsigned int capacity_term_link =100;
    unsigned int capacity_table =100;

    float complexity_unit = 1.0; // 1.0 - oo;

    float quality_min =0.3;
    unsigned int cycles_per_duration =5;
    unsigned int n_forget_durations =2;
    unsigned int cycles_forget = cycles_per_duration*n_forget_durations;

    unsigned int revision_max_occurence_distance = 10;

    float truth_epsilon = 0.01;
    float budget_epsilon = 0.0001;
    // float complexity_unit = 1.0;

    bool variable_repr_normalized = false;

    float rate_discount_c = 0.5;

    float rate_discount_p_internal_exp = 0.1;
    float rate_discount_d_internal_exp = 0.1;

    unsigned int temporal_duration  = 5;
    unsigned int n_sequence_attempts = 10;
    unsigned int n_op_condition_attempts = 10;
} // namespace CONFIG
