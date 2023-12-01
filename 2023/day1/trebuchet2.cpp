#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>

std::stringstream readFile(char * filename)
{
    std::ifstream inFile;
    std::string line;
    std::stringstream buffer, second_buffer;

    inFile.open(filename);
    for( std::string line; getline( inFile, line ); )
    {   
        buffer << line << std::endl;
    }   

    return buffer;
}

int main(void)
{
    std::vector<int> v;
    std::stringstream bufferFromFile;
    std::string line = "";
    std::string numberStr = "";
    std::string resultStr = "";
    std::string literalNrStr = "";
    int resultA = 0;
    bufferFromFile = readFile((char*)"input");
    std::map<std::string, std::string> m{{"one",   "1"}, 
	                                 {"two",   "2"}, 
                                         {"three", "3"},
					 {"four",  "4"},
					 {"five",  "5"},
					 {"six",   "6"},
					 {"seven", "7"},
					 {"eight", "8"},
					 {"nine",  "9"},
					 {"zero",  "0"},
                	                };
 

    while (getline (bufferFromFile, line, '\n')) {
      for (int i=0; i < line.length(); i++)
      {
	if (line[i] >= '0' && line[i] <='9') {
          numberStr = numberStr + line[i];
	  literalNrStr = "";
	}
	else  
	  literalNrStr = literalNrStr + line[i]; 

 	for(auto it = m.cbegin(); it != m.cend(); ++it)
	{
	  if (literalNrStr.find(it->first) != std::string::npos){
	    numberStr = numberStr + it->second;
	    literalNrStr = std::string(literalNrStr.c_str()+literalNrStr.find(it->first)+1);
	    break;
	  }
	}
      }
      if (numberStr != "") {
	if (numberStr.length() > 1) 
          resultStr = std::string() + numberStr[0] + numberStr[numberStr.length()-1];
	else
          resultStr = std::string() + numberStr[0]+numberStr[0];
	
	v.push_back(std::stoi(resultStr));
	numberStr = "";
      }

    }

    for (int i: v)
      resultA = resultA + i;
    std::cout << "What is the sum of all of the calibration values?"; 
    std::cout << resultA;

}
