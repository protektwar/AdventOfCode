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
    std::stringstream games;
    std::string game;
    bufferFromFile = readFile((char*)"input");

    while (getline (bufferFromFile, line, '\n')) {
        std::cout << line <<'\n';

    }

    std::cout << "Message Line"; 
    std::cout << "result comes here!";

}
