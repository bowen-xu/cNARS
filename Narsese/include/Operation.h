#ifndef _OPERATION_H
#define _OPERATION_H

#include "./Term.h"
#include "utils/hash.h"
#include <memory>

namespace OPERATION
{
    using TERM::Term;
    using TERM::TermType;
    using UTILS::Hash;

    class Operation;
    typedef std::shared_ptr<Operation> pOperation;

    class Operation : public Term
    {
    public:
        bool is_mental_operation : 1 = false;
        Operation(bool is_mental_operation = false) : Term(), is_mental_operation(is_mental_operation)
        {
            // this->hash_value = Hash{}(std::initializer_list<size_t>{(size_t)TermType::OPERATION, (size_t)this});
            this->is_operation = true;
        }
    };

} // namespace OPERATION

#endif // _OPERATION_H