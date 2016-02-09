///////////////////////////////////////////////////////////////////////
// TestExecutive.cpp - automatic test suite	                         //
// ver 0.1                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CIS687 - Object Oriented Design    //
// Author:		Chenghong Wang, Syracuse University					 //
//				cwang132@syr.edu									 //
//																	 //
// Source:      Jim Fawcett, CIS-687 SP16 Help Code Pr1	             //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////


#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <exception>
#include "TestExecutive.h"

using namespace Scanner;


int testtoker(std::string fileSpec) {
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
	Toker::reset();
	return 0;
}

int testsetspecial(std::string fileSpec) {
	Toker toker_set_special;
	std::fstream inset(fileSpec);
	toker_set_special.attach(&inset);
	std::string newSpecialChars = "., :, +, +=, \n { }";
	toker_set_special.setSpecialTokens(newSpecialChars);

	if (!inset.good())
	{
		std::cout << "\n  can't open " << fileSpec << "\n\n";
		return 1;
	}


	while (inset.good())
	{
		std::string tok = toker_set_special.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	Toker::reset();
	return 0;
}

int testSemiExp(std::string fileSpecSemi) {
	Toker toker;
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
	return 0;
}

int testSemiExpOnCpp(std::string fileSpecSemi) {
	Toker tokercpp;
	std::fstream insemicpp(fileSpecSemi);
	if (!insemicpp.good())
	{
		std::cout << "\n  can't open file " << fileSpecSemi << "\n\n";
		return 1;
	}
	tokercpp.attach(&insemicpp);

	SemiExp semi(&tokercpp);
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
	return 0;
}

int main()
{
	std::cout << "===================== Automatic Test Suite Started Here ===============================" << std::endl << std::endl << std::endl;
	std::cout << "===================== Part #1 Test Tokenizer Package =================================" << std::endl << std::endl << std::endl;
	std::string fileSpec = "../Test Case/alphanumeric tokens.txt";
	if (testtoker(fileSpec)) { return 1; }
	std::cout << "\n\n\n";

	std::cout << "=========================== Part #2 SemiExp Testing ===================================" << std::endl << std::endl;
	std::string fileSpecSemi = "../Test Case/TestSemiExp.txt";
	if (testSemiExp(fileSpecSemi)) { return 1; }

	std::cout << "================= Part #3 General SemiExp Testing on Source Code ======================" << std::endl << std::endl;
	std::string fileSpecSemicpp = "../Test Case/Tokenizer.cpp";
	if (testSemiExpOnCpp(fileSpecSemicpp)) { return 1; }

	std::cout << "===================== Part #3 Test Set Special Chars =================================" << std::endl << std::endl;
	std::cout << "[+]Set the special two string as \"., :, ++, +=, \n{}\" " << std::endl;
	std::string fileSpecSet = "../Test Case/setspecial.txt";
	if (testsetspecial(fileSpecSet)) { return 1; }
	std::cout << "\n\n\n";
	
	system("pause");
	return 0;

}