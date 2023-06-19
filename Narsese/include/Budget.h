#ifndef _BUDGET_H
#define _BUDGET_H

#include <memory>


namespace BUDGET
{
    class Budget
    {
    private:
        static float _priority_default;
        static float _durability_default;
        static float _quality_default;

    public:
        float priority;
        float durability;
        float quality;

        Budget(float priority=_priority_default, float durability=_durability_default, float quality=_quality_default) : priority(priority), durability(durability), quality(quality) {};
    };

    typedef std::shared_ptr<Budget> pBudget;
} // namespace BUDGET


#endif // _BUDGET_H