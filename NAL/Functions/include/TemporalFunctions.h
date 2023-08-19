#ifndef _TEMPORAL_FUNCTIONS_H
#define _TEMPORAL_FUNCTIONS_H

#include "Narsese/include/Truth.h"

namespace TEMPORAL_FUNCTIONS
{
    using TRUTH::pTruth;
    using TRUTH::Truth;

    inline auto project(pTruth truth, int64_t t_source, int64_t t_current, int64_t t_target, size_t decay_duration = 1000)
    {
        auto d = (abs(t_source - t_current) + abs(t_target - t_current)) + decay_duration;
        auto k_c = d > 0 ? abs(t_source - t_target) / d : 0;
        auto c_new = (1 - k_c) * truth->c;
        return Truth::create(truth->f, c_new, truth->k);
    }

} // namespace TEMPORAL_FUNCTIONS

#endif //_TEMPORAL_FUNCTIONS_H