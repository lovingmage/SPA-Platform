#ifndef SEMIEXPRESSION_H
#define SEMIEXPRESSION_H
///////////////////////////////////////////////////////////////////////
// SemiExpression.h - collect tokens for analysis                    //
// ver 0.4                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CIS687 - Object Oriented Design    //
// Author:		Chenghong Wang, Syracuse University					 //
//				cwang132@syr.edu									 //
//																	 //
// Source:      Jim Fawcett, CIS-687 SP16 Help Code Pr1	             //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a public SemiExp class that collects and makes
* available sequences of tokens.  SemiExp uses the services of a Toker
* class to acquire tokens.  Each call to SemiExp::get() returns a 
* sequence of tokens that ends in {.  The full set of terminators have
* updated, it will terminate at {, }, ;, and '\n' if the line begins 
* with #.
*
* This is a new version for Chenghong Wang's programming submission
* for Project #1.
*
* Build Process:
* --------------
* Required Files: 
*   SemiExp.h, SemiExp.cpp, Tokenizer.h, Tokenizer.cpp, itokcollection.h
* 
* Build Command: devenv SemiExp.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 0.4 : 05 Feb 2016
* - Add the function to extract one token when a newline start with '#'
* -	Fixed the bugs when perform ConsumeState, pointers problems
* - Add the function to handle the key word public, private and protected
* - Implement the methods defined in interface ITOCKcollection.
* ver 0.3 : 03 Feb 2016
* - Add the function to support for loops, which will keep the semicolons
*	within the for loops.
* - added default argument for Toker pointer to nullptr so SemiExp
*   can be used like a container of tokens.
* - if pToker is nullptr then get() will throw logic_error exception
* ver 0.2 : 31 Jan 2016
* - Update new terminators contains {,} and ;
* - fixed bug in termination due to continually trying to read
*   past end of stream if last tokens didn't have a semiExp termination
*   character
* - Handled the bug when finishing SemiExp the Toker still remains,
*	Add a new methhod in Class Toker called reset(), which can reset
*	The class of Toker.
* ver 0.1 : 29 Jan 2016
* - built for Pr1 Submission, source Jim Fawcett's Help Code for Pr1 SP
*   2016
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "../TestExecutive/itokcollection.h"


namespace Scanner
{
  using Token = std::string;

  class SemiExp : public ITokCollection
  {
  public:
    SemiExp(Toker* pToker = nullptr);
    SemiExp(const SemiExp&) = delete;
    SemiExp& operator=(const SemiExp&) = delete;
    bool get();
    Token operator[](size_t n);
    size_t length();
	bool isComment(const std::string& tok);
	size_t find(const std::string& tok);
	bool remove(const std::string& tok);
	bool remove(size_t i);
    void show();
	void toLower();
	void trimFront();
	void clear();
	void push_back(const std::string& tok);
	std::string CURRENT_TOKEN;
	std::string LAST_TOKEN = "newline";
  private:
    std::vector<Token> _tokens;
    Toker* _pToker;
  };
}

#endif
