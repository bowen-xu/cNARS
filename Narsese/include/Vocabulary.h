#ifndef _VOCABULARY_H
#define _VOCABULARY_H

#include <unordered_map>
#include <string>
#include "../utils/hash.h"

namespace VOCABULARY
{
    using std::string;
    using std::unordered_map;
    using UTILS::hash_str;

    unordered_map<unsigned int, string> vocabulary{
        {hash_str(string("SELF")), string("SELF")}
    };

} // namespace VOCABULARY


# endif // _VOCABULARY_H