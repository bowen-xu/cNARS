#ifndef _INTERVAL_H
#define _INTERVAL_H

#include "./Term.h"
#include "utils/hash.h"
#include <memory>
#include <functional>
#include <initializer_list>


namespace INTERVAL
{
    using UTILS::Hash;
    using TERM::Term;
    using TERM::TermType;

    class Interval;
    typedef std::shared_ptr<Interval> pInterval;

    class Interval : public Term
    {
    public:
        signed int interval;
        Interval(signed int interval) : interval(interval)
        {
            this->Term::is_interval = true;
            this->hash_value = Hash{}(std::initializer_list<signed int>{TermType::INTERVAL, this->interval});
        }

        operator signed int() const
        {
            return this->interval;
        }

        Interval operator+(const Interval &other) const
        {
            return Interval(this->interval + other.interval);
        }

        Interval &operator+=(const Interval &other)
        {
            interval += other.interval;
            return *this;
        }
    };
    // class Interval(Term):
    //     is_interval: bool = True
    //     def __init__(self, interval, do_hashing=False, word_sorted=None, is_input=False) -> None:
    //         super().__init__("+"+str(interval), do_hashing=do_hashing, word_sorted=word_sorted, is_input=is_input)
    //         self.interval = int(interval)

    //     def __repr__(self) -> str:
    //         return f'<Interval: {str(self)}>'

    //     def __int__(self) -> int:
    //         return self.interval

    //     def __add__(self, o: Type['Interval']):
    //         return Interval(int(self)+int(o))
} // namespace INTERVAL

#endif // _INTERVAL_H