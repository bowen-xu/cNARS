#ifndef _CONNECTOR_H
#define _CONNECTOR_H

#include <string>

namespace CONNECTOR
{
    using std::string;
    enum Connector
    {
        None = -1,
        Conjunction = 0,                // "&&"
        Disjunction = 1,                // "||"
        Product = 2,                    // "*"
        ParallelEvents = 3,             // "&|"
        SequentialEvents = 4,           // "&/"
        IntensionalIntersection = 5,    // "|"
        ExtensionalIntersection = 6,    // "&"
        ExtensionalDifference = 7,      // "-"
        IntensionalDifference = 8,      // "~"
        Negation = 9,                   // "--"
        IntensionalSet = 10,            // "["
        ExtensionalSet = 11,            // "{"
        IntensionalImage = 12,          // "\\"
        ExtensionalImage = 13,          // "/"
        List =14                        // "#"
    };
    const Connector CONJUNCTION = Connector::Conjunction;
    const Connector DISJUNCTION = Connector::Disjunction;
    const Connector PRODUCT = Connector::Product;
    const Connector PARALLEL_EVENTS = Connector::ParallelEvents;
    const Connector SEQUENTIAL_EVENTS = Connector::SequentialEvents;
    const Connector INTENSIONAL_INTERSECTION = Connector::IntensionalIntersection;
    const Connector EXTENSIONAL_INTERSECTION = Connector::ExtensionalIntersection;
    const Connector EXTENSIONAL_DIFFERENCE = Connector::ExtensionalDifference;
    const Connector INTENSIONAL_DIFFERENCE = Connector::IntensionalDifference;
    const Connector NEGATION = Connector::Negation;
    const Connector INTENSIONAL_SET = Connector::IntensionalSet;
    const Connector EXTENSIONAL_SET = Connector::ExtensionalSet;
    const Connector INTENSIONAL_IMAGE = Connector::IntensionalImage;
    const Connector EXTENSIONAL_IMAGE = Connector::ExtensionalImage;
    const Connector LIST = Connector::List;

    const string Repr[] = {string("&&"), string("||"), string("*"), string("&|"), string("&/"), string("|"), string("&"), string("-"), string("~"), string("--"), string("["), string("{"), string("\\"), string("/"), string("#")};
    // extern const char *Repr[];
    // const char *Repr[] = {"&&", "||", "*", "&|", "&/", "|", "&", "-", "~", "--", "[", "{", "\\", "/", "#"};

    const bool _commutative[] = {true, true, false, true, false, true, true, false, false, false, true, true, false, false, false};
    const bool _single_only[] = {false, false, false, false, false, false, false, false, false, true, false, false, false, false, false};
    const bool _double_only[] = {false, false, false, false, false, false, false, true, true, false, false, false, false, false, false};
    const bool _multiple_only[] = {true, true, true, true, true, true, true, true, true, false, false, false, true, true, false};
    const bool _temporal[] = {false, false, false, true, true, false, false, false, false, false, false, false, false, false, false};

    // extern inline bool is_commutative(Connector connector);
    // extern inline bool is_single_only(Connector connector);
    // extern inline bool is_double_only(Connector connector);
    // extern inline bool is_multiple_only(Connector connector);
    // extern inline bool is_temporal(Connector connector);
    // extern inline bool check_valid(Connector connector, unsigned int len_terms);
    // static inline bool is_commutative(Connector connector) { return _commutative[connector]; }
    // static inline bool is_single_only(Connector connector) { return _single_only[connector]; }
    // static inline bool is_double_only(Connector connector) { return _double_only[connector]; }
    // static inline bool is_multiple_only(Connector connector) { return _multiple_only[connector]; }
    // static inline bool is_temporal(Connector connector) { return _temporal[connector]; }
    // static inline bool check_valid(Connector connector, unsigned int len_terms)
    // {
    //     return (!is_single_only(connector) || len_terms == 1) && 
    //         (!is_double_only(connector) || len_terms == 2) && 
    //         (!is_multiple_only(connector) || len_terms > 1) && 
    //         (len_terms > 0);
    // }
    inline bool is_commutative(Connector connector) { return _commutative[connector]; }
    inline bool is_single_only(Connector connector) { return _single_only[connector]; }
    inline bool is_double_only(Connector connector) { return _double_only[connector]; }
    inline bool is_multiple_only(Connector connector) { return _multiple_only[connector]; }
    inline bool is_temporal(Connector connector) { return _temporal[connector]; }
    inline bool check_valid(Connector connector, unsigned int len_terms)
    {
        return (!is_single_only(connector) || len_terms == 1) && 
            (!is_double_only(connector) || len_terms == 2) && 
            (!is_multiple_only(connector) || len_terms > 1) && 
            (len_terms > 0);
    }
}

# endif //_CONNECTOR_H