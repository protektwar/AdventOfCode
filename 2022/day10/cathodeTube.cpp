#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>


#define N 6 
#define M 40
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
    std::stringstream asmCode;
    std::string instructionLine, word;
    std::string instruction;
    int xRegRead, xReg = 1, sumEnergy = 0;
    int i, j, k, l, cpuCycles = 0, cpuIncCycle;

    asmCode = readFile((char*)"input");
    while (getline (asmCode, instructionLine, '\n')) {
        std::stringstream instrToSplit(instructionLine);
        int wordCnt = 0;
        xRegRead = 0;

        while (getline (instrToSplit, word,' ')){
            if (wordCnt == 0)
                instruction = word;
            else
                xRegRead = std::stoi(word);
            wordCnt ++;
        }

        if (instruction == "addx")
            cpuIncCycle = 2;
        if (instruction == "noop")
            cpuIncCycle = 1;

        for (i = 0; i < cpuIncCycle; i++)
        {
            cpuCycles++;
            if (cpuCycles == 20)
            {
                sumEnergy += cpuCycles*xReg;
            }
            if (cpuCycles == 60)
            {
                sumEnergy += cpuCycles*xReg;
            }
            if (cpuCycles == 100)
            {
                sumEnergy += cpuCycles*xReg;
            }
            if (cpuCycles == 140)
            {
                sumEnergy += cpuCycles*xReg;
            }
            if (cpuCycles == 180)
            {
                sumEnergy += cpuCycles*xReg;
            }
            if (cpuCycles == 220)
            {
                sumEnergy += cpuCycles*xReg;
            }
        }
        xReg += xRegRead;

        std::cout << "cpuCycles: " << cpuCycles << "instr: " << instruction << " xRegRead: " << xRegRead << " xReg Acc: " << xReg <<std::endl;

    }
   
    std::cout << "What is the sum of these six signal strengths? ";
    std::cout << sumEnergy << std::endl; 

    return 1;
}
