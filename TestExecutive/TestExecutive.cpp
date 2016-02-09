#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "./itokcollection.h"

using namespace Scanner;

int main()
{
	std::string fileSpec = "../SemiExp/Test.txt";

	std::ifstream in(fileSpec);
	if (!in.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		return 1;
	}
	Toker toker_test_token;
	toker_test_token.attach(&in);
	while (in.good())
	{
		std::string tok = toker_test_token.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	std::cout << "\n\n";

	Toker toker;
	std::string fileSpecSemi = "../SemiExp/test.txt";
	std::fstream insemi(fileSpecSemi);
	if (!insemi.good())
	{
		std::cout << "\n  can't open file " << fileSpecSemi << "\n\n";
		return 1;
	}
	toker.attach(&insemi);

	SemiExp semi(&toker);
	while (semi.get())
	{
		std::cout << "\n  -- semiExpression --";
		semi.show();
	}

	if (semi.length() > 0)
	{
		std::cout << "\n  -- semiExpression --";
		semi.show();
		std::cout << "\n\n";
	}
	system("pause");
	return 0;

}