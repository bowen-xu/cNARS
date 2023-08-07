#include "../include/Truth.h"

using namespace TRUTH;

void TRUTH::pybind_truth(py::module &m)
{
    py::class_<TRUTH::Truth, TRUTH::pTruth>(m, "Truth")
    // .def(py::init([](){return Truth::create();}))
    .def(py::init([](double f, double c, double k){return Truth::create(f, c, k);}), py::arg("f"), py::arg("c"), py::arg("k")=1.0)
    .def_readwrite("f", &Truth::f)
    .def_readwrite("c", &Truth::c)
    .def_readwrite("k", &Truth::k)
    .def_property_readonly("e", &Truth::e)
    .def("__repr__", &Truth::__repr__)
    ;
}
