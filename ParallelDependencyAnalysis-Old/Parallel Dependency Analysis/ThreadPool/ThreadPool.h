#ifndef THREADPOOL_H
#define THREADPOOL_H
///////////////////////////////////////////////////////////////////////
// QueuedWorkItems.h - child thread processes enqueued work items    //
//                                                                   //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2016         //
///////////////////////////////////////////////////////////////////////
/*
* A single child thread processes work items equeued by main thread
*/

#include <thread>
#include <functional>
#include <conio.h>
#include "Cpp11-BlockingQueue.h"

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
	size_t getThreadCount();
	Result result();
	void wait();
	~ThreadPool();
private:
	std::thread* _pThread;
	std::vector<std::thread*> _pThreadPool;
	BlockingQueue<WorkItem<Result>*> _workItemQueue;
	BlockingQueue<Result> _resultsQueue;
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
//----< retrieve results with blocking call >--------------------------

template<typename Result>
inline size_t ThreadPool<Result>::getThreadCount()
{
	size_t len = _pThreadPool.size();
	return len;
}

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

