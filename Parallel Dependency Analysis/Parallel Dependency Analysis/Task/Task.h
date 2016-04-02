#ifndef TASK_H
#define TASK_H
///////////////////////////////////////////////////////////////////////
// Task.h - child thread processes enqueued work items               //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016         //
///////////////////////////////////////////////////////////////////////
/*
* A single child thread processes work items equeued by main thread
*/

#include <thread>
#include <functional>
#include <conio.h>
#include "../ThreadPool/Cpp11-BlockingQueue.h"
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
	void createTask(WorkItem<Result>* pWi, ThreadPool<WorkResult>* proc);
	void creaNull(ThreadPool<WorkResult>* proc);
private:
	std::string filestr;

};

#endif

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


