#ifndef CONFIGUREPARSER_H
#define CONFIGUREPARSER_H
/////////////////////////////////////////////////////////////////////
//  ConfigureParser.h - builds and configures parsers              //
//  ver 1.1                                                        //
// Language:    C++, Visual Studio 2015                            //
// Application: Parser Config , CIS687 Object Oriented  Design     //
//                                                                 //
// Author:		Chenghong Wang, Syracuse University				   //
//				cwang132@syr.edu								   //
// Source:        Jim Fawcett, CST 4-187, Syracuse University      //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
  Module Operations: 
  ==================
  This module builds and configures parsers.  It builds the parser
  parts and configures them with application specific rules and actions.

  Public Interface:
  =================
  ConfigParseToConsole conConfig;
  conConfig.Build();
  conConfig.Attach(someFileName);

  Required Files:
  ===============
  SemiExp.h, Tokenizer.h, Parser.h, ActionsAndRules.h, ConfigureParser.cpp,
  ConfigureParser.h, Parser.cpp, ActionsAndRules.cpp, 
  ConfigureParser.cpp, ConfigureParser.h, SemiExp.cpp Tokenizer.cpp
  SemiExp.h Tokenizer.h
  Build commands (either one)
  - devenv ConfigureParser.sln
  - cl /EHsc /DTEST_PARSER Parser.cpp SemiExp.cpp Tokenizer.cpp \
  ActionsAndRules.cpp ConfigureParser.cpp /link setargv.obj

  Maintenance History:
  ====================
  ver 1.1 : 08 March 2016
  - Add new rules detect scope in ConfigureParser
  ver 1.0 : 05 March 2016
  - first release

*/

//
#include <fstream>
#include "Parser.h"
#include "../SemiExp/SemiExp.h"
#include "../Tokenizer/Tokenizer.h"
#include "ActionsAndRules.h"

///////////////////////////////////////////////////////////////
// build parser that writes its output to console

class ConfigParseToConsole : IBuilder
{
public:
  ConfigParseToConsole() {};
  ~ConfigParseToConsole();
  bool Attach(const std::string& name, bool isFile=true);
  Parser* Build();
  std::map<std::string, std::string>& getType();

private:
  // Builder must hold onto all the pieces

  std::ifstream* pIn;
  Scanner::Toker* pToker;
  Scanner::SemiExp* pSemi;
  Parser* pParser;
  Repository* pRepo;

  // add Rules and Actions

  BeginningOfScope* pBeginningOfScope;
  HandlePush* pHandlePush;
  EndOfScope* pEndOfScope;
  HandlePop* pHandlePop;
  ScopeDefinition* pScopeDefinition;
  FunctionDefinition* pFunctionDefinition;
  PushFunction* pPushFunction;
  PushScope* pPushScope;
  PrintScope* pPrintScope;
  PrintFunction* pPrintFunction;


  // prohibit copies and assignments

  ConfigParseToConsole(const ConfigParseToConsole&) = delete;
  ConfigParseToConsole& operator=(const ConfigParseToConsole&) = delete;
};


#endif
