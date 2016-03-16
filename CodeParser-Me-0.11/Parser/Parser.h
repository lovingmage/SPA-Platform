#ifndef PARSER_H
#define PARSER_H
/////////////////////////////////////////////////////////////////////
//  Parser.h - package headfile for Parser                         //
//  ver 1.0                                                        //
// Language:    C++, Visual Studio 2015                            //
// Application: Parser file , CIS687 Object Oriented  Design       //
//                                                                 //
// Author:		Chenghong Wang, Syracuse University				   //
//				cwang132@syr.edu								   //
// Source:        Jim Fawcett, CST 4-187, Syracuse University      //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module defines a Parser class.  Its instances collect 
  semi-expressions from a file for analysis.  Analysis consists of
  applying a set of rules to the semi-expression, and for each rule
  that matches, a set of actions is invoked.

  Public Interface:
  =================
  Toker t(someFile);              // create tokenizer instance
  SemiExp se(&t);                 // create a SemiExp attached to tokenizer
  Parser parser(se);              // now we have a parser
  Rule1 r1;                       // create instance of a derived Rule class
  Action1 a1;                     // create a derived action
  r1.addAction(&a1);              // register action with the rule
  parser.addRule(&r1);            // register rule with parser
  while(se.getSemiExp())          // get semi-expression
    parser.parse();               //   and parse it

  Build Process:
  ==============
  Required files
    - Parser.h, Parser.cpp, SemiExp.h, SemiExp.cpp,
      tokenizer.h, tokenizer.cpp,
      ActionsAndRules.h, ActionsAndRules.cpp,
      ConfigureParser.h, ConfigureParser.cpp
  Build commands (either one)
    - devenv Parser.sln
    - cl /EHsc /DTEST_PARSER Parser.cpp SemiExp.cpp Tokenizer.cpp \
         ActionsAndRules.cpp ConfigureParser.cpp /link setargv.obj

  Maintenance History:
  ====================
  ver 1.0 : 05 March 2016
  - first release

*/

#include <string>
#include <iostream>
#include <vector>
#include "../SemiExp/itokcollection.h"

///////////////////////////////////////////////////////////////
// abstract base class for parsing actions
//   - when a rule succeeds, it invokes any registered action

class Parser;

class IBuilder
{
public:
  virtual ~IBuilder() {}
  virtual Parser* Build()=0;
};

///////////////////////////////////////////////////////////////
// abstract base class for parsing actions
//   - when a rule succeeds, it invokes any registered action

class IAction
{
public:
  virtual ~IAction() {}
  virtual void doAction(ITokCollection*& pTc)=0;
};

///////////////////////////////////////////////////////////////
// abstract base class for parser language construct detections
//   - rules are registered with the parser for use

class IRule
{
public:
  virtual ~IRule() {}
  void addAction(IAction* pAction);
  void doActions(ITokCollection*& pTc);
  virtual bool doTest(ITokCollection*& pTc)=0;
protected:
  std::vector<IAction*> actions;
};

class Parser
{
public:
  Parser(ITokCollection* pTokCollection);
  ~Parser();
  void addRule(IRule* pRule);
  bool parse();
  bool next();
private:
  ITokCollection* pTokColl;
  std::vector<IRule*> rules;
};

inline Parser::Parser(ITokCollection* pTokCollection) : pTokColl(pTokCollection) {}

inline Parser::~Parser() {}

#endif
