#ifndef DEPENDENCY_H
#define DEPENDENCY_H
/////////////////////////////////////////////////////////////////////
//  DependencyAnalysis.h - Analyzes dependencey of different file  //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   DependencyAnalysis for CSE687 Pr3               //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is used for analyzing dependency of different files, this
is not the parallel version, if you want to check the parallel version
please check the paralleDependencyAnalysis.

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
- devenv DependencyAnalysis.sln

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
#include "../Task/Task.h"
#include "../Parser/Parser.h"
#include "../TypeAnalysis/TypeAnalysis .h"

using namespace Scanner;
using namespace Utilities;
using Helper = Utilities::StringHelper;
using namespace Utilities;



template<typename Result>
class DependencyAnalysis
{
public:
	WorkResult _startdepAnalysis(const std::string& handleFile);
	void _getTypes(TypeAnalysis<WorkResult>* pTypeContainer);

private:
	std::vector<std::string> DependencyList;
	std::map<std::string, std::string> typeCollection;
};


//----< setup one dependency analysis task>---------------------------

template<typename Result>
inline WorkResult DependencyAnalysis<Result>::_startdepAnalysis(const std::string& handleFile)
{
	Helper::Title("Dependency Analysis Start");
	std::cout << "\n Handleing on File " << handleFile<<std::endl;

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
				if (it != typeCollection.end())
					
					std::cout <<it->first<< "==>" << " Dependent on " << it->second<<std::endl;

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
inline void DependencyAnalysis<Result>::_getTypes(TypeAnalysis<WorkResult>* pTypeContainer)
{
	typeCollection = pTypeContainer->_getMergeType();
}
#endif