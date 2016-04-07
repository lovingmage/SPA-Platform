/////////////////////////////////////////////////////////////////////
//  Task.h - Analyzes C++ language constructs                      //
//  ver 1.0                                                        //
//  Language:      Visual C++ 2015, SP1                            //
//  Application:   Task for CSE687 Pr3                             //
//  Author:        Chenghong Wang                                  //
//  Reference:     Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <conio.h>
#include "../ThreadPool/ThreadPool.h"
#include "Task.h"
#include "../Utilities/Utilities.h"
#include "../Parser/ConfigureParser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/Parser.h"

//----< demonstrate Task class >----------------------------

using Util = Utilities::StringHelper;
using WorkResult = std::string;

#ifdef TEST_TASK

WorkResult callParser()

{
	ConfigParseToConsole configure;
	Parser* pParser = configure.Build();
	if (pParser)
	{
		if (!configure.Attach("../TestFile/nimei.cpp"))
		{
			std::cout << "\n  could not open file ";
		}
	}
	else
	{
		std::cout << "\n\n  Parser not built\n\n";
	}
	while (pParser->next())
		pParser->parse();
	std::cout << "\n";
	for (std::map<std::string, std::string>::iterator it = configure.getType().begin(); it != configure.getType().end(); it++)
	{
		std::cout << it->first << " => " << it->second << '\n';
	}
	return "Parser Done";
}

int main(int argc, char* argv[])
{
	Util::Title("Enqueued Work Items");

	std::cout << "\n  main thread id = " << std::this_thread::get_id();

	std::vector<std::string> files =
	{
		"../TestFile/nimei.cpp", "../TestFile/nimei2.cpp"
	};
	std::vector<WorkItem<WorkResult>> CallObjs;
	CallObjs.push_back(callParser);
	CallObjs.push_back(callParser);

	size_t len = CallObjs.size();
	ThreadPool<WorkResult> processor;
	processor.start();	

	WorkItem<WorkResult> func = CallObjs[1];
	processor.doWork(&func);


	std::cout << "\n  " << processor.result();


	// Padding with nullptrs

	processor.doWork(nullptr);
	// wait for child thread to complete
	processor.wait();
	std::cout << "\n\n";
}
#endif 