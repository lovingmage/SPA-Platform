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

#include "MetricExecutive.h"
using namespace Scanner;
using namespace Utilities;
#define Util StringHelper

MetricExe::MetricExe(std::string AnalyPath) : fm(AnalyPath, ds), anaPath(AnalyPath){}

void MetricExe::setPattern(std::string pattern)
{
	fm.addPattern(pattern);
}

void MetricExe::doExecutive()
{
	fm.search();
	DataStore::iterator start = ds.begin();
	DataStore::iterator end = ds.end();
	std::string tempFile;
	for (start; start != end; ++start)
	{


		tempFile = *start;
		std::string fullpath = anaPath + tempFile;
		std::string fileSpec = FileSystem::Path::getFullFileSpec(fullpath);
		MetricAnalysis* MA = new MetricAnalysis(fileSpec);
		MA->doAnalysis();
		std::cout << "\n++ Analysis File: " << tempFile<<std::endl;
		std::cout << "\n++ Analysis Completed !\n\n\n";
		std::cout << "\n\n";
	}

	std::cout << "\n\n";
}


//----< test stub >--------------------------------------------

#define TEST_METRICEXE
#ifdef TEST_METRICEXE

#define Util StringHelper

int main(int argc, char* argv[])
{
	Util::Title("Testing MetricExecutive Class", '=');
	putline();

	// collecting tokens from files, named on the command line

	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}
	std::string filePath = FileSystem::Path::getFullFileSpec(argv[1]);
	MetricExe* ME = new MetricExe(filePath);
	for (int i = 2; i < argc; ++i)
	{
		ME->setPattern(argv[i]);
	}
	ME->doExecutive();
}

#endif