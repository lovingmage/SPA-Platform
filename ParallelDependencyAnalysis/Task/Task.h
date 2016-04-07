#ifndef TASK_H
#define TASK_H
/////////////////////////////////////////////////////////////////////
//  Task.h - Analyzes C++ language constructs                      //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   Task for CSE687 Pr3                             //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is used to create task, and task will be processed by
ThreadPool, what task do is putting task into the blocking queue.

Public Interface:
=================
Task() : flagPos(0) {}                                                     //construct Task
void createTask(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc);      //this is used to create Task
void creaNull(ThreadPool<WorkResult>* proc);                               //creating null point
size_t _getPos() { return flagPos; }                                       //This is used to return the flag position
void _incPos() { flagPos++; }                                              //this is used to increase the Flag value
~Task() {}                                                                 //destruct Task


Build Process:
==============
Required files
- Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp, ThreadPool.h, ThreadPool.cpp
Utility.h, Utility.cpp, Task.h, Task.cpp
Build commands
- devenv Task.sln

Maintenance History:
====================
ver 1.0 : 4 Apr 16
- first release

*/

#include <thread>
#include <functional>
#include <map>
#include <conio.h>
#include "../ThreadPool/ThreadPool.h"

template<typename Result>
using WorkItem = std::function<Result()>;

using WorkResult = std::string;

///////////////////////////////////////////////////////////////////////
// class to process callable on threads


template<typename Result>
class Task
{
public:
	Task() : flagPos(0) {}
	void createTask(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc);
	void creaNull(ThreadPool<WorkResult>* proc);
	size_t _getPos() { return flagPos; }
	void _incPos() { flagPos++; }
	~Task() {}
private:
	std::string filestr;
	size_t flagPos;

};


template<typename Result>
inline void Task<Result>::createTask(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc)
{
	proc->getWorkItemQueue().enQ(pWi);
}

template<typename Result>
inline void Task<Result>::creaNull(ThreadPool<WorkResult>* proc)
{
	size_t nullCount = proc->getThreadCount();
	for (size_t i = 0; i < nullCount; i++)
	{
		proc->getWorkItemQueue().enQ(nullptr);
	}
}


#endif
