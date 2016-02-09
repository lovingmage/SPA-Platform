///////////////////////////////////////////////////////////////////////
// SemiExpression.cpp - collect tokens for analysis                  //
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
#include "SemiExp.h"
#include "../Tokenizer/Tokenizer.h"

using namespace Scanner;

SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {}

bool SemiExp::get()
{
  if (_pToker == nullptr)
  throw(std::logic_error("no Toker reference"));
  _tokens.clear();
  while (true)
  {
    std::string token = _pToker->getTok();
    if (token == "")
      break;
	if (isComment(token))
		continue;

	_tokens.push_back(token);

	if (token == "\n" && find("#") != length()) {
		trimFront();
		if (_tokens[0] == "#") {
			return true;
		}	
	}

	if (token == "private" || token == "public" || token == "protected") {
		token = _pToker->getTok();
		if (token == ":") {
			_tokens.push_back(token);
			return true;
		}
		if (token == "{" || token == "}" || token == ";") {
			_tokens.push_back(token);
			return true;
		}
		else { _tokens.push_back(token); }
		
	}
	if (token == "for") {
		token = _pToker->getTok();
		while (token != "{") {
			_tokens.push_back(token);
			token = _pToker->getTok();
		}
		_tokens.push_back(token);
	}
   
	if (token == "{" || token == "}" || token == ";")
      return true;
  }
  return false;
}

//----< remove leading newlines >------------------------------

void SemiExp::trimFront()
{
	while (_tokens.size() > 0 && (_tokens[0] == "\n" || _tokens[0] == ""))
		remove(0);
}

Token SemiExp::operator[](size_t n)
{
  if (n < 0 || n >= _tokens.size())
    throw(std::invalid_argument("index out of range"));
  return _tokens[n];
}

//----< remove tok if found in semi-expression >---------------

bool SemiExp::remove(const std::string& tok)
{
	std::vector<std::string>::iterator it; 
	it = std::find(_tokens.begin(), _tokens.end(), tok);
	if (it != _tokens.end())
	{
		_tokens.erase(it);
		return true;
	}
	return false;
}
//----< remove tok at specified indes >------------------------

bool SemiExp::remove(size_t i)
{
	if (i<0 || _tokens.size() <= i)
		return false;
	std::vector<std::string>::iterator it = _tokens.begin();
	_tokens.erase(it + i);
	return true;
}

bool SemiExp::isComment(const std::string& tok)
{
	if (tok.length() < 2) return false;
	if (tok[0] != '/') return false;
	if (tok[1] == '/' || tok[1] == '*') return true;
	return false;
}

size_t SemiExp::find(const std::string& tok)
{
	for (size_t i = 0; i<length(); ++i)
		if (tok == _tokens[i])
			return i;
	return length();
}

size_t SemiExp::length()
{
  return _tokens.size();
}

void SemiExp::show()
{
  std::cout << "\n  ";
  for (auto token : _tokens)
    if(token != "\n")
      std::cout << token << " ";
  std::cout << "\n";
}

void SemiExp::clear() { _tokens.clear(); }

void SemiExp::push_back(const std::string& tok)
{
	_tokens.push_back(tok);
}


#ifdef TEST_SEMIEXP
int main()
{
  Toker toker;
  std::string fileSpec = "./test2.txt";
  std::fstream in(fileSpec);
  if (!in.good())
  {
    std::cout << "\n  can't open file " << fileSpec << "\n\n";
    return 1;
  }
  toker.attach(&in);

  SemiExp semi(&toker);
  while(semi.get())
  {
    std::cout << "\n  -- semiExpression --";
    semi.show();
  }
  /*
     May have collected tokens, but reached end of stream
     before finding SemiExp terminator.
   */
  if (semi.length() > 0)
  {
    std::cout << "\n  -- semiExpression --";
    semi.show();
    std::cout << "\n\n";
  }
  system("pause");
  return 0;
}
#endif