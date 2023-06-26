#ifndef _HASH_H
#define _HASH_H

#include <functional>
#include <iostream>
#include <string>
#include <vector>

namespace UTILS
{
    class Hash
    {
    private:
        std::hash<std::string> hash_str;

    public:
        std::size_t operator()(const std::string &str) const
        {
            return hash_str(str);
        }

        std::size_t operator()(const std::vector<int> &vec) const
        {
            std::size_t hash = 0;
            for (const auto &elem : vec)
            {
                hash_combine(hash, elem);
            }
            return hash;
        }

    private:
        template <typename T>
        void hash_combine(std::size_t &seed, const T &value) const
        {
            seed ^= std::hash<T>{}(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
    };

} // namespace UTILS

#endif // _HASH_H