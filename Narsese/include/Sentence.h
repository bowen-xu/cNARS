#ifndef _SENTENCE_H_
#define _SENTENCE_H_

#include "./Term.h"
#include "./Truth.h"
#include <string>
#include <memory>

namespace SENTENCE
{
    using TERM::pTerm;
    using TERM::Term;
    using TRUTH::pTruth;
    using TRUTH::Truth;

    namespace PUNCTUATION
    {
        using std::string;
        enum Punctuation
        {
            Judgement = 0,
            Question,
            Goal,
            Quest
        };

        const string Repr[] = {string("."), string("?"), string("!"), string("@")};
    }

    class Sentence
    {
    public:
        pTerm term;
        pTruth truth = nullptr;
        PUNCTUATION::Punctuation punct;
        Sentence(pTerm _term, PUNCTUATION::Punctuation _punct, pTruth _truth=nullptr) : term(_term), punct(_punct), truth(_truth) {}

        inline bool is_judgement() { return punct == PUNCTUATION::Judgement; }
        inline bool is_question() { return punct == PUNCTUATION::Question; }
        inline bool is_goal() { return punct == PUNCTUATION::Goal; }
        inline bool is_quest() { return punct == PUNCTUATION::Quest; }
    };

    typedef std::shared_ptr<Sentence> pSentence;

    class Judgement : public Sentence
    {
    public:
        // pTruth truth;
        Judgement(pTerm _term, pTruth _truth) : Sentence(_term, PUNCTUATION::Judgement, _truth) {}
    };

    class Question : public Sentence
    {
    public:
        Question(pTerm _term) : Sentence(_term, PUNCTUATION::Question) {}
    };

    class Goal : public Sentence
    {
    public:
        pTruth &desire = Sentence::truth;
        Goal(pTerm _term, pTruth _desire) : Sentence(_term, PUNCTUATION::Goal, _desire) {}
    };

    class Quest : public Sentence
    {
    public:
        Quest(pTerm _term) : Sentence(_term, PUNCTUATION::Quest) {}
    };

} // namespace SENTENCE

#endif //_SENTENCE_H_