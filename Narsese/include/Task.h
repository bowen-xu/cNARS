#ifndef _TASK_H_
#define _TASK_H_

#include "./Budget.h"
#include "./Sentence.h"

namespace TASK
{
    using BUDGET::Budget;
    using BUDGET::pBudget;
    using SENTENCE::Judgement;
    using SENTENCE::pSentence;
    using SENTENCE::Sentence;
    class Task
    {
    public:
        pBudget budget;
        pSentence sentence;
        Task(pBudget _budget, pSentence _sentence) : budget(_budget), sentence(_sentence) {}
    };
} // namespace TAKS

#endif // _TAKS_H_