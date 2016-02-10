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

//----< Test for Tokenizer function >--------------------------------

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


//----< Test the function of SemiExpression function >-----------------
//----< 
//			Note :
//				 During this test, the testing process will also testing the
//				 interface methods in ITokenCollection. The specificl testing
//				 methods are listed as below:
//
//			     1. Testing for TrimFront(), remove(), pushback() operator[],
//					length() and isComment():
//				 --> When implemente get() method to extract # at the 1st of each
//					 newline will call all the aforementioned method. Thus the 
//				     testing for all these methods will test along with get()
//
//				2. Testing show(), clear() :
//				--> When each time call get(), it will call the two methods, thus
//					the testing of aforementioned methods along with testing get()
//      >------

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
	Toker::reset();
	return 0;
}

//----< Test the function of SemiExpression on Cpp file>-------------

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
	Toker::reset();
	return 0;
}

//----< Test the function of SetSpecialChars >-------------------------

int testSetSpecial(std::string fileSpecSemi) {
	Toker token_set;
	std::fstream insemiset(fileSpecSemi);
	std::vector<std::string> SpecialCharList =
	{// Do not Change On Single Char List, Keep it
		"\n", "<", ">", "{", "}", "[", "]", "(", ")", ":", "=", "+", "-", "*"
	};
	std::vector<std::string> SpecialPairList =
	{// Remove some Char Pairs and only remains << >> and ::
		"<<", ">>", "::"
	};
	token_set.setSpecialChars(SpecialCharList, SpecialPairList);

	if (!insemiset.good())
	{
		std::cout << "\n  can't open " << fileSpecSemi << "\n\n";
		return 1;
	}

	token_set.attach(&insemiset);
	while (insemiset.good())
	{
		std::string tok = token_set.getTok();
		if (tok == "\n")
			tok = "newline";
		std::cout << "\n -- " << tok;
	}
	std::cout << std::endl;
	std::cout << "Only << >> and :: remains as special char pairs !" << std::endl;
	Toker::reset();
	return 0;
}

int main()
{
	std::cout << "===================== Automatic Test Suite Started Here ===============================" << std::endl << std::endl << std::endl;
	std::cout << "====================== Part #1 Test Tokenizer Package =================================" << std::endl << std::endl << std::endl;
	std::string fileSpec = "../Test Case/alphanumeric tokens.txt";
	if (testtoker(fileSpec)) { return 1; }
	std::cout << "\n\n\n";

	std::cout << "=========================== Part #2 SemiExp Testing ===================================" << std::endl << std::endl;
	std::string fileSpecSemi = "../Test Case/TestSemiExp.txt";
	if (testSemiExp(fileSpecSemi)) { return 1; }

	std::cout << "================= Part #3 General SemiExp Testing on Source Code ======================" << std::endl << std::endl;
	std::string fileSpecSemicpp = "../Test Case/Tokenizer.cpp";
	if (testSemiExpOnCpp(fileSpecSemicpp)) { return 1; }

	std::cout << "======================= Part #4 Testing reset Special Chars ===========================" << std::endl << std::endl;
	std::string fileSpecSemiset = "../Test Case/testset.txt";
	if (testSetSpecial(fileSpecSemiset)) { return 1; }

	
	system("pause");
	return 0;

}