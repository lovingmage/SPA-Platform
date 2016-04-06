
#include "./ParallelDependencyAnalysis.h"
#include <vector>
using namespace Scanner;
using namespace Utilities;

using Util = Utilities::StringHelper;
using WorkResult = std::string;


//----< test stub >--------------------------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;

#define TEST_PARADEPENDENCY
#ifdef TEST_PARADEPENDENCY


int main(int argc, char* argv[])
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
	std::cout << "Map Content Size " << typeContainer._getMergeType().size()<< std::endl;
	std::cout << "Queue Content Size " << typeContainer._getMergeTypeQueue().size() << std::endl;

	ParaDependencyAnalysis<WorkResult> ParaDepAna;
	ParaDepAna._getTypes(&typeContainer);
	
	WorkItem<WorkResult>* wi2 = new WorkItem<WorkResult>;

	for (size_t i = 0; i < 3; i++) {
		*wi2 = [&]() {
			ParaDepAna._startdepAnalysis();
			return "Hello from dependency";
		};
		processor.doWork(wi2);

		wi2++;
	}

	for (size_t i = 0; i < 3; i++) {
		std::cout << "\n  " << processor.result();
	}





	// Padding with nullptrs
	processor.doWork(nullptr);
	processor.doWork(nullptr);
	processor.doWork(nullptr);

	processor.wait();


}
#endif