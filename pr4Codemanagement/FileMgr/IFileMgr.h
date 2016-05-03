#pragma once
// IFileMgr.h

#include <string>
#include <vector>
#include <iostream>

namespace FileManager
{
	struct IFileEventHandler
	{
		virtual void execute(const std::string& fileSpec) = 0;
	};

	struct IDirEventHandler
	{
		virtual void execute(const std::string& dirSpec) = 0;
	};

	struct IFileMgr
	{
		virtual ~IFileMgr() {}
		virtual void addPattern(const std::string& patt) = 0;
		virtual void search() = 0;
		virtual void find(const std::string& path) = 0;
		virtual void regForFiles(IFileEventHandler* pEventHandler) = 0;
		virtual void regForDirs(IDirEventHandler* pEventHandler) = 0;
		virtual std::vector<std::string> returnFilePath() = 0;
		virtual void setFileName(std::string temp) = 0;
		virtual bool findFile() = 0;
	};

	struct FileMgrFactory
	{
		static IFileMgr* create(const std::string& path);
	};
}