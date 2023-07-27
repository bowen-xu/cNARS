#ifndef _SENTENCE_H_
#define _SENTENCE_H_

#include "./Evidence.h"
#include "./Term.h"
#include "./Truth.h"
#include "./Tense.h"
#include "Global.h"
#include <memory>
#include <string>
#include <pybind11/pybind11.h>

namespace SENTENCE
{
    namespace py = pybind11;

    using EVIDENCE::Base;
    using EVIDENCE::pBase;
    using TERM::pTerm;
    using TERM::Term;
    using TRUTH::pTruth;
    using TRUTH::Truth;

    using std::string;

    namespace PUNCTUATION
    {
        enum Punctuation
        {
            Judgement = 0,
            Question,
            Goal,
            Quest
        };

        const string Repr[] = {string("."), string("?"), string("!"), string("@")};
    }

    class Stamp
    {
    public:
        pBase evidential_base;
        signed int t_creation;
        signed int t_occurrence;
        signed int t_put;
        bool is_eternal;

    public:
        /*
        Args:
            t_creation(int): creation time of the stamp
            t_occurrence(int): estimated occurrence time of the event
            t_put(int): the time when it was put into buffer
        */
        Stamp(bool is_eternal = false) : Stamp(GLOBAL::time, GLOBAL::time, -1, pBase(new Base({GLOBAL::get_input_id()})), is_eternal) {}

        Stamp(signed int  t_occurrence) : Stamp(t_occurrence, GLOBAL::time, -1, pBase(new Base({GLOBAL::get_input_id()})), false) {}

        Stamp(signed int t_occurrence, signed int t_creation, signed int t_put, pBase evidential_base, bool is_eternal = true) : t_occurrence(t_occurrence), t_creation(t_creation), t_put(t_put), evidential_base(evidential_base), is_eternal(is_eternal)
        {
            if (evidential_base == nullptr)
                evidential_base = pBase(new Base());
        }

        auto tense()
        {
            if (this->is_eternal)
                return TENSE::Tense::Eternal;
            else if (this->t_occurrence >= (signed int)(GLOBAL::time + CONFIG::temporal_duration))
                return TENSE::Tense::Future;
            else if (this->t_occurrence <= (signed int)(GLOBAL::time - CONFIG::temporal_duration))
                return TENSE::Tense::Past;
            else
                return TENSE::Tense::Present;
        }

        void eternalize()
        {
            this->is_eternal = true;
        }

        void extend_evidenital_base(const Base& base)
        {
            if (this->evidential_base == nullptr)
                this->evidential_base = pBase(new Base());
            this->evidential_base->extend(base);
        }
    };

    typedef std::shared_ptr<Stamp> pStamp;

    class PYBIND11_EXPORT Sentence
    {
    public:
        pTerm term;
        pTruth truth = nullptr;
        pStamp stamp = nullptr;
        PUNCTUATION::Punctuation punct;
        Sentence(pTerm _term, PUNCTUATION::Punctuation _punct, pTruth _truth = nullptr, pStamp _stamp=nullptr) : term(_term), punct(_punct), truth(_truth), stamp(_stamp) 
        {
            if (stamp == nullptr)
                stamp = pStamp(new Stamp(true));
        }

        inline bool is_judgement() { return punct == PUNCTUATION::Judgement; }
        inline bool is_question() { return punct == PUNCTUATION::Question; }
        inline bool is_goal() { return punct == PUNCTUATION::Goal; }
        inline bool is_quest() { return punct == PUNCTUATION::Quest; }
    };

    // typedef std::shared_ptr<Sentence> pSentence;
    class PYBIND11_EXPORT pSentence : public std::shared_ptr<Sentence>
    {
    public:
        using std::shared_ptr<Sentence>::shared_ptr;

        std::string __repr__(void *interpreter = nullptr) const;
    };
    
    class Judgement : public Sentence
    {
    public:
        // pTruth truth;
        Judgement(pTerm _term, pTruth _truth=nullptr, pStamp _stamp=nullptr) : Sentence(_term, PUNCTUATION::Judgement, _truth, _stamp) 
        {
            if (truth == nullptr)
                truth = pTruth(new Truth(CONFIG::f, CONFIG::c_judgement, CONFIG::k));
        }
    };

    class Question : public Sentence
    {
    public:
        Question(pTerm _term, pStamp _stamp=nullptr) : Sentence(_term, PUNCTUATION::Question, nullptr, _stamp) {}
    };

    class Goal : public Sentence
    {
    public:
        pTruth &desire = Sentence::truth;
        Goal(pTerm _term, pTruth _desire, pStamp _stamp=nullptr) : Sentence(_term, PUNCTUATION::Goal, _desire, _stamp) 
        {
            if (truth == nullptr)
                truth = pTruth(new Truth(CONFIG::f, CONFIG::c_goal, CONFIG::k));
        }
    };

    class Quest : public Sentence
    {
    public:
        Quest(pTerm _term, pStamp _stamp=nullptr) : Sentence(_term, PUNCTUATION::Quest, nullptr, _stamp) {}
    };

    void pybind_sentence(py::module &m);
} // namespace SENTENCE

#endif //_SENTENCE_H_