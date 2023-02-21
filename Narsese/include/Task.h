#ifndef _TASK_H_
#define _TASK_H_

#include "./Budget.h"
#include "./Sentence.h"

namespace TASK
{
    using BUDGET::Budget;
    using SENTENCE::Judgement;
    using SENTENCE::Sentence;
    class Task
    {
    public:
        Budget& budget;
        Sentence& sentence;
        Task(Budget &_budget, Sentence &_sentence) : budget(_budget), sentence(_sentence){}
    };
} // namespace TAKS

#endif // _TAKS_H_