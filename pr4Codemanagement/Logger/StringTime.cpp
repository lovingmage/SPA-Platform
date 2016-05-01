#include <windows.h> 
#include <iostream>
#include <sstream>
#include <vector>
#include "StringTime.h"

using namespace std;

string Time::getString(const int n)
{

	stringstream newstr;
	newstr << n;
	return newstr.str();
}

string Time::stringTime()
{
	int Temp;
	vector <string> sTemp;
	string time;

	SYSTEMTIME sys;
	GetLocalTime(&sys);

	Temp = sys.wYear;
	sTemp.push_back(getString(Temp));
	Temp = sys.wMonth;
	sTemp.push_back(getString(Temp));
	Temp = sys.wDay;
	sTemp.push_back(getString(Temp));
	Temp = sys.wHour;
	sTemp.push_back(getString(Temp));
	Temp = sys.wMinute;
	sTemp.push_back(getString(Temp));
	Temp = sys.wSecond;
	sTemp.push_back(getString(Temp));

	time = + "_DATE[" + sTemp[0] + '_' + sTemp[1] + '_' + sTemp[2] + "]__TIME[" + sTemp[3] + '_' + sTemp[4] + '_' + sTemp[5] + ']';
	return time;
}


#ifdef TEST_StringTime
int main(void)
{
	string time;
	Time newTime;
	time = newTime.stringTime();
	cout << time <<endl;

	system("pause");
	return 0;
}

#endif