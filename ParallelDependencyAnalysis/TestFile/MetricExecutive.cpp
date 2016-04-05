#include "MetricExecutive.h"
using namespace Scanner;
using namespace Utilities;

MetricExe::MetricExe(std::string AnalyPath) : fm(AnalyPath, ds){}

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
		std::string fileSpec = FileSystem::Path::getFullFileSpec(tempFile);
		MetricAnalysis* MA = new MetricAnalysis(fileSpec);
		MA->doAnalysis();
		std::cout << "\n  " << tempFile;
	}

	std::cout << "\n\n";
}


//----< test stub >--------------------------------------------

#define TEST_METRICEXE
#ifdef TEST_METRICEXE

#define Util StringHelper

int main(int argc, char* argv[])
{
	//Util::Title("Testing Parser Class", '=');
	//putline();


	MetricExe* ME = new MetricExe(".");
	ME->setPattern("*cpp");
	ME->setPattern("*.h");
	ME->doExecutive();
}

#endif