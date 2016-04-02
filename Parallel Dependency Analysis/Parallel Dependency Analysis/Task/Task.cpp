#include <string>
#include <iostream>
#include <conio.h>
#include "../ThreadPool/ThreadPool.h"
#include "Task.h"
#include "../Utilities/Utilities.h"

//----< demonstrate Task class >----------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;

int main()
{
	Util::Title("Enqueued Work Items");

	std::cout << "\n  main thread id = " << std::this_thread::get_id();

	ThreadPool<WorkResult> processor;
	processor.start();

	Task<WorkResult> currentTask;
	WorkItem<WorkResult> wi1 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi1";
	};
	currentTask.createTask(&wi1, &processor);

	// define 2nd work item

	WorkItem<WorkResult> wi2 = []()
	{
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		size_t sum = 0;
		for (size_t i = 0; i < 100000; ++i)
			sum += i;
		return "wi2 result = " + Utilities::Converter<size_t>::toString(sum);
	};

	currentTask.createTask(&wi2, &processor);

	// define 3rd work item

	WorkItem<WorkResult> wi3 = []() {
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		return "Hello from wi3";
	};

	currentTask.createTask(&wi3, &processor);

	WorkItem<WorkResult> wi4 = []()
	{
		std::cout << "\n  working on thread " << std::this_thread::get_id();
		size_t sum = 0;
		for (size_t i = 0; i < 100000; ++i)
			sum += i;
		return "wi4 result = " + Utilities::Converter<size_t>::toString(sum);
	};

	currentTask.createTask(&wi4, &processor);

	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();

	// Padding with nullptrs
	currentTask.creaNull(&processor);


	// wait for child thread to complete

	processor.wait();
	std::cout << "\n\n";
}