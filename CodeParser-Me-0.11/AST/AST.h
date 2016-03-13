#ifndef AST_H
#define AST_H

#pragma once
#include "tree.h"
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