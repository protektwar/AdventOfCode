#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>

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
    std::stringstream commBuffer;
    std::string packet;
    int i, j;
    std::string startOfPacket;

    commBuffer = readFile((char*)"input");
    int startOfPacketCounter = 0;
    int startOfPacketEndPosition = 0;
    int found = 0;
    std::size_t foundChar;
    while (getline (commBuffer, packet, '\n')) {
        for (char c: packet)
        {
            std::cout << "-" << startOfPacket << "- ";
            std::cout << c << std::endl;
            foundChar = startOfPacket.find(c);
            if (foundChar != std::string::npos){
                std::cout << "found " << foundChar << std::endl;
                std::cout << "before erase: " << startOfPacket << std::endl;
                startOfPacket.erase(0, foundChar+1);
                std::cout << "after erase: " << startOfPacket << std::endl;
                startOfPacketCounter -= foundChar+1;
                found = 1;
            }
            if (startOfPacketCounter == 3)    
                break;
            startOfPacket += c;
            startOfPacketCounter++;
            startOfPacketEndPosition++;
            std::cout << ">" << startOfPacket << "< " << startOfPacketCounter << " " << startOfPacketEndPosition << std::endl;

        }
        if (found == 1)
            break;
    }
    
    std::cout << "How many characters need to be processed before the first start-of-packet marker is detected? ";
    std::cout << startOfPacketEndPosition+1 << std::endl; 

    return 1;
}
