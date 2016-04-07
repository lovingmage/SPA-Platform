//////////////////////////////////////////////////////////////////////////////
//  ParallelDependencyExecutive.cpp - Analyzes dependencey of different file//
//  ver 1.0																	//
//  Language:      Visual C++ 2015, SP1									    //
//  Application:   DependencyAnalysis for CSE687 Pr3						//
//  Author:        Chenghong Wang											//
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University				//
//                 (315) 443-3948, jfawcett@twcny.rr.com					//
//////////////////////////////////////////////////////////////////////////////

#include "./ParallelDependencyExecutive.h"
#include <vector>
using namespace Scanner;
using namespace Utilities;

using Util = Utilities::StringHelper;
using WorkResult = std::string;


//----< test stub >--------------------------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;

#define TEST_PARADEPENDENCYEXE
#ifdef TEST_PARADEPENDENCYEXE


int main(int argc, char* argv[])
{
	Util::Title("Enqueued Work Items");
	std::cout << "\n  main thread id = " << std::this_thread::get_id();
	ThreadPool<WorkResult> processor;
	processor.start();

	Task<WorkResult> currentTask;
	TypeAnalysis<WorkResult> typeContainer(argv[1], &processor, &currentTask);
	typeContainer.setAnalysisFiles(); // Start File Analysis
	size_t file_len = typeContainer.getFileCollection().size();

	WorkItem<WorkResult>* wi = new WorkItem<WorkResult>;
	for (size_t i = 0; i < file_len; i++) {// Start Type Analysis By using multiple thrads
		*wi = [&]() {
			typeContainer.typeParser();
			return "Hello from wi";
		};
		processor.doWork(wi); wi++;
	}
	for (size_t i = 0; i < file_len; i++) 
		std::cout << "\n  " << processor.result();
	while ((typeContainer._getfileCollectionQueueSize()) != 0)
		continue;

	typeContainer._initMerge();// Init Merge Process;
	ParaDependencyAnalysis<WorkResult> ParaDepAna;
	ParaDepAna._getTypes(&typeContainer);
	WorkItem<WorkResult>* wi2 = new WorkItem<WorkResult>;
	for (size_t i = 0; i < file_len; i++) {
		*wi2 = [&]() {
			ParaDepAna._startdepAnalysis();
			return "Hello from dependency";
		};
		processor.doWork(wi2); wi2++;
	}
	for (size_t i = 0; i < file_len; i++)
		std::cout << "\n  " << processor.result();

	std::cout << "\n\n\n<=========================  Dependency Analysis Results  ==========================>\n\n";
	size_t para_len = ParaDepAna._getDependencyCollection().size();
	for (size_t i = 0; i < para_len; i++) {
		std::cout << ParaDepAna._getDependencyCollection().deQ()<< "\n\n\n";
	}
	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.wait();
	std::cout << "\n" << std::endl;
}
#endif