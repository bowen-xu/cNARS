#include "IndexVar.h"
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::unordered_map;
using std::unordered_set;
using std::vector;

using namespace INDEXVAR;

/* Helper Functions */

std::shared_ptr<vector<int>> _normalize(const vector<int> &variables)
{
    std::unordered_set<int> p1(variables.begin(), variables.end());
    vector<int> p2(p1.begin(), p1.end());

    std::unordered_map<int, int> mapping;
    for (std::size_t i = 0; i < p2.size(); ++i)
    {
        mapping[p2[i]] = i;
    }

    auto result = std::make_shared<vector<int>>();
    for (const auto &p : variables)
    {
        result->push_back(mapping[p]);
    }

    return result;
}

std::shared_ptr<vector<int>> _normalize(const vector<pInt> &indices)
{
    std::vector<int> variables;
    for (const auto &var : indices)
    {
        variables.push_back(*var);
    }

    return _normalize(variables);
}

/* IndexVar */

std::shared_ptr<vector<int>> IndexVar::normalize()
{
    /*
    normalize the index, so that the index is unique in terms of one statement which has variable(s).
    */
    if (this->_indices_normalized == nullptr)
    {
        this->_indices_normalized = _normalize(this->indices);
    }

    return this->_indices_normalized;
}

void IndexVar::connect(pIndexVar father, pIndexVar son, bool generate_pos)
{
    father->successors.push_back(son);
    son->predecessor = father;

    if (!generate_pos)
        return;

    int bias_pos = father->successors.size() - 1;
    auto &indices = son->indices;
    std::vector<std::vector<int>> positions;
    for (const auto &pos : son->positions)
    {
        std::vector<int> position = {bias_pos};
        position.insert(position.end(), pos.begin(), pos.end());
        positions.push_back(position);
    }
    indices.insert(indices.end(), son->indices.begin(), son->indices.end());
    positions.insert(positions.end(), son->positions.begin(), son->positions.end());
    father->indices.insert(father->indices.end(), indices.begin(), indices.end());
    father->positions.insert(father->positions.end(), positions.begin(), positions.end());
}

void IndexVar::build(bool rebuild)
{
    if (!rebuild && this->_is_built)
        return;

    if (successors.size() > 0)
    {
        indices.clear();
        positions.clear();
    }

    for (int bias_pos = 0; bias_pos < successors.size(); bias_pos++)
    {
        successors[bias_pos]->build(rebuild);
        auto &_indices = successors[bias_pos]->indices;
        std::vector<std::vector<int>> positions;
        for (const auto &pos : successors[bias_pos]->positions)
        {
            std::vector<int> position = {(int)(bias_pos)};
            position.insert(position.end(), pos.begin(), pos.end());
            positions.push_back(position);
        }
        this->indices.insert(this->indices.end(), _indices.begin(), _indices.end());
        this->positions.insert(this->positions.end(), positions.begin(), positions.end());
    }

    this->_is_built = true;
}

pInt IndexVar::add(int idx, const std::vector<int> &position)
{
    auto iv = pInt(new int(idx));

    if (position.empty())
    {
        positions.clear();
        indices.clear();
    }

    IndexVar *idxvar = this;
    for (int pos : position)
    {
        idxvar = idxvar->successors[pos].get();
    }
    idxvar->positions.push_back(std::vector<int>());
    idxvar->indices.push_back(iv);

    return iv;
}

void IndexVar::remove(const std::vector<int> &position)
{
    IndexVar *index = this;
    for (int pos : position)
    {
        index = index->successors[pos].get();
    }
    index->indices.clear();
    index->positions.clear();
}