#include "Interpreter/include/Interpreter.hpp"
#include "Narsese/Parser/NarseseParser.h"
#include "Narsese/Parser/generate.h"
#include "Narsese/include/Statement.h"
#include "Narsese/include/Task.h"
#include <string>
#include <vector>
#include <memory>

using INTERPRETER::interpreter;
using TASK::Task;

// using namespace PARSER;
using NARSESEPARSER::NarseseParser;

int main(int argc, char **argv)
{
	auto parser = std::shared_ptr<NarseseParser>(new NarseseParser);

	printf("go:\n");

	auto test_cases = std::vector<const char*>{
		"<robin-->bird>.",
		"(&&, A, B).",
		"(&&, A1, B1).",
		"(&&, A2, B2).",
	};

	for (int i = 0; i < test_cases.size(); i++)
	{
		std::string input(test_cases[i]);
		auto task = parser->parse_task(input);
		// task.__repr__(nullptr);
		auto str = interpreter.interpret(*task);
		printf("%s\n", str.c_str());
	}

	return 0;
}

// #include <stdio.h>
// #include <iostream>
// #include <functional>
// #include <unordered_set>
// #include "Narsese/include/Term.h"
// #include "Narsese/include/Variable.h"
// #include "Narsese/include/Statement.h"
// #include "Narsese/include/Budget.h"
// #include "Narsese/Parser/Parser.h"

// using BUDGET::Budget;
// using STATEMENT::Statement;
// using TERM::Term;
// using TERM::TermType;
// using VARIABLE::Variable;

// using std::unordered_set;

// using std::cout;
// using std::endl;
// using std::hash;

// using std::string;

// int main()
// {
//     // try {
//     //     ASTNode* out_node;
//     //     PhraseParseOrDie(input, ArithmeticGrammar1(), qi::space, out_node);

//     //     std::cout << "evaluate() = " << out_node->evaluate() << std::endl;
//     //     delete out_node;
//     // }
//     // catch (std::exception& e) {
//     //     std::cout << "EXCEPTION: " << e.what() << std::endl;
//     // }

//     // printf("hello world!\n");
//     // Term term((char*)"bird", true);
//     // cout << term.word << endl;
//     // cout << term.hash_value << endl;
//     // Term term2((char*)"bird", true);
//     // cout << term2.word << endl;
//     // cout << term2.hash_value << endl;
//     // Statement stat(Term((char*)"robin"), COPULA::Inheritance, Term((char*)"bird"));
//     // cout << stat.word << endl;
//     // cout << string(term) << endl;
//     // Variable var(VARIABLE::Independent, "x");
//     // cout << string(var) << endl;
//     // auto stat1 = Statement(Statement(Variable(VARIABLE::Independent, "x"), COPULA::Inheritance, Term("bird")), COPULA::Implication, Statement(Variable(VARIABLE::Independent, "x"), COPULA::Inheritance, Term("animal")));
//     // cout << string(stat1) << endl;
//     // auto budget = Budget();
//     // cout << sizeof(budget) << endl;

//     cout << "done." << endl;

//     return 0;
// }