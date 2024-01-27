// #include "../include/Narsese.h"
#include "../include/Compound.h"
#include "utils/hash.h"
#include <map>
#include <numeric>
#include <tuple>
#include <unordered_map>
#include <vector>
#include "Interpreter/include/Interpreter.hpp"

using namespace COMPOUND;
using std::tuple;
using std::vector;
using UTILS::hash;

/*
The `compounds` should have the same `connector`.
(&, {A, B}, {B, C}) ====> {B}
(|, {A, B}, {B, C}) ====> {A, B, C}
(&, [A, B], [B, C]) ====> [A, B, C]
(|, [A, B], [B, C]) ====> [B]
(-, {A, B}, {B, C}) ====> {A}
(~, [A, B], [B, C]) ====> [A]

It is ensured that the concerned components have no further nested compound which should be unfolded, because if there were, it would be unfolded when building its parent compound.

Make sure all the `compounds` have the same `connector`
*/
pTerms _merge_compounds(Connector connector_parent, Connector connector, const vector<pTerm> &compounds)
{
    auto get_all_terms = [connector_parent](const vector<pTerm> &input, std::vector<pTerms> &output)
    {
        for (auto term : input)
        {
            auto &cmpd = (Compound &)*term;
            const auto components = cmpd.terms;
            output.push_back(components);
        }
    };

    if (connector_parent == Connector::ExtensionalIntersection)
    {
        if (connector == Connector::ExtensionalSet)
        {
            std::vector<pTerms> terms_all;
            get_all_terms(compounds, terms_all);
            return Terms::intersection(terms_all);
        }
        else if (connector == Connector::IntensionalSet)
        {
            std::vector<pTerms> terms_all;
            get_all_terms(compounds, terms_all);
            return Terms::union_(terms_all);
        }
        else
        {
            return nullptr; // Return nullptr indicating no merge is needed
        }
    }
    else if (connector_parent == Connector::IntensionalIntersection)
    {
        if (connector == Connector::ExtensionalSet)
        {
            std::vector<pTerms> terms_all;
            get_all_terms(compounds, terms_all);
            return Terms::union_(terms_all);
        }
        else if (connector == Connector::IntensionalSet)
        {
            std::vector<pTerms> terms_all;
            get_all_terms(compounds, terms_all);
            return Terms::intersection(terms_all);
        }
        else
        {
            return nullptr; // Return nullptr indicating no merge is needed
        }
    }
    else if (connector_parent == Connector::ExtensionalDifference && connector == Connector::ExtensionalSet)
    {
        std::vector<pTerms> terms_all;
        get_all_terms(compounds, terms_all);
        return Terms::difference(terms_all);
    }
    else if (connector_parent == Connector::IntensionalDifference && connector == Connector::IntensionalSet)
    {
        std::vector<pTerms> terms_all;
        get_all_terms(compounds, terms_all);
        return Terms::difference(terms_all);
    }
    else if (connector_parent == connector)
    {
        std::vector<pTerm> terms_all;
        for (auto term : compounds)
        {
            auto &cmpd = (Compound &)*term;
            const auto components = cmpd.terms;
            terms_all.insert(terms_all.end(), components->begin(), components->end());
        }
        return Terms::create(terms_all, CONNECTOR::is_commutative(connector));
    }
    else
    {
        return nullptr; // Return nullptr indicating no merge is needed
    }
}

