#include "NAL/Functions/include/UncertaintyMappingFunctions.h"
#include <tuple>

using namespace UNCERTAINTY_MAPPING_FUNCTIONS;
namespace UMF=UNCERTAINTY_MAPPING_FUNCTIONS;

using std::tuple;

tuple<float, float> UMF::w_from_truth(Truth &truth)
{
    float w_plus, w_minus;
    w_from_truth(truth, w_plus, w_minus);
    return {w_plus, w_minus};
}
