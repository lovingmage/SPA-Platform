/////////////////////////////////////////////////////////////////////
//  typeanalysis.h - collect all types in target source files      //    
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   TypeAnalysis for CSE687 Pr3                     //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
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

//#define TEST_TYPEANA
#ifdef TEST_TYPEANA


int main()
{
	Util::Title("Enqueued Work Items");

	std::cout << "\n  main thread id = " << std::this_thread::get_id();

	ThreadPool<WorkResult> processor;
	processor.start();

	Task<WorkResult> currentTask;
	TypeAnalysis<WorkResult> typeContainer("../TestFile/", &processor, &currentTask);
	typeContainer.setAnalysisFiles();

	size_t file_len = typeContainer.getFileCollection().size();

	WorkItem<WorkResult>* wi = new WorkItem<WorkResult>;
	for (size_t i = 0; i < 3; i++) {
		*wi = [&]() {
			typeContainer.typeParser();
			return "Hello from wi";
		};
		processor.doWork(wi);

		wi++;
	}

	for (size_t i = 0; i < 3; i++) {
		std::cout << "\n  " << processor.result();
	}

	while ((typeContainer._getfileCollectionQueueSize()) != 0)
	{
		continue;
	}

	typeContainer._initMerge();

	// Padding with nullptrs

	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.doWork(nullptr);

	// wait for child thread to complete
	processor.wait();

}

#endif