#ifndef _SENTENCE_H_
#define _SENTENCE_H_

#include "./Term.h"
#include "./Truth.h"

namespace SENTENCE
{
    using TERM::Term;
    using TRUTH::Truth;
    namespace PUNCTUATION
    {
        enum Punctuation
        {
            Judgement = 0,
            Question,
            Goal,
            Quest
        };
    }

    // const auto JUDGEMENT = Punctuation::Judgement;
    // const auto QUESTION = Punctuation::Question;
    // const auto GOAL = Punctuation::Goal;
    // const auto QUEST = Punctuation::Quest;

    class Sentence
    {
    public:
        Term &term;
        PUNCTUATION::Punctuation punct;
        Sentence(Term& _term, PUNCTUATION::Punctuation _punct) : term(_term), punct(_punct) {}
    };

    class Judgement : public Sentence
    {
    public:
        Truth& truth;
        Judgement(Term& _term, Truth& _truth) : truth(_truth), Sentence(_term, PUNCTUATION::Judgement) {}
    };

    class Question : public Sentence
    {
    public:
        Question(Term& _term) : Sentence(_term, PUNCTUATION::Question) {}
    };

    class Goal : public Sentence
    {
    public:
        Truth& desire;
        Goal(Term& _term, Truth& _desire) : desire(_desire), Sentence(_term, PUNCTUATION::Goal) {}
    };

    class Quest : public Sentence
    {
    public:
        Quest(Term& _term) : Sentence(_term, PUNCTUATION::Quest) {}
    };

} // namespace SENTENCE

#endif //_SENTENCE_H_