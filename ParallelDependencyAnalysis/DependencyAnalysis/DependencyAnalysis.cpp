
/////////////////////////////////////////////////////////////////////
//  DependencyAnalysis.h - Analyzes dependencey of different file  //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   DependencyAnalysis for CSE687 Pr3               //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
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
	typeContainer.setAnalysisFiles();

	typeContainer.typeParser();
	typeContainer.typeParser();
	typeContainer.typeParser();


	DependencyAnalysis<WorkResult> DepAna;
	DepAna._getTypes(&typeContainer);
	DepAna._startdepAnalysis();

	
}
#endif