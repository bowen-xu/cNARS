#ifndef _TASK_H_
#define _TASK_H_

#include "./Budget.h"
#include "./Sentence.h"
#include <memory>
#include <pybind11/pybind11.h>

namespace TASK
{
    namespace py = pybind11;
    
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

        auto &term() { return *sentence->term; }
    };

    class pTask : public std::shared_ptr<Task>
    {
    public:
        using std::shared_ptr<Task>::shared_ptr;

        auto term() { return (*this)->sentence->term; }
        auto sentence() { return (*this)->sentence; }

        std::string __repr__(void *interpreter) const;
    };

    void pybind_task(py::module &m);

} // namespace TAKS

#endif // _TAKS_H_