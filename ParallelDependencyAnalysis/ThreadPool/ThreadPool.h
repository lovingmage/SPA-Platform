#ifndef THREADPOOL_H
#define THREADPOOL_H
/////////////////////////////////////////////////////////////////////
//  ThreadPool.h - Analyzes C++ language constructs                //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   ThreadPool for CSE687 Pr3                       //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
Module Operations:
==================
This module is used for creating a threadpool, so when someone is using
the threadpool, we will create three threads for them.

Public Interface:
=================
BlockingQueue<WorkItem<Result>*>& getWorkingQueue()   //this is used to get working queue of blocking queue
void start();                                         //this is used to get threadpool start
void working(WorkItem<Result>* pWi);                  //this is used to get the working item
size_t getThreadCount();                              //this is used to know how many threads can be in the threadpool
void suspend();                                       //this is used to wait for joinging the threads
Result result();                                      //this is used to return result queue
~ThreadPool();                                        // destruct threadpool

Build Process:
==============
Required files
- Cpp11-BlockingQueue.h, Cpp11-BlockingQueue.cpp, ThreadPool.h, ThreadPool.cpp
Utility.h, Utility.cpp
Build commands
- devenv ThreadPool.sln

Maintenance History:
====================
ver 1.0 : 4 Apr 16
- first release

*/

#include <thread>
#include <functional>
#include <map>
#include <conio.h>
#include "Cpp11-BlockingQueue.h"
#include "../Utilities/Utilities.h"

using Helper = Utilities::StringHelper;

template<typename Result>
using WorkItem = std::function<Result()>;

///////////////////////////////////////////////////////////////////////
// class to process work items
// - each work item is processed sequentially on a single child thread

template<typename Result>
class ThreadPool
{
public:
	void start();
	void doWork(WorkItem<Result>* pWi);
	BlockingQueue<WorkItem<Result>*>& getWorkItemQueue(){return _workItemQueue; }
	std::map<std::string, std::string>& _getMergeType() { return _mergeType; }
	size_t getThreadCount();
	Result result();
	void wait();
	~ThreadPool();
private:
	std::thread* _pThread;
	std::vector<std::thread*> _pThreadPool;
	BlockingQueue<WorkItem<Result>*> _workItemQueue;
	BlockingQueue<Result> _resultsQueue;
	std::map<std::string, std::string> _mergeType;
};
//----< wait for child thread to terminate >---------------------------

template<typename Result>
void ThreadPool<Result>::wait()
{
	size_t len = _pThreadPool.size();
	for (size_t i = 0; i < len; i++)
	{
		_pThreadPool[i]->join();
	}
}
//----< enqueue work item >--------------------------------------------

template<typename Result>
void ThreadPool<Result>::doWork(WorkItem<Result>* pWi)
{
	_workItemQueue.enQ(pWi);
}

//----< retrieve the total number of threads >--------------------------
template<typename Result>
inline size_t ThreadPool<Result>::getThreadCount()
{
	size_t len = _pThreadPool.size();
	return len;
}

//----< retrieve results with blocking call >--------------------------
template<typename Result>
Result ThreadPool<Result>::result()
{
	return _resultsQueue.deQ();
}
//----< start child thread that dequeus work items >-------------------

template<typename Result>
void ThreadPool<Result>::start()
{
	for (size_t i = 0; i < 3; i++)
	{
		std::function<void()> threadProc =
			[&]() {
			while (true)
			{
				WorkItem<Result>* pWi = _workItemQueue.deQ();
				if (pWi == nullptr)
				{
					std::cout << "\n  shutting down work item processing, thread id: " << std::this_thread::get_id();
					return;
				}
				Result result = (*pWi)();
				_resultsQueue.enQ(result);
			}
		};
		_pThread = new std::thread(threadProc);
		_pThreadPool.push_back(_pThread);
	}

}
//----< clean up heap >------------------------------------------------

template<typename Result>
ThreadPool<Result>::~ThreadPool()
{
	//delete _pThreadPool;
}

#endif

