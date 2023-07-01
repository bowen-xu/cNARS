#include "../include/Interpreter.hpp"
#include <cmath>
#include <fmt/color.h>
#include <fmt/core.h>

using namespace INTERPRETER;

Interpreter INTERPRETER::interpreter = Interpreter();
using COMPOUND::Compound;
using STATEMENT::Statement;

auto color_term = fmt::fg(fmt::rgb(166, 217, 246));
auto color_angle = fmt::fg(fmt::rgb(104, 154, 199));
auto color_punct = fmt::fg(fmt::rgb(104, 154, 199));
auto color_parenthesis = fmt::fg(fmt::rgb(104, 154, 199));
auto color_seperator = fmt::fg(fmt::rgb(104, 154, 199));
auto color_copula = fmt::fg(fmt::rgb(193, 137, 191));
auto color_connector = fmt::fg(fmt::rgb(193, 137, 191));
auto color_percent = fmt::fg(fmt::rgb(77, 196, 172));
auto color_number = fmt::fg(fmt::rgb(181, 206, 168));
auto color_tense = fmt::fg(fmt::rgb(77, 196, 254));

string Interpreter::interpret(Term &term, bool colored)
{
    auto key = term.hash_value;
    string str_ret;

    if (term.is_var && term.type == TermType::ATOM)
    {
        int idx_var;
        if (term.is_ivar)
            idx_var = *term._vars_independent->indices[0];
        else if (term.is_dvar)
            idx_var = *term._vars_dependent->indices[0];
        else if (term.is_qvar)
            idx_var = *term._vars_query->indices[0];
        else
            throw std::runtime_error("Invalid case");
        auto &var = *(VARIABLE::Variable *)&term;
        auto prefix = VARIABLE::Repr[var.prefix];
        auto str = prefix + std::to_string(idx_var);
        if (colored)
        {
            return fmt::format(color_term, str);
        }
        else
        {
            return str;
        }
    }

    if (this->check(key))
    {
        /* If it has been existed, then directly get the interpretation by key. */
        if (term.type == TermType::ATOM && colored)
            return fmt::format(color_term, this->get(key));
        return this->get(key);
    }
    /* Otherwise, it has not been interpreted yet. Then interpret and store it.
     If the term is atomic, add the term into the dictionary. */
    if (term.type == TermType::ATOM)
    {
        // std::stringstream ss;
        // ss << std::hex << (int)&term;
        // return string(ss.str());
        if (colored)
            str_ret = fmt::format(color_term, fmt::format("{:x}", (long)(&term)));
        else
            str_ret = fmt::format("{:x}", (long)(&term));
    }
    else if (term.type == TermType::STATEMENT)
    {
        auto &stat = (Statement &)term;
        std::stringstream ss;
        auto str_subject = this->interpret(*stat.subject, colored);
        auto str_predicate = this->interpret(*stat.predicate, colored);
        auto &str_copula = COPULA::Repr[(int)stat.copula];

        if (colored)
        {
            // str_subject =
            auto str1 = fmt::format(color_angle, "<");
            // auto str2 = fmt::format(color_term, str_subject);
            auto str2 = fmt::format(fmt::format(color_term, "{{}}"), str_subject);
            auto str3 = fmt::format(color_copula, str_copula);
            // auto str4 = fmt::format(color_term, str_predicate);
            auto str4 = fmt::format(fmt::format(color_term, "{{}}"), str_predicate);
            auto str5 = fmt::format(color_angle, ">");
            str_ret = fmt::format("{}{} {} {}{}", str1, str2, str3, str4, str5);
        }
        else
            str_ret = fmt::format("<{} {} {}>", str_subject, str_copula, str_predicate);
    }
    else if (term.type == TermType::COMPOUND)
    {
        auto &cpmd = (Compound &)term;
        std::stringstream ss;
        auto &components = cpmd.components();
        auto str_conn = CONNECTOR::Repr[(int)cpmd.connector];
        auto last_it = components.end() - 1;

        auto append_strs = [components, this, colored](std::stringstream &_ss)
        {
            for (auto it = components.begin(); it != components.end(); it++)
            {
                auto &tm = **it;
                _ss << this->interpret(tm, colored);
                if (it != components.end() - 1)
                {
                    _ss << fmt::format(color_seperator, ", ");
                }
            }
        };

        if (colored)
        {

            if (cpmd.connector == CONNECTOR::Connector::ExtensionalSet)
            {
                ss << fmt::format(color_parenthesis, "{{");
                append_strs(ss);
                ss << fmt::format(color_parenthesis, "}}");
            }
            else if (cpmd.connector == CONNECTOR::Connector::IntensionalSet)
            {
                ss << fmt::format(color_parenthesis, "[");
                append_strs(ss);
                ss << fmt::format(color_parenthesis, "]");
            }
            else
            {
                ss << fmt::format(color_parenthesis, "(") << fmt::format(color_connector, str_conn) << fmt::format(color_seperator, ", ");
                append_strs(ss);
                ss << fmt::format(color_parenthesis, ")");
            }
        }
        else
        {
            if (cpmd.connector == CONNECTOR::Connector::ExtensionalSet)
            {
                ss << "{{";
                append_strs(ss);
                ss << "}}";
            }
            else if (cpmd.connector == CONNECTOR::Connector::IntensionalSet)
            {
                ss << "[";
                append_strs(ss);
                ss << "]";
            }
            else
            {
                ss << "(" << str_conn;
                append_strs(ss);
                ss << ")";
            }
        }
        str_ret = string(ss.str());
    }
    else
    {
        // TODO: raise exception
    }
    return str_ret;
}

