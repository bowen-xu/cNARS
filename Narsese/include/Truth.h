#ifndef _TRUTH_H
#define _TRUTH_H

#include <memory>


namespace TRUTH
{
    class Truth
    {
    public:
        float f;
        float c;
        float k;

        inline Truth(float f, float c, float k=1.0) : f(f), c(c), k(k) {};

        inline double e() const
        {
            return (c * (f - 0.5) + 0.5);
        }
    };
    typedef Truth Desire;

    typedef std::shared_ptr<Truth> pTruth;
} // namespace TRUTH

#endif //_TRUTH_H