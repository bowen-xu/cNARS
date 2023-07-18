#include "../include/Connector.h"


using namespace CONNECTOR;

namespace CONNECTOR
{
    void pybind_connnector(py::module &m)
    {
        py::enum_<CONNECTOR::Connector>(m, "Connector")
            .value("Conjunction", CONNECTOR::Connector::Conjunction, "&&")
            .value("Disjunction", CONNECTOR::Connector::Disjunction, "||")
            .value("Product", CONNECTOR::Connector::Product, "*")
            .value("ParallelEvents", CONNECTOR::Connector::ParallelEvents, "&|")
            .value("SequentialEvents", CONNECTOR::Connector::SequentialEvents, "&/")
            .value("IntensionalIntersection", CONNECTOR::Connector::IntensionalIntersection, "|")
            .value("ExtensionalIntersection", CONNECTOR::Connector::ExtensionalIntersection, "&")
            .value("ExtensionalDifference", CONNECTOR::Connector::ParallelEvents, "-")
            .value("IntensionalDifference", CONNECTOR::Connector::IntensionalDifference, "~")
            .value("Negation", CONNECTOR::Connector::Negation, "--")
            .value("IntensionalSet", CONNECTOR::Connector::IntensionalSet, "[")
            .value("ExtensionalSet", CONNECTOR::Connector::ExtensionalSet, "{")
            .value("IntensionalImage", CONNECTOR::Connector::IntensionalImage, "\\")
            .value("ExtensionalImage", CONNECTOR::Connector::ExtensionalImage, "/")
            .value("List", CONNECTOR::Connector::List, "#");
    }
} // namespace CONNECTOR
