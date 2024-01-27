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
        py::enum_<PUNCTUATION::Punctuation>(m, "Punctuation")
            .value("Judgement", PUNCTUATION::Punctuation::Judgement, ".")
            .value("Question", PUNCTUATION::Punctuation::Question, "?")
            .value("Goal", PUNCTUATION::Punctuation::Goal, "!")
            .value("Quest", PUNCTUATION::Punctuation::Quest, "@")
            ;
        py::class_<Stamp, pStamp>(m, "Stamp")
            // .def(py::init(
            //     [](bool eternal, long time)
            //     {
            //         return Stamp::create(eternal, time);
            //     }), py::arg("eternal"), py::arg("time"))
        ;
        
        py::class_<pSentence>(m, "Sentence")
            .def(py::init(
                [](TERM::pTerm term, PUNCTUATION::Punctuation _punct, pTruth _truth, pStamp _stamp)
                {
                    return SENTENCE::Sentence::create(term, _punct, _truth, _stamp);
                }), py::arg("term"), py::arg("punct"), py::arg("truth"), py::arg("stamp"))
            // .def("__repr__", &pSentence::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);
            .def("__repr__", [](const pSentence &self, void* interpreter=nullptr){
                if (interpreter == nullptr)
                    interpreter = (void *)&INTERPRETER::interpreter;
                return self.__repr__(interpreter);
            });
    }
}