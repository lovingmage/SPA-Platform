#ifndef PARADEPENDENCY_H
#define PARADEPENDENCY_H
/////////////////////////////////////////////////////////////////////////////
//  ParallelDependencyAnalysis.h - Analyzes dependencey of different file  //
//  ver 1.0																   //
//  Language:      Visual C++ 2015, SP1									   //
//  Application:   DependencyAnalysis for CSE687 Pr3					   //
//  Author:        Chenghong Wang										   //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University			   //
//                 (315) 443-3948, jfawcett@twcny.rr.com				   //
/////////////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is used for analyzing dependency of different files and
output them, thie module is the parallel version.

Public Interface:
=================
WorkResult _startdepAnalysis(const std::string& handleFile)            //It is used for starting the dependency analysis
void _getTypes(TypeAnalysis<WorkResult>* pTypeContainer)               //It is used for checking if types are writing in

Build Process:
==============
Required files
- ThreadPool.h, Task.h, Parser.h, TypeAnalysis.h
ThreadPool.cpp, Task.cpp, Parser.cpp, TypeAnalysis.cpp


Build commands
- devenv ParallelDependencyAnalysis.sln

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
#include <vector>
#include "../ThreadPool/ThreadPool.h"
#include "../Task/Task.h"
#include "../Parser/Parser.h"
#include "../TypeAnalysis/TypeAnalysis .h"

using namespace Scanner;
using Helper = Utilities::StringHelper;
using namespace Utilities;



template<typename Result>
class ParaDependencyAnalysis
{
public:
	WorkResult _startdepAnalysis();
	void _getTypes(TypeAnalysis<WorkResult>* pTypeContainer);
	BlockingQueue<std::string>& _getDependencyCollection() { return _dependencyCollection; }


private:
	std::vector<std::string> DependencyList;
	std::map<std::string, std::string> typeCollection;
	BlockingQueue<std::string> _fileCollectionQueue;
	BlockingQueue<std::string> _dependencyCollection;
};


//----< setup one dependency analysis task>---------------------------

template<typename Result>
inline WorkResult ParaDependencyAnalysis<Result>::_startdepAnalysis()
{
	std::mutex g_lock;
	g_lock.lock();
	std::string handleFile = _fileCollectionQueue.deQ();
	g_lock.unlock();
	try
	{
		std::ifstream in(handleFile);
		if (!in.good()){
			std::cout << "\n  can't open " << handleFile << "\n\n";
		}

			Toker toker;
			toker.returnComments();
			toker.attach(&in);
			do
			{
				std::string tok = toker.getTok();
				std::map<std::string, std::string>::iterator it;
				it = typeCollection.find(tok);
				if (it != typeCollection.end() && (handleFile != it->second)) {
					std::string keyIndex = "\n TYPE NAME : \t<-- " + it->first + " -->\tin \n\t" + handleFile + "\n\tDependence Relation \n\t\t|\n\t\t|\n\t\t--->" + it->second;
					_dependencyCollection.enQ(keyIndex);
					//std::cout << it->first << "==>" << " Dependent on " << it->second << std::endl;
				}

			} while (in.good());
		
		putline();
	}
	catch (std::logic_error& ex){
		std::cout << "\n  " << ex.what();
	}
	std::cout << "\n\n";
	return ".";
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
	//std::cout << "Length of current file : " << _fileCollectionQueue.size();
}
#endif