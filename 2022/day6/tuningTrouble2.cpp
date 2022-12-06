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
    std::string startOfPacket,startOfMessage;

    commBuffer = readFile((char*)"input");
    int startOfPacketCounter = 0;
    int startOfPacketEndPosition = 0;
    int startOfMessageCounter = 0;
    int startOfMessageEndPosition = 0;
    int found = 0;
    std::size_t foundChar;
    std::size_t foundCharMessage; 
    while (getline (commBuffer, packet, '\n')) {
        for (char c: packet)
        {
            if ( found == 0 )
                std::cout << "-" << startOfPacket << "- ";
            else
                std::cout << "-" << startOfMessage << "- ";

            std::cout << c << std::endl;
            foundChar = startOfPacket.find(c);
            foundCharMessage = startOfMessage.find(c);
            if (foundChar != std::string::npos && found == 0){
                std::cout << "found in Packet" << foundChar << std::endl;
                std::cout << "before erase: " << startOfPacket << std::endl;
                startOfPacket.erase(0, foundChar+1);
                std::cout << "after erase: " << startOfPacket << std::endl;
                startOfPacketCounter -= foundChar+1;
            }

            if (foundCharMessage != std::string::npos && found == 1){
                std::cout << "found in Message" << foundCharMessage << std::endl;
                std::cout << "before erase: " << startOfMessage << std::endl;
                startOfMessage.erase(0, foundCharMessage+1);
                std::cout << "after erase: " << startOfMessage << std::endl;
                startOfMessageCounter -= foundCharMessage+1;
            }
            if (startOfPacketCounter == 3)
            {
                found = 1;
                std::cout << "----------------------------------------------\n";
            }

            if (startOfMessageCounter == 13)
            {   found = 2;
                break;
            }
                 
            if (found == 0) {
                startOfPacket += c;
                startOfPacketCounter++;
            }
            else{ 
                startOfMessage += c; 
                startOfMessageCounter++;
            }
            startOfPacketEndPosition++;
            if (found == 0 ) 
                std::cout << ">" << startOfPacket << "< " << startOfPacketCounter << " " << startOfPacketEndPosition << std::endl;
            else
                std::cout << ">" << startOfMessage << "< " << startOfMessageCounter << " " << startOfPacketEndPosition << std::endl;

        }
        if (found == 2)
            break;
    }
    
    std::cout << "How many characters need to be processed before the first start-of-message marker is detected? ";
    std::cout << startOfPacketEndPosition+1 << std::endl; 

    return 1;
}
