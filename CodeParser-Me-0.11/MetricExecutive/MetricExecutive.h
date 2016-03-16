#ifndef METRIXEXE_H
#define METRICEXE_H
/////////////////////////////////////////////////////////////////////
//  MetricExecutive.h - MetricExecutive Package                    //
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
This module will search for some specific directory given by command
argments and then mathc the file pattern given by other command arguments
and then it will run the MetricAnalysis to analysis each matched fiel.

Public Interface:
=================
void setPattern(std::string pattern); //Set File pattern
void setPath(std::string AnalyPath);  //Set Directory Path
void doExecutive();					  //perform executive

Build Process:
==============
Required files
- Parser.h, Parser.cpp, SemiExp.h, SemiEx.cpp,
Tokenizer.h, Tokenizer.cpp,
ActionsAndRules.h, ActionsAndRules.cpp,
ConfigureParser.h, ConfigureParser.cpp,
FileSystem.h, FileSystem.cpp,
FileMgr.h, FileMgr.cpp,
MetricAnalysis.h, MetricAnalysis.cpp,
MetricExecutive.h, MetricExecutive.cpp

Build commands (either one)
- devenv MetricExecutive.sln
- cl /EHsc /DTEST_PARSER MetricExecutive.cpp Parser.cpp SemiExp.cpp Tokenizer.cpp \
ActionsAndRules.cpp ConfigureParser.cpp FileSystem.cpp FileMgr.cpp\
MetricAnalysis.cpp /link setargv.obj

Maintenance History:
====================
ver 1.0 : 05 March 2016
- first release

*/

#include <vector>
#include <iostream>
#include "../Tokenizer/Tokenizer.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../Utilities/Utilities.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../FileMgr/FileMgr.h"
#include "../MetricAnalysis/MetricAnalysis.h"

class MetricExe
{
public:
	MetricExe();
	MetricExe(std::string AnalyPath);
	~MetricExe();
	void setPattern(std::string pattern);
	void setPath(std::string AnalyPath) { anaPath = AnalyPath; }
	void doExecutive();
private:
	std::string anaPath;
	DataStore ds;
	FileMgr fm;

};


#endif