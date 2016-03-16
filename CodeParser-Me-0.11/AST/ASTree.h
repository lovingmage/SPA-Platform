///////////////////////////////////////////////////////////////////////
// ASTree.h - Abstract Syntax Tree                                   //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CIS687 - Object Oriented Design    //
// Author:		Chenghong Wang, Syracuse University					 //
//				cwang132@syr.edu									 //
//																	 //
///////////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package provides a class of Abstract Syntax Tree, this tree
* class can perform losts of operations including append child, 
* insert nodes, get complexity, count lines, etc. This tree is 
* used for constructing syntax tree in code parser process.
*
*
* Build Process:
* --------------
* Required Files: AST.h, ASTree.h, ASTree.cpp
* Build Command: devenv AST.sln /rebuild debug
*
* Maintenance History:
* --------------------
* ver 1.1 : 11 March 2016
* - Add the method ShowcurrNode()
* - Delete two redudant elements in ASTree Class
* ver 1.0 : 5 March 2016
* - start up AST project
*
* Planned Additions and Changes:
* ------------------------------
* - none yet
*/
#ifndef ASTREE_H
#define ASTREE_H


#pragma once
#include "AST.h"
#include <iostream>
#include <iomanip>

class ASTree : public IAST {

public:
	ASTree();
	~ASTree() {};
	void AppendChild();
	void InsertElement(std::string type, std::string name, size_t linecount);
	void getParent();
	size_t getComplexity(tree<Element>::iterator itr);
	void ShowCurrNode();
	void ShowTree();
	Element GetCurrElement();

private:
	tree<Element> astree;
	tree<Element>::iterator root;
	tree<Element>::iterator currItr;
};

#endif 