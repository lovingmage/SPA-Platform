///////////////////////////////////////////////////////////////////////
// SemiExpression.cpp - collect tokens for analysis                  //
// ver 3.1                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CSE687 - Object Oriented Design    //
// Author:      Jim Fawcett, Syracuse University, CST 4-187          //
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

//std::string LAST_TOKEN = "newline";
//std::string CURRENT_TOKEN = "newline";

SemiExp::SemiExp(Toker* pToker) : _pToker(pToker) {
    CURRENT_TOKEN = _pToker->getTok();
}

bool SemiExp::get()
{
  _tokens.clear();
  while (true)
  {
    std::string token = CURRENT_TOKEN
    if (token == "")
      break;
    _tokens.push_back(token);
      
    CURRENT_TOKEN = _pToker->getTok();

    if ((token == "Public" || token == "Private" || token == "Protect")&&CURRENT_TOKEN == ":"){
        LAST_TOKEN = CURRENT_TOKEN;
        _tokens.push_back(CURRENT_TOKEN);
        CURRENT_TOKEN = _pToker-> getTok();
        return true;
      }
      
    if (token == "#" && LAST_TOKEN = "newline"){
          while (token != "newline") {
              token = _pToker->getTok;
              _tokens.push_back(token);
          }
        LAST_TOKEN = "newline";
        CURRENT_TOKEN = _pToker->getTok();
        return true;
      }
    
    //_tokens.push_back(token);
      
      if ((token = _pToker -> getTok()) == "for"){
          while(token != ")"){
              token = _pToker->getTok();
              _tokens.push_back(token);
          }
      }
//***********************************************************************
      

      if (token == "{" || token == "}"){
          LAST_TOKEN = token;
          return true;
  }
  return false;
}

Token SemiExp::operator[](size_t n)
{
  if (n < 0 || n >= _tokens.size())
    throw(std::invalid_argument("index out of range"));
  return _tokens[n];
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

int main()
{
  Toker toker;
  std::string fileSpec = "../Tokenizer/Tokenizer.cpp";
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
  return 0;
}