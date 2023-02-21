#include <string>
#include "Narsese/Parser/NarseseParser.h"
#include "Narsese/include/Task.h"
#include "Narsese/include/Statement.h"
#include "Narsese/Parser/generate.h"

using TASK::Task;

// using namespace PARSER;
using NARSESEPARSER::NarseseParser;
int main( int argc, char** argv )
{
	// GENERATE::generate();
	// return 0;
#define UNICCMAIN_SILENT		1
#define UNICCMAIN_ENDLESS		2
#define UNICCMAIN_LINEMODE		4
#define UNICCMAIN_SYNTAXTREE	8
#define UNICCMAIN_AUGSYNTAXTREE	16

	char*				opt;
	int					flags	= 0;
	NarseseParser*	parser = new NarseseParser;

#ifdef LC_ALL
	setlocale( LC_ALL, "" );
#endif

	printf("go:\n");

	/* Get command-line options */
	flags |= UNICCMAIN_SILENT;\
	flags |= UNICCMAIN_LINEMODE;

	const char* test_cases[] = {
		"<robin-->bird>.",
		"(&&, A, B).",
	};
	std::string input(test_cases[1]);
	
	for (int i=0; i<1; i++)
	{
		Task& task = *((Task*)parser->parse_string(input));
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