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
	Element _currentElement;
	Element _nextElement;
	tree<Element> astree;
	tree<Element>::iterator root;
	tree<Element>::iterator currItr;
};

#endif 