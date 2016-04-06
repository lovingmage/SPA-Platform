#ifndef PARADEPENDENCY_H
#define PARADEPENDENCY_H
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

#include <iostream>
#include <map>
#include <thread>
#include <functional>
#include <conio.h>
#include <typeinfo> 
#include <vector>
#include "../ThreadPool/ThreadPool.h"
#include "../Task/Task.h"
#include "../Parser/Parser.h"
#include "../TypeAnalysis/TypeAnalysis .h"

using namespace Scanner;
using namespace Utilities;
using Helper = Utilities::StringHelper;
using namespace Utilities;



template<typename Result>
class ParaDependencyAnalysis
{
public:
	WorkResult _startdepAnalysis();
	void _getTypes(TypeAnalysis<WorkResult>* pTypeContainer);


private:
	std::vector<std::string> DependencyList;
	std::map<std::string, std::string> typeCollection;
	BlockingQueue<std::string> _fileCollectionQueue;
};


//----< setup one dependency analysis task>---------------------------

template<typename Result>
inline WorkResult ParaDependencyAnalysis<Result>::_startdepAnalysis()
{
	std::mutex g_lock;
	Helper::Title("Dependency Analysis Start");

	g_lock.lock();
	std::string handleFile = _fileCollectionQueue.deQ();
	std::cout << "Content Size " << _fileCollectionQueue.size() << std::endl;
	g_lock.unlock();
	std::this_thread::sleep_for(std::chrono::microseconds(200));
	std::cout << "\n Handleing on File " << handleFile << std::endl;

	try
	{
		std::ifstream in(handleFile);
		if (!in.good())
		{
			std::cout << "\n  can't open " << handleFile << "\n\n";
		}

		{
			Toker toker;
			toker.returnComments();
			toker.attach(&in);
			do
			{
				std::string tok = toker.getTok();
				std::map<std::string, std::string>::iterator it;
				it = typeCollection.find(tok);
				if (it != typeCollection.end() && (handleFile != it->second))

					std::cout << it->first << "==>" << " Dependent on " << it->second << std::endl;

			} while (in.good());
		}

		putline();

	}
	catch (std::logic_error& ex)
	{
		std::cout << "\n  " << ex.what();
	}
	std::cout << "\n\n";
	return "Got Dep!\n";
}

//----< return the reference of mergeType >---------------------------
template<typename Result>
inline void ParaDependencyAnalysis<Result>::_getTypes(TypeAnalysis<WorkResult>* pTypeContainer)
{
	typeCollection = pTypeContainer->_getMergeType();
	size_t len = pTypeContainer->getFileCollection().size();
	std::vector<std::string> temFileMap = pTypeContainer->getFileCollection();
	for (size_t i = 0; i < len; i++) {
		_fileCollectionQueue.enQ(temFileMap[i]);
	}
	std::cout << "Length of current file : " << _fileCollectionQueue.size();
}
#endif