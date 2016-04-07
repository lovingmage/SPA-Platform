#ifndef TYPEANALYSIS_H
#define TYPEANALYSIS_H
/////////////////////////////////////////////////////////////////////
//  typeanalysis.h - collect all types in target source files      //    
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   TypeAnalysis for CSE687 Pr3                     //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is used to collect all types in target source files, it is
a template.

Public Interface:
=================
TypeAnalysis();                                                                               //construct TypeAnalysis
TypeAnalysis(std::string AnalyPath, ThreadPool<WorkResult>* proc, Task<WorkResult>* pWi);     //construct TypeAnalysis with parameters
void addTypeAnalysis(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc);                    //add TypeAnalysis with task and workqueue
void ternimateAnalysis(ThreadPool<WorkResult>* proc);                                         //give nonepointer if none
void setAnalysisFiles();                                                                      //it will set the file type
~TypeAnalysis();                                                                              //destruct TypeAnalysis
WorkResult typeParser(std::string fi);                                                        //create parser
std::vector<std::string>& getFileCollection() { return fileCollection; }                      //it used for return file colletcion
std::map<std::string, std::string>& _getMergeType() { return _mergeType; }                    //it used for return mergeType


Build Process:
==============
Required files
- ThreadPool.h, Task.h, Parser.h, DataStore.h, FileMgr.h, Utilities.h, Tokenizer.h,
ActionsAndRules.h, ConfigureParser.h, Parser.h, ThreadPool.cpp, Task.cpp, Parser.cpp,
DataStore.cpp, FileMgr.cpp, Utilities.cpp, Tokenizer.cpp, ActionsAndRules.hcpp,
ConfigureParser.cpp, Parser.cpp


Build commands
- devenv TypeAnalysis.sln

Maintenance History:
====================
ver 1.0 : 4 Apr 16
- first release

*/

#include <iostream>
#include <map>
#include <thread>
#include <functional>
#include <conio.h>
#include <typeinfo> 
#include <mutex>
#include "../Task/Task.h"
#include "../Parser/Parser.h"
#include "../DataStore/DataStore.h"
#include "../FileMgr/FileMgr.h"
#include "../Utilities/Utilities.h"
#include "../Tokenizer/Tokenizer.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../Parser/Parser.h"

using namespace Scanner;
using namespace Utilities;

template<typename Result>
using WorkItem = std::function<Result()>;

using WorkResult = std::string;

template<typename Result>
class TypeAnalysis
{
public:
	TypeAnalysis(std::string fi);
	TypeAnalysis(std::string AnalyPath, ThreadPool<WorkResult>* proc, Task<WorkResult>* pWi);
	void addTypeAnalysis(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc);
	void ternimateAnalysis(ThreadPool<WorkResult>* proc);
	void setAnalysisFiles();
	~TypeAnalysis();

	//Basic Method Defined
	void initTypeAnalysis();
	WorkResult typeParser();
	void _initMerge();

	//method to access private data
	std::vector<std::string>& getFileCollection() { return fileCollection; }
	size_t _getfileCollectionQueueSize() { return _fileCollectionQueue.size(); }
	std::map<std::string, std::string>& _getMergeType() { return _mergeType; }
	BlockingQueue<std::pair<std::string, std::string>>& _getMergeTypeQueue() { return _mergeTypeQueue; }

private:
	std::vector<std::string> fileCollection;
	BlockingQueue<std::string> _fileCollectionQueue;
	ThreadPool<WorkResult>* runningPool;
	Task<WorkResult>* typeTask;
	std::map<std::string, std::string> _mergeType;
	BlockingQueue<std::pair<std::string, std::string>> _mergeTypeQueue;
	std::string anaPath;
	size_t flagPos;
	DataStore ds;
	FileMgr fm;

};

//----< Constructor for this class >--------------------------
template<typename Result>
inline TypeAnalysis<Result>::TypeAnalysis(std::string fi) : fm(fi, ds), anaPath(fi), flagPos(0){}

//----< Constructor with initiazations>----------------------------
template<typename Result>
inline TypeAnalysis<Result>::TypeAnalysis(std::string AnalyPath, ThreadPool<WorkResult>* proc, Task<WorkResult>* pWi) : fm(AnalyPath, ds), anaPath(AnalyPath), flagPos(0)
{
	runningPool = proc;
	typeTask = pWi;
}

//----< Destructor >----------------------------
template<typename Result>
inline TypeAnalysis<Result>::~TypeAnalysis() {}

//----< Create one type analysis task and enQueue the workQueue >----------------------------
template<typename Result>
inline void TypeAnalysis<Result>::addTypeAnalysis(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc)
{
	typeTask->createTask(pWi, proc);
}


//----< Create the termination tasks for the thread pool, if not the threadpool will keep alive >---
template<typename Result>
inline void TypeAnalysis<Result>::ternimateAnalysis(ThreadPool<WorkResult>* proc)
{
	typeTask->creaNull(ThreadPool<WorkResult>* proc);
}

//----< Init the type analysis process, reserved >--------------------------
template<typename Result>
inline void TypeAnalysis<Result>::initTypeAnalysis(){}

//----< Member Function for TypeAnalysis which will be called into thread >----------------------------
template<typename Result>
inline WorkResult TypeAnalysis<Result>::typeParser()
{
	std::mutex g_lock;
	std::this_thread::sleep_for(std::chrono::microseconds(rand() % 100));
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	g_lock.lock();
	std::string handleFile = _fileCollectionQueue.deQ();
	g_lock.unlock();

	if (pParser)
	{
		if (!configure.Attach(handleFile))
		{
			std::cout << "\n  could not open file ";
		}
	}
	else
	{
		std::cout << "\n\n  Parser not built\n\n";
	}
	while (pParser->next())
		pParser->parse();
	std::cout << "\n";

	for (std::map<std::string, std::string>::iterator it = configure.getType().begin(); it != configure.getType().end(); it++)
	{
		_mergeTypeQueue.enQ(std::pair<std::string, std::string>(it->first, handleFile));
	}
	//std::cout<< runningPool->getFlag()<<std::endl;
	return "\n Current Parser Work Finish";
}

//----< Perform the Merge Process >--------------------------
template<typename Result>
inline void TypeAnalysis<Result>::_initMerge()
{
	size_t len = _mergeTypeQueue.size();
	for (size_t i = 0; i < len; i++) {
		std::pair<std::string, std::string> temp = _mergeTypeQueue.deQ();
		_mergeType.insert(temp);
	}
}



//----< Get all the files which we need to analyssi >----------------------------
template<typename Result>
inline void TypeAnalysis<Result>::setAnalysisFiles()
{
	fm.addPattern("*.h");
	fm.addPattern("*.cpp");
	fm.search();
	DataStore::iterator start = ds.begin();
	DataStore::iterator end = ds.end();
	std::string tempFile;
	for (start; start != end; ++start)
	{
		tempFile = *start;
		std::string fullpath = anaPath + tempFile;
		std::string fileSpec = FileSystem::Path::getFullFileSpec(fullpath);
		_fileCollectionQueue.enQ(fileSpec);
		fileCollection.push_back(fileSpec);
	}
	std::cout << "\n\n";
}

#endif