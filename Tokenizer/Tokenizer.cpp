/////////////////////////////////////////////////////////////////////
// Tokenizer.cpp - read words from a std::stream                   //
// ver 3.2                                                         //
// Language:    C++, Visual Studio 2015                            //
// Application: Parser component, CSE687 - Object Oriented Design  //
// Author:      Jim Fawcett, Syracuse University, CST 4-187        //
//              jfawcett@twcny.rr.com                              //
/////////////////////////////////////////////////////////////////////
/*
  Helper code that does not attempt to handle all tokenizing
  special cases like escaped characters.
*/
#include "Tokenizer.h"
#include <iostream>
#include <cctype>
#include <string>

namespace Scanner
{
  class ConsumeState
  {
  public:
    ConsumeState();
    virtual ~ConsumeState();
    void attach(std::istream* pIn) { _pIn = pIn; }
    virtual void eatChars() = 0;
    void consumeChars() {
      _pState->eatChars();
      _pState = nextState();
    }
    bool canRead() { return _pIn->good(); }
    std::string getTok() { return token; }
    bool hasTok() { return token.size() > 0; }
    ConsumeState* nextState();
  protected:
    static std::string token;
    static std::istream* _pIn;
    static int prevChar;
    static int currChar;
    static ConsumeState* _pState;
    static ConsumeState* _pEatCppComment;
    static ConsumeState* _pEatCComment;
    static ConsumeState* _pEatWhitespace;
    static ConsumeState* _pEatPunctuator;
	static ConsumeState* _pEatSpecialSingleChars;
	static ConsumeState* _pEateSpecialCharPairs;
	static ConsumeState* _pEateQoutedString;
    static ConsumeState* _pEatAlphanum;
    static ConsumeState* _pEatNewline;
  };
}

using namespace Scanner;

std::string ConsumeState::token;
std::istream* ConsumeState::_pIn;
int ConsumeState::prevChar;
int ConsumeState::currChar;
ConsumeState* ConsumeState::_pState = nullptr;
ConsumeState* ConsumeState::_pEatCppComment = nullptr;
ConsumeState* ConsumeState::_pEatCComment = nullptr;
ConsumeState* ConsumeState::_pEatWhitespace = nullptr;
ConsumeState* ConsumeState::_pEatPunctuator = nullptr;
ConsumeState* ConsumeState::_pEatSpecialSingleChars = nullptr;
ConsumeState* ConsumeState::_pEateSpecialCharPairs = nullptr;
ConsumeState* ConsumeState::_pEateQoutedString = nullptr;
ConsumeState* ConsumeState::_pEatAlphanum = nullptr;
ConsumeState* ConsumeState::_pEatNewline;

void testLog(const std::string& msg);

ConsumeState* ConsumeState::nextState()
{
  if (!(_pIn->good())) { return nullptr; }
  int chNext = _pIn->peek();

  if (std::isspace(currChar) && currChar != '\n'){
		testLog("state: eatWhitespace");
		return _pEatWhitespace;
	}

  if (currChar == '/' && chNext == '/')
  {
    testLog("state: eatCppComment");
    return _pEatCppComment;
  }
  if (currChar == '/' && chNext == '*')
  {
    testLog("state: eatCComment");
    return _pEatCComment;
  }

  if (currChar == '\n')
  {
    testLog("state: eatNewLine");
    return _pEatNewline;
  }
  if (std::isalnum(currChar))
  {
    testLog("state: eatAlphanum");
    return _pEatAlphanum;
  }
  if (ispunct(currChar))
  {
	  //This place is self modified function
	  if (currChar == 34 || currChar == 36)
	  {
		  testLog("state: eatQoutedString");
		  return _pEateQoutedString;
	  }
	  if (currChar == '<' || currChar == '>' || currChar == '[' || currChar == ']' || currChar == ':' || currChar == '(' || currChar == ')' || currChar == '{' || currChar == '}' || currChar == '=' || currChar == '+' || currChar == '-' || currChar == '*' || currChar == '/')
	  {
		  if ((currChar == '<' && chNext == '<') || (currChar == '>' && chNext == '>') || (currChar == ':' && chNext == ':') || (currChar == '+' && chNext == '+') || (currChar == '-' && chNext == '-') || (currChar == '=' && chNext == '=') || (currChar == '+' && chNext == '=') || (currChar == '-' && chNext == '=') || (currChar == '*' && chNext == '=') || (currChar == '/' && chNext == '=')) {
			  testLog("state: eatSpecialCharPairs");
			  return _pEateSpecialCharPairs;
		  }
		  else {
			  testLog("state: eatSpecialStringChars");
			  return _pEatSpecialSingleChars;
		  }
	  }
	  //Self Modified Part End
	testLog("state: eatPunctuator");
    return _pEatPunctuator;
  }
  if (!_pIn->good())
    return _pEatWhitespace;
  throw(std::logic_error("invalid type"));
}



