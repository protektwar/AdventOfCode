#include <iostream>
#include <variant>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>
#include <algorithm>
#include <set>
#include <math.h>
#include <unistd.h>

std::stringstream readFile(char * filename)
{
    std::ifstream inFile;
    std::string line;
    std::stringstream buffer;

    inFile.open(filename);
    for( std::string line; getline( inFile, line ); )
    {   
        buffer << line << std::endl;
    }   

    return buffer;
}

int main(void)
{
    std::stringstream monkeyMaths;
    std::string line, monkey1, monkey2, monkey3, monkeyOperation, monkeyValue;
    char column;
    int rootMonkey = 0;


    monkeyMaths = readFile((char*)"input");
    while (getline (monkeyMaths, line, '\n')) {
//        std::cout << line << std::endl;
        std::istringstream monkeys(line);
        if ( line.find('/')!=std::string::npos ||\
             line.find('*')!=std::string::npos ||\
             line.find('+')!=std::string::npos ||\
             line.find('-')!=std::string::npos ) {
            monkeys >> monkey1 >> monkey2 >> monkeyOperation >> monkey3;
            monkey1.erase(monkey1.begin() + monkey1.length()-1);
            std::cout << monkey1 << " = " << monkey2 << monkeyOperation << monkey3 << std::endl;
        }
        else {
            monkeys >> monkey1 >> monkeyValue;
            monkey1.erase(monkey1.begin() + monkey1.length()-1);
            std::cout << monkey1 << " = " << monkeyValue << std::endl;
        }

    }

    std::cout << "What number will the monkey named root yell? ";
    std::cout << rootMonkey << std::endl; 
    return 0;
}
