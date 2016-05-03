/////////////////////////////////////////////////////////////////////
// FileMgr.cpp - find files matching specified patterns            //
//               on a specified path                               //
// ver 2.0                                                         //
// Jim Fawcett, MidtermCodeSupplement, Spring 2016                 //
/////////////////////////////////////////////////////////////////////

#include "FileMgr.h"
#include <iostream>

#ifdef TEST_FILEMGR

using namespace FileManager;

struct FileHandler : IFileEventHandler
{
	void execute(const std::string& fileSpec)
	{
//		std::cout << "\n  --   " << fileSpec;
	}
};

struct DirHandler : IDirEventHandler
{
	void execute(const std::string& dirSpec)
	{
//		std::cout << "\n  ++ " << dirSpec;
	}
};

int main()
{
	std::cout << "\n  Testing FileMgr";
	std::cout << "\n =================";

	std::string path = FileSystem::Path::getFullFileSpec("../TestFile/Server");
	IFileMgr* pFmgr = FileMgrFactory::create(path);

	FileHandler fh;
	DirHandler dh;

	pFmgr->regForFiles(&fh);
	pFmgr->regForDirs(&dh);

	pFmgr->addPattern("*.h");
	pFmgr->addPattern("*.cpp");
	//pFmgr->addPattern("*.log");

	pFmgr->setFileName("caocaocao.cpp");
	pFmgr->search();
	if (pFmgr->findFile())
	{
		std::cout << "i find it, i find it, i find it" << std::endl;
	}


	std::cout << "\n\n";
	return 0;
}
#endif
