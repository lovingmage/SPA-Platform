///////////////////////////////////////////////////////////////////////
// ASTree.h - Abstract Syntax Tree                                   //
// ver 1.1                                                           //
// Language:    C++, Visual Studio 2015                              //
// Application: Parser component, CIS687 - Object Oriented Design    //
// Author:		Chenghong Wang, Syracuse University					 //
//				cwang132@syr.edu									 //
//																	 //
///////////////////////////////////////////////////////////////////////

#include "ASTree.h"

//constructor without argument to initialize AST with namespace as its type
ASTree::ASTree() {
	Element _currentElement;
	_currentElement.type = "Namespace";
	_currentElement.name = "Global";
	_currentElement.lineCount = 0;
	root = astree.begin();
	currItr = astree.insert(root, _currentElement);
}

//Add element to the current parent, then then make the pointer points to this new element
void ASTree::AppendChild() {

	Element _tempElement;
	currItr = astree.append_child(currItr, _tempElement);

}

//Add element to the current parent, then then make the pointer points to this new element
void ASTree::InsertElement(std::string type, std::string name, size_t linecount) {
	(*currItr).type = type;
	(*currItr).lineCount = linecount;
	(*currItr).name = name;
}


//show the whole tree with infor: type, name, lineCount and complexity
void ASTree::ShowTree() {
	tree<Element>::iterator iterStart = astree.begin();
	tree<Element>::iterator end = astree.end();
	while (iterStart != end) {
		for (int i = 0; i < astree.depth(iterStart); ++i)
			std::cout << "	";
		if ((*iterStart).type == "Namespace")
			std::cout << (*iterStart).type << ", " << (*iterStart).name << std::endl;
		else
			std::cout <<std::setw(10)<<std::setfill('-')<< "-> (" <<(*iterStart).type << ", " << (*iterStart).name << ", " << (*iterStart).lineCount << ", " << getComplexity(iterStart) << ")" << std::endl;
		++iterStart;
	}
}


//make the current pointer point to its parent
void ASTree::getParent() {
	currItr = astree.parent(currItr);
}


//get the scope complexity of the indicated Element which should be a tree iterator
size_t ASTree::getComplexity(tree<Element>::iterator itr) {

	return astree.size(itr);
}

//Show the current Node information
void ASTree::ShowCurrNode() {
	std::cout << "-----------Show Current Node------------";
	std::cout << (*currItr).lineCount << std::endl;
	std::cout << (*currItr).name << std::endl;
}

//return the element the pointer currently points to
Element ASTree::GetCurrElement() {
	return *currItr;
}



#ifdef  TEST_ASTREE

int main() {

	

	AST *ast = new ASTree();
	ast->ShowTree();

	//ast.GetCurrentElement()
}

#endif