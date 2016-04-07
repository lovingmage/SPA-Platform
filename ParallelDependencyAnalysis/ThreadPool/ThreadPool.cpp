/////////////////////////////////////////////////////////////////////
//  ThreadPool.cpp Analyzes C++ language constructs                //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   ThreadPool for CSE687 Pr3                       //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
/*
* A single child thread processes work items equeued by main thread
*/

#include <string>
#include <iostream>
#include <conio.h>
#include "ThreadPool.h"
#include "../Utilities/Utilities.h"

//----< demonstrate ThreadPool class >----------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;


//#define TEST_THREADPOOL
#ifdef TEST_THREADPOOL

size_t testfunc(size_t in) {
	std::cout << in << std::endl;
	return in;
}

int main()
{
	Util::Title("Enqueued Work Items"); 

	std::cout << "\n  main thread id = " << std::this_thread::get_id();

	ThreadPool<WorkResult> processor;
	processor.start();

	// define 1st work item

	WorkItem<WorkResult> wi1 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi1";
	};

	processor.doWork(&wi1);

	// define 2nd work item

	WorkItem<WorkResult> wi2 = []()
	{
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		size_t sum = 0;
		for (size_t i = 0; i < 100000; ++i)
			sum += i;
		return "wi2 result = " + Utilities::Converter<size_t>::toString(sum);
	};

	processor.doWork(&wi2);

	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();
	size_t po = testfunc(10);

	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.doWork(nullptr);

	processor.wait();
	std::cout << "\n\n";
}
#endif