#ifndef _COPULA_H
#define _COPULA_H

#include <pybind11/pybind11.h>
#include <string>

namespace COPULA
{
    namespace py = pybind11;
    using string = std::string;
    enum PYBIND11_EXPORT Copula
    {
        None = -1,
        Inheritance = 0,              // -->
        Similarity = 1,               // <->
        Instance = 2,                 // {--
        Property = 3,                 // --]
        InstanceProperty = 4,         // {-]
        Implication = 5,              // ==>
        PredictiveImplication = 6,    // =/>
        ConcurrentImplication = 7,    // =|>
        RetrospectiveImplication = 8, // =\>
        Equivalence = 9,              // <=>
        PredictiveEquivalence = 10,   // </>
        ConcurrentEquivalence = 11    // <|>
    };
    const Copula INHERITANCE = Copula::Inheritance;
    const Copula SIMILARITY = Copula::Similarity;
    const Copula INSTANCE = Copula::Instance;
    const Copula PROPERTY = Copula::Property;
    const Copula INSTANCEPROPERTY = Copula::InstanceProperty;
    const Copula IMPLICATION = Copula::Implication;
    const Copula PREDICTIVEIMPLICATION = Copula::PredictiveImplication;
    const Copula CONCURRENTIMPLICATION = Copula::ConcurrentImplication;
    const Copula RETROSPECTIVEIMPLICATION = Copula::RetrospectiveImplication;
    const Copula EQUIVALENCE = Copula::Equivalence;
    const Copula PREDICTIVEEQUIVALENCE = Copula::PredictiveEquivalence;
    const Copula CONCURRENTEQUIVALENCE = Copula::ConcurrentEquivalence;

    const string Repr[] = {string("-->"), string("<->"), string("{--"), string("--]"), string("{-]"), string("==>"), string("=/>"), string("=|>"), string("=\\>"), string("<=>"), string("</>"), string("<|>")};

    const bool _commutative[] = {false, true, false, false, false, false, false, false, false, true, false, true};
    const bool _higher_order[] = {false, false, false, false, false, true, true, true, true, true, true, true};
    const bool _temporal[] = {false, false, false, false, false, false, true, true, true, false, true, true};
    const Copula _symmetrize[] = {Similarity, Similarity, None, None, None, Equivalence, PredictiveEquivalence, ConcurrentEquivalence, None, Equivalence, PredictiveEquivalence, ConcurrentEquivalence};
    const Copula _reverse[] = {None, None, None, None, None, None, RetrospectiveImplication, ConcurrentImplication, PredictiveImplication, None, None, ConcurrentEquivalence};

    inline bool is_commutative(Copula copula) { return _commutative[copula]; }
    inline bool is_higher_order(Copula copula) { return _higher_order[copula]; }
    inline bool is_temporal(Copula copula) { return _temporal[copula]; }
    inline bool symmetrize(Copula copula) { return _symmetrize[copula]; }
    inline bool reverse(Copula copula) { return _reverse[copula]; }

    void pybind_copula(py::module &m);

} // namespace Copula

#endif // _COPULA_H