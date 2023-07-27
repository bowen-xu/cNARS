#ifndef _TERM_H
#define _TERM_H

#include "Connector.h"
#include "Copula.h"
#include "utils/IndexVar.h"
#include "utils/hash.h"
#include <algorithm>
#include <array>
#include <list>
#include <memory>
#include <string>
#include <unordered_set>
#include <fmt/core.h>
#include <pybind11/pybind11.h>

// #include "../utils/repr.h"
namespace VARIABLE
{
    class Variable;
}

namespace COMPOUND
{
    class Compound;
}

namespace STATEMENT
{
    class Statement;
}

namespace TERM
{
    namespace py = pybind11;
    
    using CONNECTOR::Connector;
    using COPULA::Copula;
    // using REPR::repr;
    using INDEXVAR::IndexVar;
    using INDEXVAR::pIndexVar;
    using std::string;
    using std::unordered_set;
    using UTILS::Hash;
    using UTILS::hash;


    class Terms;
    class Term;
    // typedef std::shared_ptr<Term> pTerm;
    class pTerm : public std::shared_ptr<Term>
    {
    private:
        void *_interpreter = nullptr;

    public:
        // using std::shared_ptr<Term>::shared_ptr;
        pTerm() : std::shared_ptr<Term>::shared_ptr() {}
        pTerm(Term *term, void *interpreter = nullptr) : std::shared_ptr<Term>(term), _interpreter(interpreter) {}
        // pTerm() : std::shared_ptr<Term>() {}

        ~pTerm();

        std::string __repr__(void *interpreter) const;

    private:
        void _free_from_interpreter();
        // void _free_from_interpreter() {}
    };

    typedef std::shared_ptr<Terms> pTerms;

    enum PYBIND11_EXPORT TermType
    {
        ATOM = 0,
        STATEMENT = 1,
        COMPOUND = 2,
        INTERVAL = -1,
        OPERATION = -2,
        VARIABLE = -3
    };

    class PYBIND11_EXPORT Term
    {
    public:
        /* for statement */
        pTerm subject;
        pTerm predicate;
        Copula copula = COPULA::None;

        /* for compound */
        Connector connector = CONNECTOR::None;
        pTerms terms;

        /* for all */
        TermType type = TermType::ATOM;

        bool is_var : 1 = false;
        bool is_ivar : 1 = false;
        bool is_dvar : 1 = false;
        bool is_qvar : 1 = false;
        bool has_var : 1 = false;  // Whether the term contains variable(s).
        bool has_ivar : 1 = false; // Whether the term contains independent variable(s).
        bool has_dvar : 1 = false; // Whether the term contains dependent variable(s).
        bool has_qvar : 1 = false; // Whether the term contains query variable(s).

        bool is_closed : 1 = true; // Whether the term is closed or open in terms of variable.
        bool is_interval : 1 = false;
        bool is_operation : 1 = false;

        bool is_higher_order : 1 = false;

        bool is_hashed : 1 = false;
        size_t hash_value = 0;

        int complexity = 1; // The complexity of the term. Read only.

        pIndexVar _vars_independent = IndexVar::create();
        pIndexVar _vars_dependent = IndexVar::create();
        pIndexVar _vars_query = IndexVar::create();

        // Term(int hash_value);
        // Term(char *_word);
        // string word;
        Term() : hash_value(Hash{}(std::initializer_list<size_t>{(size_t)TermType::ATOM, (size_t)this})), is_hashed(true){};
        Term(const TermType _type) : type(_type) {}
        // ~Term()
        // {
        //     std::cout << (size_t)this << " Term freed" << std::endl;
        // }
        size_t __hash__()
        {
            return this->is_hashed ? this->hash_value : this->do_hashing();
        }

        virtual size_t do_hashing()
        {
            this->hash_value = Hash{}(std::initializer_list<size_t>{(size_t)TermType::ATOM, (size_t)this});
            this->is_hashed = true;
            return this->hash_value;
        }

        inline bool is_atom() const { return this->type == TermType::ATOM; }
        inline bool is_statement() const { return this->type == TermType::STATEMENT; }
        inline bool is_compound() const { return this->type == TermType::COMPOUND; }

        static pTerm create()
        {
            auto term = new Term();
            // std::cout << "create Term " << (size_t)term << std::endl;
            return pTerm(term);
        }

        static pTerm create(const char *word, void *interpreter = nullptr);

        static pTerm clone(pTerm term);

        bool operator==(Term &other);

        bool operator<(Term &other);

