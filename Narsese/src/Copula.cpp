#include "../include/Copula.h"
#include <string>

#include <pybind11/pybind11.h>

namespace COPULA
{

    // inline bool is_commutative(Copula copula) { return _commutative[copula]; }
    // inline bool is_higher_order(Copula copula) { return _higher_order[copula]; }
    // inline bool is_temporal(Copula copula) { return _temporal[copula]; }
    // inline bool symmetrize(Copula copula) { return _symmetrize[copula]; }
    // inline bool reverse(Copula copula) { return _reverse[copula]; }

    // const auto INHERITANCE = Copula::Inheritance;

    void pybind_copula(py::module& m)
    {
        py::enum_<COPULA::Copula>(m, "Copula")
            .value("Inheritance", COPULA::Copula::Inheritance, "-->")
            .value("Similarity", COPULA::Copula::Similarity, "<->")
            .value("Instance", COPULA::Copula::Instance, "{--")
            .value("Property", COPULA::Copula::Property, "--]")
            .value("InstanceProperty", COPULA::Copula::InstanceProperty, "{-]")
            .value("Implication", COPULA::Copula::Implication, "==>")
            .value("PredictiveImplication", COPULA::Copula::PredictiveImplication, "=/>")
            .value("ConcurrentImplication", COPULA::Copula::ConcurrentImplication, "=|>")
            .value("RetrospectiveImplication", COPULA::Copula::RetrospectiveImplication, "=\\>")
            .value("Equivalence", COPULA::Copula::Equivalence, "<=>")
            .value("PredictiveEquivalence", COPULA::Copula::PredictiveEquivalence, "</>")
            .value("ConcurrentEquivalence", COPULA::Copula::ConcurrentEquivalence, "<|>");
    }

} // namespace COPULA
