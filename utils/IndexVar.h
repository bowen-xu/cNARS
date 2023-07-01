#ifndef _INDEX_VAR_H
#define _INDEX_VAR_H

#include "./hash.h"
#include <functional>
#include <memory>
#include <vector>

namespace INDEXVAR
{
    class IndexVar;

    using std::vector;
    typedef std::shared_ptr<int> pInt;
    typedef std::shared_ptr<IndexVar> pIndexVar;
    using UTILS::Hash;

    class IndexVar
    {
        /*
        Examples:
        (&&, <$1-->A>, <$2-->B>, <$1-->C>)
        positions = [[0, 2], [1]]
        positions_unfolded = [[0, 2], [1]]
        variables = [0, 1, 0]

        (&&, <<$1-->A>==><$2-->B>>, <$2-->C>, <$3-->D>)
        positions = [[(0, 0)], [(0, 1), 1], [2]]
        positions_unfolded = [[0], [1, 2], [3]]
        variables = [[0, 1], 1, 2]
        variables_unfolded = [0, 1, 1, 2]
        */
    public:
        std::shared_ptr<vector<int>> _indices_normalized = nullptr;
        vector<vector<int>> positions;
        vector<pInt> indices;

        unsigned int _hash_value = 0;

        std::weak_ptr<IndexVar> predecessor;
        // IndexVar *predecessor;
        vector<pIndexVar> successors;
        bool _is_built = false;

        inline IndexVar() {}

        inline static pIndexVar create()
        {
            return pIndexVar(new IndexVar());
        }

        std::shared_ptr<vector<int>> normalize();
        static void connect(pIndexVar father, pIndexVar successor, bool generate_pos = false);
        void build(bool rebuild = false);
        pInt add(int idx, const std::vector<int> &position);
        void remove(const std::vector<int> &position);

        void rebuild()
        {
            this->build(true);
        }

        const std::shared_ptr<std::vector<int>> &indices_normalized()
        {
            if (this->_indices_normalized == nullptr)
            {
                this->_indices_normalized = normalize();
            }

            return this->_indices_normalized;
        }

        size_t do_hashing()
        {
            auto __indices_normalized = indices_normalized();

            this->_hash_value = Hash{}(*__indices_normalized);
            return this->_hash_value;
        }

        size_t __hash__()
        {
            return this->_hash_value != 0 ? this->_hash_value : this->do_hashing();
        }

        bool operator==(IndexVar *other)
        {
            return (this->__hash__() == other->__hash__());
        }
    };
} // namespace INDEXVAR

#endif //_INDEX_VAR_H