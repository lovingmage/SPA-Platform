#ifndef ITOKCOLLECTION_H
#define ITOKCOLLECTION_H
////////////////////////////////////////////////////////////////////////
//  ITokCollection.h - package for the ITokCollection interface       //
//  ver 0.2                                                           //
//  Language:      Visual C++ 2015                                    //
//  Platform:      Alienware M17x, Windows 10 Home                    //
//  Application:   Parser component, CIS687 - Object Oriented Design  //
//  Author:		   Chenghong Wang, Syracuse University				  //
//				   cwang132@syr.edu								      //
//																      //
//  Source:        Jim Fawcett, CIS-687 SP16 Help Code Pr1  	      //
//                 jfawcett@twcny.rr.com                              //
////////////////////////////////////////////////////////////////////////
/*
  Module Purpose:
  ===============
  ITokCollection is an interface that supports substitution of different
  types of scanners for parsing.  In this solution, we illustrate that
  by binding two different types of collections, SemiExp,to this interface.
  This is illustrated in the test stubs for the SemiExpression modules.

  Maintenance History:
  ====================
  ver 0.1 : 31 Jun 16
  - Import ITokCollection from Jim Fawcett's source
  ver 0.2 : 8 Feb 16
  - Rewrite show(), clear(), toLower()
*/

struct ITokCollection
{
  virtual bool get()=0;
  virtual size_t length()=0;
  virtual std::string operator[](size_t n)=0;
  virtual size_t find(const std::string& tok)=0;
  virtual void push_back(const std::string& tok)=0;
  virtual bool remove(const std::string& tok)=0;
  virtual bool isComment(const std::string& tok)=0;
  virtual bool remove(size_t i)=0;
  virtual void toLower()=0;
  virtual void trimFront()=0;
  virtual void clear()=0;
  virtual void show()=0;
  virtual ~ITokCollection() {};
};

#endif
