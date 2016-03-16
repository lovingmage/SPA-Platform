/////////////////////////////////////////////////////////////////////
//  AST.h - package for the AST interface                          //
//  ver 1.0                                                        //
//  Language:      Visual Studio 2015                              //
//  Application:   Abstract Syntax Tree Interface                  //
//  Author:		   Chenghong Wang, Syracuse University			   //
//				     cwang132@syr.edu					           //
/////////////////////////////////////////////////////////////////////
/*
Module Purpose:
===============
AST is an interface for abstract syntax tree, it contains some basic 
Abstract Syntax Tree required methods and been defined as virtual
functions, like AppendChild(); InsertElement(); getComplexity();, etc.
This interface can be used in future construction for abstract syntax
tree structure.

Maintenance History:
====================
ver 1.0 : 05 March 2016
- first release
*/
#ifndef AST_H
#define AST_H

#pragma once
#include "tree.hh"
#include <iostream>
#include <string>

struct Element
{
	std::string type;
	std::string name;
	size_t lineCount;

};

class IAST {
public:
	virtual ~IAST() {};
	void virtual AppendChild() =0 ;
	void virtual InsertElement(std::string type, std::string name, size_t linecount)=0;
	void virtual getParent()=0;
	size_t virtual getComplexity(tree<Element>::iterator itr)=0;
	void virtual ShowTree()=0;

};

#endif