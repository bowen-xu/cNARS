#include "Interpreter/include/Interpreter.hpp"
#include "Narsese/Parser/NarseseParser.h"
#include "Narsese/include/Narsese.h"
#include "Narsese/include/Term.h"
#include "Narsese/include/Term.inl"
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
	auto term = TERM::Term::create();
	std::cout << term.__repr__() << std::endl;
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