class EatWhitespace : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating whitespace";
    do {
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (std::isspace(currChar) && currChar != '\n');
  }
};

class EatCppComment : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating C++ comment";
    do {
	  token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (currChar != '\n');
  }
};

class EatCComment : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating C comment";
    do {
	token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (currChar != '*' || _pIn->peek() != '/');
	//currChar = _pIn->get();
	token += currChar;
    currChar = _pIn->get();
	token += currChar;
  }
};

class EatPunctuator : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating punctuator";
    do {
      token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (ispunct(currChar));
  }
};

// Self Modified Code Part--EatQoutedString
class EatQoutedString : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		do {
			token += currChar;
			if (!_pIn->good())
				return;
			currChar = _pIn->get();
		} while (currChar != 34 && currChar != 36);
		token += currChar;
		currChar = _pIn->get();
		
		
	}
};

class EatSpecialStringChars : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		token += currChar;
		if (!_pIn->good())
			return;
		currChar = _pIn->get();
	}
};

class EatSpecialCharPairs : public ConsumeState
{
public:
	virtual void eatChars()
	{
		token.clear();
		int Jishujun = 2;
		do {
			token += currChar;
			if (!_pIn->good())
				return;
			currChar = _pIn->get();
		} while (--Jishujun);
	}
};
//Self Modified Part Ended

class EatAlphanum : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating alphanum";
    do {
      token += currChar;
      if (!_pIn->good())  // end of stream
        return;
      currChar = _pIn->get();
    } while (isalnum(currChar));
  }
};

class EatNewline : public ConsumeState
{
public:
  virtual void eatChars()
  {
    token.clear();
    //std::cout << "\n  eating alphanum";
    token += currChar;
    if (!_pIn->good())  // end of stream
      return;
    currChar = _pIn->get();
  }
};

ConsumeState::ConsumeState()
{
  static bool first = true;
  if (first)
  {
    first = false;
    _pEatAlphanum = new EatAlphanum();
    _pEatCComment = new EatCComment();
    _pEatCppComment = new EatCppComment();
    _pEatPunctuator = new EatPunctuator();
	_pEatSpecialSingleChars = new EatSpecialStringChars();
	_pEateSpecialCharPairs = new EatSpecialCharPairs();
	_pEateQoutedString = new EatQoutedString();
    _pEatWhitespace = new EatWhitespace();
    _pEatNewline = new EatNewline();
    _pState = _pEatWhitespace;
  }
}

ConsumeState::~ConsumeState()
{
  static bool first = true;
  if (first)
  {
    first = false;
    delete _pEatAlphanum;
    delete _pEatCComment;
    delete _pEatCppComment;
    delete _pEatPunctuator;
	delete _pEatSpecialSingleChars;
	delete _pEateSpecialCharPairs;
	delete _pEateQoutedString;
    delete _pEatWhitespace;
    delete _pEatNewline;
  }
}

Toker::Toker() : pConsumer(new EatWhitespace()) {}

Toker::~Toker() { delete pConsumer; }

bool Toker::attach(std::istream* pIn)
{
  if (pIn != nullptr && pIn->good())
  {
    pConsumer->attach(pIn);
    return true;
  }
  return false;
}

std::string Toker::getTok()
{
  while(true) 
  {
    if (!pConsumer->canRead())
      return "";
    pConsumer->consumeChars();
    if (pConsumer->hasTok())
      break;
  }
  return pConsumer->getTok();
}

bool Toker::canRead() { return pConsumer->canRead(); }

void testLog(const std::string& msg)
{
#ifdef TEST_LOG
  std::cout << "\n  " << msg;
#endif
}

//----< test stub >--------------------------------------------------

#ifdef TEST_TOKENIZER

#include <fstream>

int main()
{
  //std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
  //std::string fileSpec = "../Tokenizer/Tokenizer.h";
  std::string fileSpec = "../Tokenizer/Test.txt";

  std::ifstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open " << fileSpec << "\n\n";
    return 1;
  }
  Toker toker;
  toker.attach(&in);
  while (in.good())
  {
    std::string tok = toker.getTok();
    if (tok == "\n")
      tok = "newline";
    std::cout << "\n -- " << tok;
  }
  std::cout << "\n\n";
  system("pause");
  return 0;
}
#endif