    protected:
        template <typename _Container>
        void _refresh_var_status(const _Container &terms)
        {
            this->has_var = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                        { return term->has_var; });
            this->has_ivar = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                         { return term->has_ivar; });
            this->has_dvar = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                         { return term->has_dvar; });
            this->has_qvar = std::any_of(terms.begin(), terms.end(), [](const pTerm &term)
                                         { return term->has_qvar; });
        }

        void _init_indexvars(const std::array<pIndexVar, 3> &variables, const Terms &terms);

        void _init_indexvars(const std::array<pIndexVar, 3> &variables, std::initializer_list<pTerm> terms);

        void _build_indexvars()
        {
            if (this->has_ivar)
                this->_vars_independent->build();
            else
                this->_vars_independent->_is_built = true;
            if (this->has_dvar)
                this->_vars_dependent->build();
            else
                this->_vars_dependent->_is_built = true;
            if (this->has_qvar)
                this->_vars_query->build();
            else
                this->_vars_query->_is_built = true;
        }

        std::array<pIndexVar, 3> _index_vars() const
        {
            return {this->_vars_independent, this->_vars_dependent, this->_vars_query};
        }
    };

    class PYBIND11_EXPORT Iterator
    {
    public:
        // using iterator_category = typename std::iterator_traits<pTerm *>::iterator_category;
        // using value_type = typename std::iterator_traits<pTerm *>::value_type;
        using value_type = pTerm;
        // using reference = pTerm&;
        // using pointer = pTerm*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

    public:
        Iterator(const Iterator &iterator)
        {
            *this = iterator;
            if (this->_is_commutative)
                it_ = new auto(*(std::set<pTerm>::iterator *)(iterator.it_));
            else
                it_ = new auto(*(std::vector<pTerm>::iterator *)(iterator.it_));
        }
        Iterator(std::vector<pTerm>::const_iterator it) : it_((void *)new auto(it)), _is_commutative(false) {}
        Iterator(std::set<pTerm>::iterator it) : it_((void *)new auto(it)), _is_commutative(true) {}

        ~Iterator()
        {
            if (it_ == nullptr)
                return;
            if (this->_is_commutative)
                delete ((std::vector<pTerm>::iterator *)it_);
            else
                delete ((std::set<pTerm>::iterator *)it_);
            it_ = nullptr;
        }

        const pTerm &operator*()
        {
            if (this->_is_commutative)
                return **((std::set<pTerm>::iterator *)it_);
            else
                return **((std::vector<pTerm>::iterator *)it_);
        }

        Iterator &operator++()
        {
            if (this->_is_commutative)
                (*((std::set<pTerm>::iterator *)it_))++;
            else
                (*((std::vector<pTerm>::iterator *)it_))++;
            return *this;
        }

        Iterator &operator++(int)
        {
            return ++(*this);
        }

        bool operator!=(const Iterator &other) const
        {
            if (this->_is_commutative)
                return (*((std::set<pTerm>::iterator *)this->it_)) != (*((std::set<pTerm>::iterator *)other.it_));
            else
                return (*((std::vector<pTerm>::iterator *)this->it_)) != (*((std::vector<pTerm>::iterator *)other.it_));
        }

        bool operator==(const Iterator &other) const
        {
            if (this->_is_commutative)
                return (*((std::set<pTerm>::iterator *)this->it_)) == (*((std::set<pTerm>::iterator *)other.it_));
            else
                return (*((std::vector<pTerm>::iterator *)this->it_)) == (*((std::vector<pTerm>::iterator *)other.it_));
        }

        Iterator operator+(int n) const
        {
            if (this->_is_commutative)
            {
                std::set<pTerm>::iterator newIt = *(std::set<pTerm>::iterator *)it_;
                std::advance(newIt, n);
                return Iterator(newIt);
            }
            else
            {
                std::vector<pTerm>::iterator newIt = *(std::vector<pTerm>::iterator *)it_;
                std::advance(newIt, n);
                return Iterator(newIt);
            }
        }
        Iterator operator-(int n) const
        {
            if (this->_is_commutative)
            {
                std::set<pTerm>::iterator newIt = *(std::set<pTerm>::iterator *)it_;
                std::advance(newIt, -n);
                return Iterator(newIt);
            }
            else
            {
                std::vector<pTerm>::iterator new_it = *(std::vector<pTerm>::iterator *)it_;
                std::advance(new_it, -n);
                return Iterator(new_it);
            }
        }

    private:
        bool _is_commutative;
        void *it_;
    };

    class PYBIND11_EXPORT Terms
    {
    public:
        struct compare
        {
            bool operator()(const pTerm &a, const pTerm &b) const
            {
                auto &term1 = *a;
                auto &term2 = *b;
                return term1 < term2;
                // return a < b;
            }
        };

    public:
        // std::vector<pTerm> terms;
        std::vector<pTerm> terms_ordered;
        std::set<pTerm, compare> terms_unordered;

        // IndexVar _vars_independent = IndexVar();
        // IndexVar _vars_dependent = IndexVar();
        // IndexVar _vars_query = IndexVar();

        bool _is_commutative;

        Terms(bool is_commutative) : _is_commutative(is_commutative) {}

        // Terms(std::list<pTerm> terms, bool is_commutative);
        Terms(std::list<pTerm> terms, bool is_commutative) : _is_commutative(is_commutative)
        {
            this->fill_terms(terms);
        }
        template <typename _Compare>
        Terms(std::set<pTerm, _Compare> terms, bool is_commutative) : _is_commutative(is_commutative)
        {
            this->fill_terms(terms);
        }
        Terms(std::vector<pTerm> &terms, bool is_commutative) : _is_commutative(is_commutative)
        {
            this->fill_terms(terms);
        }

        Terms(std::initializer_list<pTerm> terms, bool is_commutative) : _is_commutative(is_commutative)
        {
            this->fill_terms(terms);
        }

        Terms(Terms &terms, bool is_commutative) : _is_commutative(is_commutative)
        {
            this->fill_terms(terms);
        }

        inline static pTerms create(bool is_commutative)
        {
            return pTerms(new Terms(is_commutative));
        }

        template <typename _T>
        inline static pTerms create(_T terms, bool is_commutative)
        {
            return pTerms(new Terms(terms, is_commutative));
        }

        inline static auto intersection(std::vector<pTerms> terms_all)
        {
            if (terms_all.size() == 0)
                throw std::runtime_error("Empty input.");

            auto it = terms_all.begin();
            std::set<pTerm, compare> intersection((*it)->terms_unordered);
            for (++it; it != terms_all.end(); ++it)
            {
                const auto &terms = *(*it);
                if (!terms._is_commutative)
                    throw std::runtime_error("Each `Terms` should be commutative.");
                std::set<pTerm, compare> temp{};
                std::set_intersection(
                    intersection.begin(), intersection.end(),
                    terms.begin(), terms.end(),
                    std::inserter(temp, temp.begin()), compare{});
                intersection = temp;
            }
            return Terms::create(intersection, true);
        }

        inline static auto union_(std::vector<pTerms> terms_all)
        {
            if (terms_all.size() == 0)
                throw std::runtime_error("Empty input.");

            auto it = terms_all.begin();
            std::set<pTerm, compare> union_((*it)->terms_unordered);
            for (++it; it != terms_all.end(); ++it)
            {
                const auto &terms = *(*it);
                if (!terms._is_commutative)
                    throw std::runtime_error("Each `Terms` should be commutative.");
                std::set<pTerm, compare> temp;
                std::set_union(
                    union_.begin(), union_.end(),
                    terms.begin(), terms.end(),
                    std::inserter(temp, temp.begin()), compare{});
                union_ = temp;
            }
            return Terms::create(union_, true);
        }

        inline static auto difference(std::vector<pTerms> terms_all)
        {
            if (terms_all.size() == 0)
                throw std::runtime_error("Empty input.");

            auto it = terms_all.begin();
            std::set<pTerm, compare> difference((*it)->terms_unordered);
            for (++it; it != terms_all.end(); ++it)
            {
                const auto &terms = *(*it);
                if (!terms._is_commutative)
                    throw std::runtime_error("Each `Terms` should be commutative.");
                std::set<pTerm, compare> temp;
                std::set_difference(
                    difference.begin(), difference.end(),
                    terms.begin(), terms.end(),
                    std::inserter(temp, temp.begin()), compare{});
                difference = temp;
            }
            return Terms::create(difference, true);
        }

        inline void push_back(pTerm term)
        {
            if (this->_is_commutative)
                this->terms_unordered.insert(term);
            else
                this->terms_ordered.push_back(term);
        }

        inline auto size()
        {
            if (this->_is_commutative)
                return this->terms_unordered.size();
            else
                return this->terms_ordered.size();
        }

        Iterator begin() const
        {
            if (this->_is_commutative)
                return Iterator(this->terms_unordered.begin());
            else
                return Iterator(this->terms_ordered.begin());
        }

        Iterator end() const
        {
            if (this->_is_commutative)
                return Iterator(this->terms_unordered.end());
            else
                return Iterator(this->terms_ordered.end());
        }

        operator std::vector<pTerm>() const
        {
            if (this->_is_commutative)
                return std::vector<pTerm>(this->terms_unordered.begin(), this->terms_unordered.end());
            else
                return this->terms_ordered;
        }

    private:
        template <typename _T>
        void fill_terms(_T terms)
        {
            if (this->_is_commutative)
            {
                for (auto it = terms.begin(); it != terms.end(); it++)
                {
                    this->terms_unordered.insert((*it));
                }
            }
            else
            {
                for (auto it = terms.begin(); it != terms.end(); it++)
                {
                    this->terms_ordered.push_back((*it));
                }
            }
        }
    };
    void pybind_term(py::module &m);
    void pybind_terms(py::module &m);

} // namespace Term
// #include "Term.inl"

#endif // _TERM_H