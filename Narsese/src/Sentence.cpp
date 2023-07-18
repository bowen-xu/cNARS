#include "../include/Sentence.h"
#include "Interpreter/include/Interpreter.hpp"

using namespace SENTENCE;

std::string pSentence::__repr__(void *interpreter) const
{
    if (interpreter == nullptr)
        interpreter = (void *)&(INTERPRETER::interpreter);
    auto &_interpreter = *((INTERPRETER::Interpreter *)interpreter);
    auto str = _interpreter.interpret(**this);
    return fmt::format("<Sentence: {}>", str);
}
namespace SENTENCE
{
    void pybind_sentence(py::module &m)
    {
        py::class_<pSentence>(m, "Sentence")
            .def("__repr__", &pSentence::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);
    }
}