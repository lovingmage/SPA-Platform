#ifndef TOKENIZER_H
#define TOKENIZER_H
///////////////////////////////////////////////////////////////////////
// Tokenizer.h - read words from a std::stream                       //
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
 * This package provides a public Toker class and private ConsumeState class.
 * Toker reads words from a std::stream, throws away whitespace and comments
 * and returns words from the stream in the order encountered.  Quoted
 * strings and certain punctuators and newlines are returned as single tokens.
 *
 * This is a new version, based on the State Design Pattern.  
 *
 * Build Process:
 * --------------
 * Required Files: Tokenizer.h, Tokenizer.cpp
 * Build Command: devenv Tokenizer.sln /rebuild debug
 *
 * Maintenance History:
 * --------------------
 * ver 0.4 : 84 Feb 2016
 * - Return quoted strings as single token.  Handle \" and \'correctly.
 * - Converting eatNewLine() to eatSpecialTokens() - see below
 * - Return [, ], {, }, (, ), <, >, :, ; as single character tokens
 * - Return <<, >>, +=, -=, *=, /=, :: as two character tokens
 * - Add setSpecialChars let users to define their single char and
 * - double char pair.
 * ver 0.3 : 31 Jan 2016
 * - fixed bug in ConsumeState::nextState() by returning a valid state
 *   pointer if all tests fail due to reaching end of file instead of
 *   throwing logic_error exception.
 * ver 0.2 : 29 Jan 2016
 * - fixed bug in EatCComment::eatChars()
 * - removed redundant statements assigning _pState in derived eatChars() 
 *   functions
 * - removed calls to nextState() in each derived eatChars() and fixed
 *   call to nextState() in ConsumeState::consumeChars()
 * ver 0.1 : 29 Jan 2016
 * - start up Tokenizer project
 *
 * Planned Additions and Changes:
 * ------------------------------
 * - none yet
 */
#include <iosfwd>
#include <string>
#include <vector>

namespace Scanner
{
  class ConsumeState;

  class Toker
  {
  public:
    Toker();
    ~Toker();
    bool attach(std::istream* pIn);
    std::string getTok();
    bool canRead();
	static void reset();
	static void setSpecialChars(std::vector<std::string> OneCharList, std::vector<std::string> PairCharList);
  private:
    ConsumeState* pConsumer;
  };
}
#endif

