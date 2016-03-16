/////////////////////////////////////////////////////////////////////
//  MetricAnalysis.cpp - MetricAnalysis Package                    //
//  ver 1.0                                                        //
// Language:    C++, Visual Studio 2015                            //
// Application:	MetricExecutive , CIS687 Object Oriented  Design   //
//                                                                 //
// Author:		Chenghong Wang, Syracuse University				   //
//				cwang132@syr.edu								   //
// Source:        Jim Fawcett, CST 4-187, Syracuse University      //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////
#include <queue>
#include <string>
#include <cctype>
#include <string>
#include <iostream>
#include "MetricAnalysis.h"
#include "../Utilities/Utilities.h"

using namespace Scanner;
using namespace Utilities;
#define Util StringHelper


//MetricAnalysis Constructor
MetricAnalysis::MetricAnalysis()
{
	pParser = configure.Build();
	
}

//MetricAnalysis Constructor with arguments which initialize fileSpec
MetricAnalysis::MetricAnalysis(std::string AnalyPath)
{
	pParser = configure.Build();
	fileSpec = AnalyPath;
}

//Method to perform metric analysis
void MetricAnalysis::doAnalysis()
{
	ASTree* tempTree = &configure.getASTree();
	try
	{
		if (pParser)
		{
			if (!configure.Attach(fileSpec))
			{
				std::cout << "\n  could not open file " << fileSpec << std::endl;
			}
		}
		else
		{
			std::cout << "\n\n  Parser not built\n\n";
		}
		// now that parser is built, use it
		std::cout << "-------------------" << "Start Presenting Functions" << "------------------" << std::endl;
		while (pParser->next())
			pParser->parse();
		std::cout << "\n";
	}
	catch (std::exception& ex)
	{
		std::cout << "\n\n    " << ex.what() << "\n\n";
	}
	std::cout << "-------------------"<< "Tree Structure Presentation" << "------------------\n"<<std::endl;
	std::cout <<"<Tree Node Format (Name, Type, Lines, Complexity)>\n" << std::endl;
	tempTree->ShowTree();
}

//Attach file to fileSpec in the metricAnalysis Class
void MetricAnalysis::attachFile(std::string analyfile)
{
	fileSpec = analyfile;
}

//----< test stub >--------------------------------------------

//#define TEST_METRIC
#ifdef TEST_METRIC

#define Util StringHelper

int main(int argc, char* argv[])
{
	Util::Title("Testing Parser Class", '=');
	putline();

	// collecting tokens from files, named on the command line
	if (argc < 2)
	{
		std::cout
			<< "\n  please enter name of file to process on command line\n\n";
		return 1;
	}

	for (int i = 1; i < argc; ++i)
	{
		std::string fileSpec = FileSystem::Path::getFullFileSpec(argv[i]);
		std::string msg = "Processing file" + fileSpec;
		Util::title(msg);
		putline();
		MetricAnalysis* Metric = new MetricAnalysis(fileSpec);
		Metric->doAnalysis();

		std::cout << "\n";
	}
}

#endif