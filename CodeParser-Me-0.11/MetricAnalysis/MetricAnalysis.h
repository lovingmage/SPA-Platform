#ifndef METRIC_H
#define METRIC_H

#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../Utilities/Utilities.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"

class MetricAnalysis
{
public:
	MetricAnalysis();
	MetricAnalysis(std::string AnalyPath);
	~MetricAnalysis();
	void doAnalysis();
private:
	ConfigParseToConsole configure;
	std::string fileSpec;
	Parser* pParser;
};

#endif
