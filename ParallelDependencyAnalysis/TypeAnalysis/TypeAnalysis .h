#ifndef TYPEANALYSIS_H
#define TYPEANALYSIS_H
///////////////////////////////////////////////////////////////////////
// typeanalysis.h - collect all types in target source files         //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016         //
///////////////////////////////////////////////////////////////////////
/*
* collect all types in target source files, include enums, classes, structs
* 
*/

#include <iostream>
#include <map>
#include <thread>
#include <functional>
#include <conio.h>
#include <typeinfo> 
#include <mutex>
#include "../ThreadPool/ThreadPool.h"
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
	TypeAnalysis();
	TypeAnalysis(std::string AnalyPath, ThreadPool<WorkResult>* proc, Task<WorkResult>* pWi);
	void addTypeAnalysis(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc);
	void ternimateAnalysis(ThreadPool<WorkResult>* proc);
	void setAnalysisFiles();
	~TypeAnalysis();

	//Basic Method Defined
	void initTypeAnalysis();
	WorkResult typeParser(std::string fi);

	//method to access private data
	std::vector<std::string>& getFileCollection() { return fileCollection; }
	std::map<std::string, std::string>& _getMergeType() { return _mergeType; }

private:
	std::vector<std::string> fileCollection;
	ThreadPool<WorkResult>* runningPool;
	Task<WorkResult>* typeTask;
	std::map<std::string, std::string> _mergeType;
	std::string anaPath;
	size_t flagPos;
	DataStore ds;
	FileMgr fm;

};
//----< Default Constructor >----------------------------
template<typename Result>
inline TypeAnalysis<Result>::TypeAnalysis(){}

//----< Constructor with initiazations>----------------------------
template<typename Result>
inline TypeAnalysis<Result>::TypeAnalysis(std::string AnalyPath, ThreadPool<WorkResult>* proc, Task<WorkResult>* pWi) : fm(AnalyPath, ds), anaPath(AnalyPath), flagPos(0)
{
	runningPool = proc;
	typeTask = pWi;
}

//----< Destructor >----------------------------
template<typename Result>
inline TypeAnalysis<Result>::~TypeAnalysis() { std::cout << "TypeAnalysis Exit\n"; }

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


template<typename Result>
inline void TypeAnalysis<Result>::initTypeAnalysis()
{

}

//----< Member Function for TypeAnalysis which will be called into thread >----------------------------
template<typename Result>
inline WorkResult TypeAnalysis<Result>::typeParser(std::string fi)
{
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();

	if (pParser)
	{
		if (!configure.Attach(fi))
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
	std::mutex g_lock;
	g_lock.lock();
	for (std::map<std::string, std::string>::iterator it = configure.getType().begin(); it != configure.getType().end(); it++)
	{
		_mergeType.insert(std::pair<std::string, std::string>(it->first, fi));
	}
	g_lock.unlock();
	//std::cout<< runningPool->getFlag()<<std::endl;
	return "\n Current Parser Work Finish";
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
		fileCollection.push_back(fileSpec);
	}
	std::cout << "\n\n";
}

#endif