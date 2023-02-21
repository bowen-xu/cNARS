#include "../include/Connector.h"

using namespace CONNECTOR;

namespace CONNECTOR
{
    const char *Repr[] = {"&&", "||", "*", "&|", "&/", "|", "&", "-", "~", "--", "[", "{", "\\", "/", "#"};
    
    bool _commutative[] = {true, true, false, true, false, true, true, false, false, false, true, true, false, false, false};
    bool _single_only[] = {false, false, false, false, false, false, false, false, false, true, false, false, false, false, false};
    bool _double_only[] = {false, false, false, false, false, false, false, true, true, false, false, false, false, false, false};
    bool _multiple_only[] = {true, true, true, true, true, true, true, true, true, false, false, false, true, true, false};
    bool _temporal[] = {false, false, false, true, true, false, false, false, false, false, false, false, false, false, false};

    // inline bool is_commutative(Connector connector) { return _commutative[connector]; }
    // inline bool is_single_only(Connector connector) { return _single_only[connector]; }
    // inline bool is_double_only(Connector connector) { return _double_only[connector]; }
    // inline bool is_multiple_only(Connector connector) { return _multiple_only[connector]; }
    // inline bool is_temporal(Connector connector) { return _temporal[connector]; }
    // inline bool check_valid(Connector connector, unsigned int len_terms)
    // {
    //     return (!is_single_only(connector) || len_terms == 1) && 
    //         (!is_double_only(connector) || len_terms == 2) && 
    //         (!is_multiple_only(connector) || len_terms > 1) && 
    //         (len_terms > 0);
    // }
} // namespace CONNECTOR




// @property
// def is_commutative(self):
//     return self in (
//         Connector.Conjunction, 
//         Connector.Disjunction, 
//         Connector.ParallelEvents,
//         Connector.IntensionalIntersection,
//         Connector.ExtensionalIntersection,
//         Connector.IntensionalSet,
//         Connector.ExtensionalSet
//     )
// @property
// def is_single_only(self):
//     return self in (
//         Connector.Negation,
//     )

// @property
// def is_double_only(self):
//     return self in (
//         Connector.ExtensionalDifference, 
//         Connector.IntensionalDifference
//     )

// @property
// def is_multiple_only(self):
//     return self in (
//         Connector.Conjunction, 
//         Connector.Disjunction, 
//         Connector.Product, 
//         Connector.ParallelEvents,
//         Connector.SequentialEvents,
//         Connector.IntensionalIntersection,
//         Connector.ExtensionalIntersection,
//         Connector.ExtensionalDifference,
//         Connector.IntensionalDifference,
//         Connector.IntensionalImage,
//         Connector.ExtensionalImage
//     )

// @property
// def is_temporal(self):
//     return self in (Connector.SequentialEvents, Connector.ParallelEvents)

// def check_valid(self, len_terms: int):
//     if self.is_single_only: return len_terms == 1
//     elif self.is_double_only: return len_terms == 2
//     elif self.is_multiple_only: return len_terms > 1
//     else: return len_terms > 0
