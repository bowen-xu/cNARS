#ifndef _TRUTH_FUNCTIONS_H
#define _TRUTH_FUNCTIONS_H

#include "Narsese/include/Truth.h"
#include "./UncertaintyMappingFunctions.h"
#include "./ExtendedBooleanFunction.h"

namespace TRUTH_FUNCTIONS
{
    using TRUTH::pTruth;
    using namespace UNCERTAINTY_MAPPING_FUNCTIONS;
    using namespace BOOLEAN_FUNCTIONS;

    inline auto truth_revision(pTruth truth1, pTruth truth2)
    {
        auto w = truth1->w() + truth2->w();
        auto w_p = truth1->w_p() + truth2->w_p();
        auto k = truth1->k;
        auto f = w_to_f(w_p, w);
        auto c = w_to_c(w, k);
        truth1->f = f;
        truth1->c = c;
    }

    inline auto truth_deduction(pTruth truth1, pTruth truth2)
    {
        auto truth = Truth::create(truth1->k);
        auto f1 = truth1->f;
        auto f2 = truth2->f;
        auto c1 = truth1->c;
        auto c2 = truth2->c;
        truth->f = And(f1, f2);
        truth->c = And(f1, f2, c1, c2);
        return truth;
    }

    inline auto truth_induction(pTruth truth1, pTruth truth2)
    {
        auto truth = Truth::create();
        auto w_p = And(truth1->f, truth2->f, truth1->c, truth2->c);
        auto w = And(truth2->f, truth1->c, truth2->c);
        truth->set_w(w_p, w);
        return truth;
    }

    inline auto truth_comparison(pTruth truth1, pTruth truth2)
    {
        auto truth = Truth::create();
        auto w_p = And(truth1->f, truth2->f, truth1->c, truth2->c);
        auto w = And(Or(truth1->f, truth2->f), truth1->c, truth2->c);
        truth->set_w(w_p, w);
        return truth;
    }

}

#endif // _TRUTH_VALUE_FUNCTIONS_H