#ifndef _COMPOUND_H
#define _COMPOUND_H
#include "../utils/hash.h"
#include "./Connector.h"
#include "./Term.h"
#include "Config.h"
#include <functional>
#include <pybind11/pybind11.h>
#include <string>
#include <vector>

#if SRC_LIST == LIST_BOOST
#include <boost/container/list.hpp>
using boost::container::list;
#elif SRC_LIST == _LIST_STD
#include <list>
using std::list;
#endif

namespace TERM
{
    class Term;
    class pTerm;
    // class pTerms;
}

namespace COMPOUND
{
    namespace py = pybind11;

    using CONNECTOR::Connector;
    using std::string;
    using TERM::pTerm;
    using TERM::pTerms;
    using TERM::Term;
    using TERM::Terms;
    using TERM::TermType;
    using UTILS::Hash;

    class pCompound : public pTerm
    {
    public:
        pCompound(Term *term, void *interpreter = nullptr) : pTerm(term, interpreter) {}
        pCompound() : pTerm() {}
    };

    class Compound : public Term
    {
    public:
        // string word_sorted;
        bool is_commutative : 1 = false;

        inline const auto &components() const { return *terms; }

        Compound(Connector connector, pTerms terms, bool is_input = false);
        Compound(Connector connector, std::list<pTerm> &terms, bool is_input = false);
        Compound(Connector connector, std::vector<pTerm> &terms, bool is_input = false);
        Compound(Connector connector, std::initializer_list<pTerm> terms, bool is_input = false);
        Compound(Connector connector, pTerm term, bool is_input = false) : Compound(connector, {term}, is_input){};

        Compound(const Compound &other, bool deep);

        template <typename _T>
        static pCompound create(Connector connector, _T &terms)
        {
            return pCompound((Term *)new Compound(connector, terms));
        }

        static auto ExtensionalSet(std::initializer_list<pTerm> terms)
        {
            return pTerm(new Compound(Connector::ExtensionalSet, terms));
        }
        static auto IntensionalSet(std::initializer_list<pTerm> terms)
        {
            return pTerm(new Compound(Connector::IntensionalSet, terms));
        }

        virtual size_t do_hashing()
        {
            std::vector<size_t> values{(size_t)TermType::COMPOUND, (size_t)'(', (size_t)connector};
            for (auto &term : *terms)
            {
                values.push_back(term->hash_value);
            }
            values.push_back((size_t)')');

            auto &vars_independent = *this->_vars_independent->indices_normalized();
            auto &vars_dependent = *this->_vars_dependent->indices_normalized();
            auto &vars_query = *this->_vars_query->indices_normalized();
            values.push_back((size_t)'(');
            values.insert(values.end(), vars_independent.begin(), vars_independent.end());
            values.push_back((size_t)')');
            values.push_back((size_t)'(');
            values.insert(values.end(), vars_dependent.begin(), vars_dependent.end());
            values.push_back((size_t)')');
            values.push_back((size_t)'(');
            values.insert(values.end(), vars_query.begin(), vars_query.end());
            values.push_back((size_t)')');

            this->hash_value = Hash{}(values);
            this->is_hashed = true;

            return this->hash_value;
        }

    private:
        Compound(Connector &connector) : Term(TermType::COMPOUND)
        {
            // this->type = TermType::COMPOUND;
            this->connector = connector;
            this->terms = pTerms(new Terms(CONNECTOR::is_commutative(connector)));
        }
    };
    
    void pybind_compound(py::module &m);

} // namespace COMPOUND

// #include "Compound.inl"

#endif // _COMPOUND_H
