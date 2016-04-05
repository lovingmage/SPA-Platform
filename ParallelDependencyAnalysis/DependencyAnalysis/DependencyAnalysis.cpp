
#include "./DependencyAnalysis.h"
#include <vector>
using namespace Scanner;
using namespace Utilities;

using Util = Utilities::StringHelper;
using WorkResult = std::string;


//----< test stub >--------------------------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;

//#define TEST_DEPENDENCY
#ifdef TEST_DEPENDENCY


int main(int argc, char* argv[])
{

	Util::Title("Enqueued Work Items");

	std::cout << "\n  main thread id = " << std::this_thread::get_id();

	Task<WorkResult> currentTask;
	TypeAnalysis<WorkResult> typeContainer("../TestFile/");

	std::string tempFile = "../TestFile/nimei.cpp";
	typeContainer.typeParser(tempFile);

	DependencyAnalysis<WorkResult> DepAna;
	DepAna._getTypes(&typeContainer);
	DepAna._startdepAnalysis(tempFile);

	
}
#endif