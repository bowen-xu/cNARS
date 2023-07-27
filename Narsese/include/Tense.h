#ifndef _TENSE_H
#define _TENSE_H

#include <string>

namespace TENSE
{
    using std::string;

    enum PYBIND11_EXPORT Tense
    {
        Past = 0,    // :\:
        Present = 1, // :|:
        Future = 2,  // :/:
        Eternal = 3 // :-:
    };
    const string Repr[] = {string(":\\:"), string(":|:"), string(":/:"), string(":-:")};
} // namespace TENSE

#endif // _TENSE_H