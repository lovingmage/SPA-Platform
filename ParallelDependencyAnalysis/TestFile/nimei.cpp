#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../Utilities/Utilities.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"

using namespace std;
//Test Using 

int main(){
	
	func1(25);
	std::cout << "Here is the func1 calling position";
	//This place will call the functions in .h file
	
	func2(33, 85);
	std::cout << "Here is the func2 calling position";
	//This place will call the functions in .h file


	puttin(99, "NIMEI", "NIMEI, NIMEI");
	//This place will call the functions in .h file

	std::cout << "Here is the puttin calling position";
	
	isfunc2M(290, 787);
	//This place will call the functions in cando.h fil
	
	isfunc3M(990, 700);
	//This place will call the functions in cando.h file
	
	element su;
	// Test the struct detection

	Helper;
	//Test using alias;
	
	doit;
	//Test enum
	
	li spec = 1000000;
}