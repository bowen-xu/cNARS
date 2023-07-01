#ifndef _EVIDENCE_H
#define _EVIDENCE_H

#include "../utils/hash.h"
#include "Config.h"
#include "Global.h"
#include <algorithm>
#include <memory>
#include <set>

namespace EVIDENCE
{
    using std::set;
    using std::shared_ptr;
    using UTILS::Hash;

    class Base;
    typedef shared_ptr<Base> pBase;

    class Base // Evidential Base
    {
    public:
        shared_ptr<set<size_t>> _set;
        size_t _hash;
        bool _is_hashed = false;
        Base(shared_ptr<set<size_t>> evidence=nullptr) : _set(evidence) 
        {
            if (evidence == nullptr)
                this->_set = shared_ptr<set<size_t>>(new set<size_t>({GLOBAL::get_input_id()}));
        }
        Base(set<size_t> evidence) : _set(shared_ptr<set<size_t>>(new set<size_t>(evidence))) {}

        void extend(const Base &other)
        {
            auto base1 = Base(*this);
            auto &base2 = other;
            this->_set->clear();
            Base::interleave(*this, base1, base2);
        }

        static void interleave(Base &base, const Base &base1, const Base &base2)
        {
            auto base_length = std::min(base1.size() + base2.size(), (size_t)CONFIG::maximum_evidential_base_length);
            size_t i = 0;
            auto it1 = base1._set->begin();
            auto it2 = base2._set->begin();
            while (i < base_length)
            {
                if (it2 != base2._set->end())
                {
                    base._set->insert(*it2);
                    it2++;
                    i++;
                }
                if (it1 != base1._set->end())
                {
                    base._set->insert(*it1);
                    it1++;
                    i++;
                }
            }
        }

        static auto interleave(const Base &base1, const Base &base2)
        {
            auto base = pBase(new Base());
            Base::interleave(*base, base1, base2);
            return base;
        }

        auto add(size_t id_evidence)
        {
            this->_set->insert(id_evidence);
            this->_is_hashed = false;
            return this;
        }

        bool is_overlaped(Base &base)
        {
            std::set<int> intersection;
            auto &set1 = *(this->_set);
            auto &set2 = *(base._set);
            std::set_intersection(set1.begin(), set1.end(),
                                  set2.begin(), set2.end(),
                                  std::inserter(intersection, intersection.begin()));

            return !intersection.empty();
        }

        size_t size() const { return this->_set->size(); }

        size_t do_hashing()
        {
            this->_hash = Hash{}(*this->_set);
            this->_is_hashed = true;
            return this->_hash;
        }

        size_t __hash__()
        {
            return this->_is_hashed ? this->_hash : this->do_hashing();
        }
    };
} // namespace EVIDENCE

#endif // _EVIDENCE_H