#ifndef PARADEPENDENCEEXE_H
#define PARADEPENDENCEEXE_H
/////////////////////////////////////////////////////////////////////////////
//  ParallelDependencyExecutive.h - Analyzes dependencey of different file //
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
This module is used for execute the parallelized dependency analysis.

Build Process:
==============
Required files
- ThreadPool.h, Task.h, Parser.h, TypeAnalysis.h
ThreadPool.cpp, Task.cpp, Parser.cpp, TypeAnalysis.cpp
ParallelDependencyAnalysis.h, ParallelDependencyAnalysis.cpp

Build commands
- devenv ParallelDependencyExecutive.sln

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
#include "../ParallelDependencyAnalysis/ParallelDependencyAnalysis.h"

using namespace Scanner;
using Helper = Utilities::StringHelper;
using namespace Utilities;

#endif