/*
pre-process the terms, return the connecor of this compound and the set/list of components.
For `{{A, B}, {B, C}}`, return `{, A, B, C`;
    proof: {{A, B}, {B, C}}={(|, {A}, {B}), (|, {B}, {C})}=(|, (|, {A}, {B}), (|, {B}, {C}))=(|, {A}, {B}, {C})={A, B, C}
For `[[A, B], [B, C]]`, return `[, A, B, C`;
For `(con, (con, A, B), (con, B, C))`, return `con, A, B, C` if con is commutative, else return `con, A, B, B, C`
For `(|, {A, B}, {B, C})`, return `{, A, B, C`;
For `(&, [A, B], [B, C])`, return `[, A, B, C`;
For `(con, A, B, C)`, return `con, A, B, C`;
For `{{A, B}, {B, C}, D}`, return `{, {A, B, C}, D`;

Returns:
    connector, terms

*/
std::tuple<Connector, pTerms> prepocess_terms(Compound &self, Connector connector_parent, pTerms terms)
{
    // static const std::set<Connector> set1{Connector::Product, Connector::IntensionalImage, Connector::ExtensionalImage, Connector::ExtensionalDifference, Connector::IntensionalDifference};
    auto is_commutative = CONNECTOR::is_commutative(connector_parent);
    if (!CONNECTOR::is_reducible(connector_parent))
    {
        /*
        For example, in the test-case `nal6.22.nal`, there is a statement
        `<(*,(*,(*,0))) --> num>`
        */
        return {connector_parent, terms};
    }
    if (is_commutative)
    {
        /*
        if there are terms with the same commutative connector, they should be combined together
        */
        // auto categories = std::map<Connector, std::vector<pTerm>>();
        // auto categories = std::unordered_map<Connector, std::vector<pTerm>>();
        std::unordered_map<Connector, std::vector<pTerm>> categories{};
        pTerms _terms;
        Connector _connector;
        /* Step 1. Categorize the terms according to their connectors. */

        pTerms terms2 = terms;
        pTerms terms = pTerms(new Terms(is_commutative));
        for (auto term : *terms2)
        {
            if (term->is_compound() && term->connector == connector_parent)
                for (auto _term : *(term->terms))
                    terms->push_back(_term);
            else
                terms->push_back(term);
        }

        for (auto term : *terms)
        {
            _connector = Connector::None; // `None` means the connector of the term is not cared about, because it just needs to be added into the parent compound-term as a whole.
            if (term->is_compound())
            {
                auto &cmpd = (Compound &)*term;
                if (cmpd.is_commutative)
                    _connector = cmpd.connector;
            }
            if (!categories.contains(_connector))
                categories[_connector] = std::vector<pTerm>();
            auto &category = categories[_connector];
            category.push_back(term);
        }

        /* Step 2. */
        std::vector<std::tuple<Connector, pTerms>> terms_norm;
        for (const auto &pair : categories)
        {
            auto &connector = pair.first;
            auto &compounds = pair.second;
            if (connector == Connector::None)
            {
                for (auto &compound : compounds)
                    terms_norm.push_back({connector, Terms::create(std::vector{compound}, true)});
                continue;
            }

            /* Now, `connector` is not `None`. */
            auto terms_merged = _merge_compounds(connector_parent, connector, compounds);
            if (terms_merged == nullptr)
            {
                for (auto &compound : compounds)
                    terms_norm.push_back({connector, compound->terms});
                continue;
            }

            /*
            Now, `terms_merged` is not `None`.

            However, the compounds (in `terms_merged`), as components, shouldn't further be constructed as a compound term immediately, as there are some cases where there is only one compound and the parent connector should be set as the current single compound connector, for example, (|, {A, B}, {C, D}) is handled and `terms_merged` is `A, B, C, D`. In this case, if this function returned a compound `{A, B, C, D}`, the parent compound would be (&, {A, B, C, D}), which is obviously incorrect.

            Hence, the final construction of the compound is out of this function.
            */
            terms_norm.push_back({connector, terms_merged});
        }

        /* Step 3. */
        if (terms_norm.size() > 1)
        {
            std::vector<pTerm> _terms_all;
            for (auto &pair : terms_norm)
            {
                std::tie(_connector, _terms) = pair;
                if (_connector == Connector::None || _connector == connector_parent)
                {
                    _terms_all.insert(_terms_all.end(), _terms->begin(), _terms->end());
                }
                else if (CONNECTOR::check_valid(_connector, _terms->size()))
                {
                    auto _term = Compound::create(_connector, _terms);
                    _terms_all.push_back(_term);
                }
            }
            if (_terms_all.size() > 1)
            {
                return {connector_parent, Terms::create(_terms_all, true)};
            }
            else // _terms_all.size() == 1
            {
                auto _term = *_terms_all.begin();
                if (_term->is_compound())
                {
                    auto &_cmpd = (Compound &)(*_term);
                    auto _connector = _cmpd.connector;
                    terms_norm = {{_connector, _cmpd.terms}};
                }
                else
                {
                    terms_norm = {{Connector::None, Terms::create(_terms_all, true)}};
                }
            }
        }

        /* Step 4. */
        {
            /*
            Now, there is only one term in `terms_norm`.
            */
            std::tie(_connector, _terms) = *terms_norm.begin();
            /*
            the connector returned depends on the types of `connector` and `connector_parent`. For example,
                if `connector_parent` is `&` and `connector` is `{`, the return `connector`;
                if `connector_parent` is `|` and `connector` is `{`, the return `connector`;
                if `connector_parent` is `&` and `connector` is `&`, it makes no difference returning either `connector` or `connector_parent`;
            */
            if ((_connector == Connector::ExtensionalSet && connector_parent == Connector::IntensionalIntersection) ||
                (_connector == Connector::IntensionalSet && connector_parent == Connector::ExtensionalIntersection))
            {
                return {_connector, Terms::create(*_terms, true)};
            }

            /* otherwise, return `connector_parent` as the connector. */
            return {connector_parent, Terms::create(*_terms, true)};
            // return connector_parent, Terms(terms, is_commutative=True, is_input=is_input)
        }
    }
    else
    {
        /*
        E.g. (&/, (&/, A, B), (&|, C, D), E) will be converted to (&/, A, B, (&|, C, D), E)
        */
        auto expanded_terms = pTerms(new Terms(is_commutative));

        for (const auto &term : *terms)
        {
            if (term->is_compound() && term->connector == connector_parent)
            {
                auto &cmpd = (Compound &)*term;
                for (const auto &component : cmpd.components())
                {
                    expanded_terms->push_back(component);
                }
            }
            else
            {
                expanded_terms->push_back(term);
            }
        }
        return {connector_parent, expanded_terms};
    }
    return {connector_parent, terms};
}

