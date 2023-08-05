#ifndef _TRUTH_H
#define _TRUTH_H

#include <memory>
#include <pybind11/pybind11.h>
#include "Config.h"
#include <fmt/core.h>

namespace TRUTH
{
    namespace py = pybind11;

    class Truth;
    typedef std::shared_ptr<Truth> pTruth;

    class PYBIND11_EXPORT Truth
    {
    public:
        float f;
        float c;
        float k;

        Truth(float f, float c, float k = 1.0) : f(f), c(c), k(k){};
        Truth(float k = 1.0) : f(CONFIG::f), c(CONFIG::c), k(k){};

        inline double e() const
        {
            return (c * (f - 0.5) + 0.5);
        }

        inline double w() const
        {
            return k * c / (1 - c);
        }

        inline double w_p() const
        {
            return k * f * c / (1 - c);
        }

        inline double w_m() const
        {
            return k * (1 - f) * c / (1 - c);
        }

        inline void set_w(double w_p, double w)
        {
            this->f = w > 0 ? w_p / w : 0.5;
            this->c = w / (w + k);
        }

        inline static pTruth create(float f, float c, float k = 1.0)
        {
            return pTruth(new Truth(f, c, k));
        }

        inline static pTruth create(float k = 1.0)
        {
            return pTruth(new Truth(k));
        }

        inline std::string __repr__()
        {
            return fmt::format("<Truth: %{:.2f}, {:.2f}% (k={})>", this->f, this->c, this->k);
        }
    };
    typedef Truth Desire;

    void pybind_truth(py::module &m);

} // namespace TRUTH

#endif //_TRUTH_H