/////////////////////////////////////////////////////////////////////
//  MetricExecutive.cpp - MetricExecutive Package                  //
//  ver 1.0                                                        //
// Language:    C++, Visual Studio 2015                            //
// Application:	MetricExecutive , CIS687 Object Oriented  Design   //
//                                                                 //
// Author:		Chenghong Wang, Syracuse University				   //
//				cwang132@syr.edu								   //
// Source:        Jim Fawcett, CST 4-187, Syracuse University      //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
#include "TypeAnalysis .h"
#include <vector>
using namespace Scanner;
using namespace Utilities;

using Util = Utilities::StringHelper;
using WorkResult = std::string;
//----< test stub >--------------------------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;

#define TEST_TYPEANA
#ifdef TEST_TYPEANA


int main(int argc, char* argv[])
{
	Util::Title("Enqueued Work Items");

	std::cout << "\n  main thread id = " << std::this_thread::get_id();


	ThreadPool<WorkResult> processor;
	processor.start();

	Task<WorkResult> currentTask;
	TypeAnalysis<WorkResult> typeContainer("../TestFile/", &processor, &currentTask);

	WorkItem<WorkResult> wi1 = [&]()
	{
		typeContainer.typeParser("../TestFile/nimei.cpp");
		return "Got it!\n";

	};
	currentTask.createTask(&wi1, &processor);

	WorkItem<WorkResult> wi2 = [&]()
	{
		typeContainer.typeParser("../TestFile/MetricExecutive.cpp");
		return "Got it!\n";
	};

	currentTask.createTask(&wi2, &processor);


	std::cout << "\n  " << processor.result();
	std::cout << "\n  " << processor.result();



	// Padding with nullptrs

	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.doWork(nullptr);

	// wait for child thread to complete
	processor.wait();

	for (std::map<std::string, std::string>::iterator it = typeContainer._getMergeType().begin(); it != typeContainer._getMergeType().end(); it++)
	{
		std::cout << it->first << " ==> "<< it->second << std::endl;
	}
	std::cout << "\n\n";

}

#endif