Compound::Compound(Connector connector, pTerms terms, bool is_input) : Term(TermType::COMPOUND)
{
    this->is_hashed = false;

    // this->type = TermType::COMPOUND;
    this->connector = connector;
    pTerms _terms;
    std::tie(this->connector, _terms) = prepocess_terms(*this, connector, terms);
    this->is_commutative = CONNECTOR::is_commutative(this->connector);
    if (is_input)
    {
        this->terms = _terms;
    }
    else
    {
        this->terms = Terms::create(this->is_commutative);
        for (auto &_term : *_terms)
            this->terms->push_back(Term::clone(_term));
    }
    this->hash_value = hash(*this);
    this->complexity = std::accumulate(this->terms->begin(), this->terms->end(), 0,
                                       [](int sum, const auto &term)
                                       { return sum + term->complexity; });

    this->_refresh_var_status(*this->terms);
    this->_init_indexvars(this->_index_vars(), *this->terms);
    this->_build_indexvars();
}

Compound::Compound(Connector connector, std::list<pTerm> &terms, bool is_input) : Compound::Compound(connector, pTerms(new Terms(terms, CONNECTOR::is_commutative(connector))), is_input)
{
}

Compound::Compound(Connector connector, std::vector<pTerm> &terms, bool is_input) : Compound::Compound(connector, pTerms(new Terms(terms, CONNECTOR::is_commutative(connector))), is_input)
{
}

Compound::Compound(Connector connector, std::initializer_list<pTerm> terms, bool is_input) : Compound::Compound(connector, pTerms(new Terms(terms, CONNECTOR::is_commutative(connector))), is_input)
{
}

void COMPOUND::pybind_compound(py::module &m)
{
    py::class_<COMPOUND::pCompound, TERM::pTerm>(m, "Compound")
        .def(py::init(
            [](CONNECTOR::Connector connector, py::args args)
            {
                std::vector<TERM::pTerm> terms{};
                for (auto arg : args)
                    terms.push_back(py::cast<TERM::pTerm>(arg));
                return COMPOUND::Compound::create(connector, terms);
            }))
        // .def("__repr__", &TERM::pTerm::__repr__, py::arg("interpreter") = (void *)&INTERPRETER::interpreter);
        .def("__repr__", [](const pCompound &self, void* interpreter=nullptr){
                if (interpreter == nullptr)
                    interpreter = (void *)&INTERPRETER::interpreter;
                return self.__repr__(interpreter);
            });
}
