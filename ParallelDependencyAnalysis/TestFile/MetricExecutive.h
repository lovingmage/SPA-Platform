#ifndef METRIXEXE_H
#define METRICEXE_H

#include <vector>
#include <iostream>
#include "../Tokenizer/Tokenizer.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../Utilities/Utilities.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"
#include "../FileMgr/FileMgr.h"
#include "../MetricAnalysis/MetricAnalysis.h"

class MetricExe
{
public:
	MetricExe();
	MetricExe(std::string AnalyPath);
	~MetricExe();
	void setPattern(std::string pattern);
	void doExecutive();
private:
	DataStore ds;
	FileMgr fm;

};


#endif