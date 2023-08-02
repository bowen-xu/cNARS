#include "NAL/Functions/include/UncertaintyMappingFunctions.h"
#include <tuple>

using namespace UNCERTAINTY_MAPPING_FUNCTIONS;
namespace UMF=UNCERTAINTY_MAPPING_FUNCTIONS;

using std::tuple;

Truth UMF::truth_from_w(float w_plus, float w, float k)
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

tuple<float, float> UMF::w_from_truth(Truth &truth)
{
    float w_plus, w_minus;
    w_from_truth(truth, w_plus, w_minus);
    return {w_plus, w_minus};
}
