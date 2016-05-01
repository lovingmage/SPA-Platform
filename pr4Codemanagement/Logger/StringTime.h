#ifndef STRINGTIME_H
#define STRINGTIME_H
#include <windows.h> 
#include <iostream>
#include <sstream>
#include <vector>

class Time
{
public:
	std::string getString(const int n);
	std::string stringTime();
};
#endif