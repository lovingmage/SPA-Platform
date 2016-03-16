#ifndef METRIC_H
#define METRIC_H
/////////////////////////////////////////////////////////////////////
//  MetricAnalysis.h   - MetricAnalysis Package Headerfile         //
//  ver 1.0                                                        //
// Language:    C++, Visual Studio 2015                            //
// Application:	MetricExecutive , CIS687 Object Oriented  Design   //
//                                                                 //
// Author:		Chenghong Wang, Syracuse University				   //
//				cwang132@syr.edu								   //
// Source:        Jim Fawcett, CST 4-187, Syracuse University      //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is used to analysis specific source code, analysis the 
scope and attach them int abstrac syntax tree structure.

Public Interface:
=================
void doAnalysis();                            //Perform Analysis
void attachFile(std::string analyfile);       //Attach File

Build Process:
==============
Required files
- Parser.h, Parser.cpp, SemiExp.h, SemiExp.cpp,
Tokenizer.h, Tokenizer.cpp,
ActionsAndRules.h, ActionsAndRules.cpp,
ConfigureParser.h, ConfigureParser.cpp,
FileSystem.h, FileSystem.cpp,
FileMgr.h, FileMgr.cpp,
MetricAnalysis.h, MetricAnalysis.cpp

Build commands (either one)
- devenv MetricAnalysis.sln
- cl /EHsc /DTEST_PARSER MetricAnalysis.cpp Parser.cpp SemiExp.cpp Tokenizer.cpp \
ActionsAndRules.cpp ConfigureParser.cpp FileSystem.cpp FileMgr.cpp /link setargv.obj

Maintenance History:
====================
ver 1.0 : 05 March 2016
- first release

*/

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../Utilities/Utilities.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"

class MetricAnalysis
{
public:
	MetricAnalysis();
	MetricAnalysis(std::string AnalyPath);
	~MetricAnalysis();
	void doAnalysis();
	void attachFile(std::string analyfile);
private:
	ConfigParseToConsole configure;
	std::string fileSpec;
	Parser* pParser;
};

#endif