string Interpreter::interpret(Task &task, bool colored)
{
    auto &budget = *task.budget;
    auto &sentence = *task.sentence;
    auto &punct = sentence.punct;
    auto &term = *sentence.term;
    auto key = term.hash_value;
    auto str_term = interpret(term, colored);

    float p = budget.priority;
    float d = budget.durability;
    float q = budget.quality;
    p = std::round((p >= 0 ? (p <= 1 ? p : 1) : 0) * 1000) / 1000;
    d = std::round((d >= 0 ? (d <= 1 ? d : 1) : 0) * 1000) / 1000;
    q = std::round((q >= 0 ? (q <= 1 ? q : 1) : 0) * 1000) / 1000;

    auto color_priority = fmt::bg(fmt::rgb(std::min(255, int(255 * p / 2 + 10)), 10, 10));
    auto color_durability = fmt::bg(fmt::rgb(10, std::min(255, int(255 * d / 2 + 10)), 10));
    auto color_quality = fmt::bg(fmt::rgb(10, 10, std::min(255, int(255 * q / 1.5 + 10))));

    string str_truth;
    string str_stamp;
    string str_punct;
    if (colored)
    {
        if (sentence.is_judgement())
        {
            const auto &truth = *((SENTENCE::Judgement &)sentence).truth;
            str_truth = fmt::format("{0}{1}{3}{2}{0}", fmt::format(color_percent, "%"), fmt::format(color_number, "{:.3f}", truth.f), fmt::format(color_number, "{:.3f}", truth.c), fmt::format(color_percent, ";"));
        }
        else if (sentence.is_goal())
        {
            auto &truth = *((SENTENCE::Goal &)sentence).desire;
            str_truth = fmt::format("{0}{1}{3}{2}{0}", fmt::format(color_percent, "%"), fmt::format(color_number, "{:.3f}", truth.f), fmt::format(color_number, "{:.3f}", truth.c), fmt::format(color_percent, ";"));
        }
        str_punct = fmt::format(color_punct, SENTENCE::PUNCTUATION::Repr[(int)(sentence.punct)]);
        str_stamp = sentence.stamp->is_eternal?"":fmt::format(color_tense, "{} ", TENSE::Repr[sentence.stamp->tense()]);

        return fmt::format("{}{}{} {}{} {}{}", fmt::format(color_priority, " {:.2f} ", p), fmt::format(color_durability, " {:.2f} ", d), fmt::format(color_quality, " {:.2f} ", q), str_term, str_punct, str_stamp, str_truth);
    }
    else
    {
        if (sentence.is_judgement())
        {
            auto &truth = *((SENTENCE::Judgement &)sentence).truth;
            str_truth = fmt::format("%{:.3f};{:.3f}%", truth.f, truth.c);
        }
        else if (sentence.is_goal())
        {
            auto &truth = *((SENTENCE::Goal &)sentence).desire;
            str_truth = fmt::format("%{:.3f};{:.3f}%", truth.f, truth.c);
        }
        str_punct = SENTENCE::PUNCTUATION::Repr[(int)(sentence.punct)];
        str_stamp = sentence.stamp->is_eternal?"":fmt::format( "{} ", TENSE::Repr[sentence.stamp->tense()]);

        return fmt::format("${:.2f};{:.2f};{:.2f}$ {}{} {}{}", p, d, q, str_term, str_punct, str_stamp, str_truth);
    }

    
}