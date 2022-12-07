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
    std::stringstream commandos;
    std::string line, commandName, fileNameDir;
    int isCommand, takeCmdOutput, cmdOutputCounter, fileSize, collectInfo, dirFileSize, totalFileSize;
    int changeDir = 0;
    std::vector<std::string> systemCurrentPath = {};
    int systemCurrentPathSize[100];
    int systemPathLevel = 0;

    commandos = readFile((char*)"input");
    collectInfo = 0;
    takeCmdOutput = 0;
    fileSize = 0;
    dirFileSize = 0;
    totalFileSize = 0;
    while (getline (commandos, line, '\n')) {
        std::cout << "> " << line << std::endl;
        std::stringstream command(line);
        std::string commandParts;
        isCommand = 0;
        cmdOutputCounter = 0;
        changeDir = 0;
        while (getline (command, commandParts, ' ')){
//            std::cout << "next command parts: " << commandParts << std::endl;
//            std::cout << "takeCmdOutput: " << takeCmdOutput << std::endl;
            if (takeCmdOutput == 1 && commandParts[0] != '$')
            {
                if (commandParts != "dir" && cmdOutputCounter == 0) // 
                {
//                    std::cout << commandParts << std::endl;
                    fileSize = std::stoi(commandParts);
                    systemCurrentPathSize[systemPathLevel] += fileSize;
                }

                if (cmdOutputCounter == 1) // get name 
                {
                    fileNameDir = commandParts;
                    cmdOutputCounter = 0;
                } 

                cmdOutputCounter ++;
            }

            if (changeDir == 1)
            {
                std::cout <<"current Path: ";
                for (std::string directory: systemCurrentPath)
                {
                    if (directory == "/"){
                        std::cout << "/";
                    }
                    else
                    {
                        std::cout << directory << "/";
                    }
                }
                std::cout << std::endl;
                std::cout << "current Path Size: ";
                for (int j = 0; j <= systemPathLevel; j++)
                {
                    std::cout << systemCurrentPathSize[j] << "/";
                }
                std::cout << std::endl;

                fileNameDir = commandParts;
                std::cout <<"fileNameDir added to path -" << fileNameDir<< "-\n";
                if (fileNameDir == ".."){
                    if (systemCurrentPathSize[systemPathLevel] <= 100000){
                        totalFileSize += systemCurrentPathSize[systemPathLevel];
                        std::cout << "adding to total " << totalFileSize << "\n";
                    }
                    if (systemCurrentPath.back() != "/")
                        systemCurrentPath.pop_back();
                    systemCurrentPathSize[systemPathLevel-1] += systemCurrentPathSize[systemPathLevel];
                    systemPathLevel--;
                }
                else
                {
                    systemCurrentPath.push_back(fileNameDir);
                    if (fileNameDir != "/")
                        systemPathLevel++;
                    systemCurrentPathSize[systemPathLevel] = 0;
                }

                std::cout <<"current Path: ";
                for (std::string directory: systemCurrentPath)
                {
                    if (directory == "/"){
                        std::cout << "/";
                    }
                    else
                    {
                        std::cout << directory << "/";
                    }
                }
                std::cout << std::endl;
                std::cout << "current Path Size: ";
                for (int j = 0; j <= systemPathLevel; j++)
                {
                    std::cout << systemCurrentPathSize[j] << "/";
                }
                std::cout << std::endl;
                isCommand = 0;
            }

            if (isCommand == 1) 
            {
                commandName = commandParts;
                isCommand = 0;
                if ( commandName == "ls"){
//                    std::cout << "Command ls start counting size" << std::endl;
//                    std::cout << "dirFileSize: " << dirFileSize << std::endl;
                    collectInfo = 1;
                    changeDir = 0;
                    takeCmdOutput = 1;  
                    fileSize = 0;
                }
                if ( commandName == "cd"){
//                    std::cout << "Command cd" << std::endl;
                    collectInfo = 0;
                    changeDir = 1;
                }
            }

            if (commandParts == "$")
            {
                isCommand = 1;
                takeCmdOutput = 0;
                cmdOutputCounter = 0;
//                std::cout << "new Command dirFileSize: " << dirFileSize << std::endl;
            }
        }
//        std::cout << "file Size: " << fileSize << std::endl;
//        std::cout << "file Size in dir: " << dirFileSize << std::endl;
        if (fileSize != 0)
            dirFileSize += fileSize;
    }
    if (systemCurrentPathSize[systemPathLevel] <= 100000){
        totalFileSize += systemCurrentPathSize[systemPathLevel];
        std::cout << "adding to total " << totalFileSize << "\n";
    }
    
    std::cout << "What is the sum of the total sizes of those directories? ";
    std::cout << totalFileSize << std::endl; 

    return 1;
}
