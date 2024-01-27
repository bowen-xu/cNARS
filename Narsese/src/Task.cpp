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

namespace TASK
{
    void pybind_task(py::module &m)
    {
        py::class_<TASK::pTask>(m, "Task")
        .def_property_readonly("sentence", &TASK::pTask::sentence)
        .def_property_readonly("term", &TASK::pTask::term)
        // .def("__repr__", &TASK::pTask::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);
        .def("__repr__", [](const pTask &self, void* interpreter=nullptr){
                if (interpreter == nullptr)
                    interpreter = (void *)&INTERPRETER::interpreter;
                return self.__repr__(interpreter);
            });
    }

}
