#ifndef _BUDGET_H
#define _BUDGET_H

#include <memory>
#include <algorithm>
#include "Truth.h"
#include <pybind11/pybind11.h>

namespace BUDGET
{
    namespace py=pybind11;

    class Budget;
    typedef std::shared_ptr<Budget> pBudget;

    class Budget
    {
    public:
        static double _priority_default;
        static double _durability_default;
        static double _quality_default;

    public:
        double priority;
        double durability;
        float quality;

        Budget(float priority = _priority_default, float durability = _durability_default, float quality = _quality_default) : priority(priority), durability(durability), quality(quality){};

        static auto quality_from_truth(const TRUTH::Truth &t)
        {
            auto e = t.e();
            return std::max(e, (1 - e) * 0.75);
        }

        static pBudget create(float priority = _priority_default, float durability = _durability_default, float quality = _quality_default)
        {
            return pBudget(new Budget(priority, durability, quality));
        }
    };

    void pybind_budget(py::module &m);
} // namespace BUDGET

#endif // _BUDGET_H