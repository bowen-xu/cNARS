#include "../include/Budget.h"

namespace BUDGET
{
    double Budget::_priority_default = 0.9;
    double Budget::_durability_default = 0.9;
    double Budget::_quality_default = 0.5;

    void pybind_budget(py::module &m)
    {
        py::class_<Budget, pBudget>(m, "Budget")
            .def(py::init(&Budget::create), py::arg("p")=Budget::_priority_default, py::arg("d")=Budget::_durability_default, py::arg("q")=Budget::_quality_default)
            .def_readwrite("p", &Budget::priority)
            .def_readwrite("d", &Budget::durability)
            .def_readwrite("q", &Budget::quality)
            .def_static("quality_from_truth", [](TRUTH::pTruth t) { return Budget::quality_from_truth(*t); })
            .def("__repr__", [](Budget& self)
                 { return fmt::format("<Budget: ${:.2f};{:.2f};{:.2f}$>", self.priority, self.durability, self.quality); });
    }

} // namespace BUDGET
