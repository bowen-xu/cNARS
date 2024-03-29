#ifndef _UNCERTAINTY_MAPPING_FUNCTIONS_H
#define _UNCERTAINTY_MAPPING_FUNCTIONS_H

#include "Narsese/include/Truth.h"
namespace UNCERTAINTY_MAPPING_FUNCTIONS
{
    using TRUTH::Truth;

    inline float fc_to_w_plus(float f, float c, float k) { return k * f * c / (1 - c); }
    inline float fc_to_w(float f, float c, float k) { return k * c / (1 - c); }
    inline float fc_to_w_minus(float f, float c, float k) { return k * (1 - f) * c / (1 - c); }
    inline float w_to_f(float w_plus, float w) { return w > 1e-8 ? w_plus / w : 0.0; }
    inline float w_to_c(float w, float k) { return w / (w + k); }

    // Truth truth_from_w(float w_plus, float w, float k=1.0);
    inline Truth truth_from_w(float w_plus, float w, float k = 1.0)
    {
        float f, c;
        if (w != 0)
        {
            f = w_to_f(w_plus, w);
            c = w_to_c(w, k);
        }
        else
        {
            f = 0.5;
            c = 0.0;
        }
        return Truth(f, c, k);
    }
    std::tuple<float, float> w_from_truth(Truth &truth);

    inline void w_from_truth(Truth &truth, float &o__w_plus, float &o__w_minus)
    {
        float &f = truth.f;
        float &c = truth.c;
        float &k = truth.k;
        o__w_plus = fc_to_w_plus(f, c, k);
        o__w_minus = fc_to_w_minus(f, c, k);
    }

} // namespace _UNCERTAINTY_MAPPING_FUNCTIONS_H

#endif // _UNCERTAINTY_MAPPING_FUNCTIONS_H