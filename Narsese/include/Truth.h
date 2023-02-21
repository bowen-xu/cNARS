#ifndef _TRUTH_H
#define _TRUTH_H

namespace TRUTH
{
    class Truth
    {
    public:
        float f;
        float c;
        float k;

        inline Truth(float f, float c, float k=1.0) : f(f), c(c), k(k) {};
        float e();
    };
    typedef Truth Desire;
} // namespace TRUTH

#endif //_TRUTH_H