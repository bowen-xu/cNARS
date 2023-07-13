#include "../include/Task.h"
#include "Interpreter/include/Interpreter.hpp"
#include <fmt/core.h>

using namespace TASK;

std::string pTask::__repr__(void *interpreter = nullptr) const
{
    if (interpreter == nullptr)
        interpreter = (void *)&(INTERPRETER::interpreter);
    auto &_interpreter = *((INTERPRETER::Interpreter *)interpreter);
    auto str = _interpreter.interpret(**this);
    return fmt::format("<Task: {}>", str);
}