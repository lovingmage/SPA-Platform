#include <vector>
#include "../Tokenizer/Tokenizer.h"
#include "../FileSystem-Windows/FileSystemDemo/FileSystem.h"
#include "../Utilities/Utilities.h"
#include "../SemiExp/SemiExp.h"
#include "../Parser/Parser.h"
#include "../Parser/ActionsAndRules.h"
#include "../Parser/ConfigureParser.h"

struct element
{
  std::string type;
  std::string name;
  size_t lineCount;
  std::string show()
  {
    std::ostringstream temp;
    temp << "(";
    temp << type;
    temp << ", ";
    temp << name;
    temp << ", ";
    temp << lineCount;
    temp << ")"; 
    return temp.str();
  }
};

class Build
{
	public:
	void build()
	{
		cout<<yes<<endl;
	}
}

int func1(int i){
	for(i =0; i<10;i++){
		if(i>5){
			std::cout << i;
		}
	}
}

int func2(int i, int j)
{
	PTC *pTc = new PTC 
}