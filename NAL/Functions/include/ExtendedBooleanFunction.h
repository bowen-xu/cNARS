#ifndef _EXTENDED_BOOLEAN_FUNCTIONS_H
#define _EXTENDED_BOOLEAN_FUNCTIONS_H
#include <iostream>
#include <algorithm>
#include <numeric>
#include <initializer_list>

namespace BOOLEAN_FUNCTIONS
{
    inline double And(double x1, double x2) { return x1 * x2; }

    inline double And(double x1, double x2, double x3) { return x1 * x2 * x3; }

    inline double And(double x1, double x2, double x3, double x4) { return x1 * x2 * x3 * x4; }

    inline double Or(double x1, double x2) { return 1 - (1 - x1) * (1 - x2); }

    inline double Or(double x1, double x2, double x3) { return 1 - (1 - x1) * (1 - x2) * (1 - x3); }

    inline double Or(double x1, double x2, double x3, double x4) { return 1 - (1 - x1) * (1 - x2) * (1 - x3) * (1 - x4); }

    inline double Or(std::initializer_list<double> x)
    {
        return 1.0 - std::accumulate(x.begin(), x.end(), 1.0, [](double acc, double xi)
                                     { return acc * (1.0 - xi); });
    }

} // namespace FUNCTIONS

#endif // _EXTENDED_BOOLEAN_FUNCTIONS_H