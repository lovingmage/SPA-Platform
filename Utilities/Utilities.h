#ifndef UTILITIES_H
#define UTILITIES_H
///////////////////////////////////////////////////////////////////////
// Utilities.h - small, generally usefule, helper classes            //
// ver 0.1                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CIS687 - Object Oriented Design    //
// Author:		Chenghong Wang, Syracuse University					 //
//				cwang132@syr.edu									 //
//																	 //
// Source:      Jim Fawcett, CIS-687 SP16 Help Code Pr1	             //
//              jfawcett@twcny.rr.com                                //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
*
* Build Process:
* --------------
* Required Files: Utilities.h, Utilities.cpp
*
* Build Command: devenv Utilities.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 0.1 : 08 Feb 2016
* - first release
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/
#include <string>
#include <vector>
#include <sstream>
#include <functional>

namespace Utilities
{
  class StringHelper
  {
  public:
    static std::vector<std::string> split(const std::string& src);
    static void Title(const std::string& src, char underline = '-');
    static void title(const std::string& src);
  };

  void putline();

  template <typename T>
  class Converter
  {
  public:
    static std::string toString(const T& t);
    static T toValue(const std::string& src);
  };

  template <typename T>
  std::string Converter<T>::toString(const T& t)
  {
    std::ostringstream out;
    out << t;
    return out.str();
  }

  template<typename T>
  T Converter<T>::toValue(const std::string& src)
  {
    std::istringstream in(src);
    T t;
    in >> t;
    return t;
  }
}
#endif
