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

void displayCrt(char crtImage[N][M])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
            std::cout << crtImage[i][j];
        std::cout << std::endl;
    }
}

int main(void)
{
    std::stringstream asmCode;
    std::string instructionLine, word;
    std::string instruction;
    int xRegRead, xReg = 1, sumEnergy = 0;
    int i, j, k, l, cpuCycles = 0, cpuIncCycle=0;
    int spriteCol = 0, crtRow, crtCol;
    int spriteUpper, spriteLower;
    char crtImage[N][M];

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            crtImage[i][j] = '@';

    asmCode = readFile((char*)"input");
    while (getline (asmCode, instructionLine, '\n')) {
        std::stringstream instrToSplit(instructionLine);
        int wordCnt = 0;
        xRegRead = 0;

        std::cout << "cpuCycles: " << cpuCycles << "instr: " << instruction << " xRegRead: " << xRegRead << " xReg Acc: " << xReg <<std::endl;
        displayCrt(crtImage);
        std::cout << "reading instruction" << std::endl;
        while (getline (instrToSplit, word,' ')){
            if (wordCnt == 0)
                instruction = word;
            else
                xRegRead = std::stoi(word);
            wordCnt ++;
        }

        std::cout << "cpuCycles: " << cpuCycles << "instr: " << instruction << " xRegRead: " << xRegRead <<std::endl;
        if (instruction == "addx")
            cpuIncCycle = 2;
        if (instruction == "noop")
            cpuIncCycle = 1;

        for (i = 0; i < cpuIncCycle; i++)
        {
            cpuCycles++;
            crtRow = (cpuCycles-1) / 40;
            crtCol = (cpuCycles-1) % 40;
            spriteUpper = spriteCol + 1;
            spriteLower = spriteCol - 1;
            if (spriteLower < 0)
                spriteLower = 0;
            if (spriteUpper > 39)
                spriteUpper = 39;
            std::cout << "spriteCol: " << spriteCol <<" crtRow: " << crtRow << " crtCol: " << crtCol << std::endl;
            std::cout << "spriteLower: " << spriteLower << " " << crtCol <<" spriteUpper: " << spriteUpper << std::endl;
            std::cout << (spriteLower >= crtCol) << " " << (crtCol <= spriteUpper) << std::endl;
            if ((spriteLower <= crtCol) && (crtCol <= spriteUpper))
            {
                std::cout << "putPixel" << std::endl;
                crtImage[crtRow][crtCol] = '@';
            }
            else
            {
                std::cout << "delPixel" << std::endl;
                crtImage[crtRow][crtCol] = '-';
            }
            displayCrt(crtImage);
        }
        xReg += xRegRead;
        spriteCol = xReg;


        std::cout << "cpuCycles: " << cpuCycles << "instr: " << instruction << " xRegRead: " << xRegRead << " xReg Acc: " << xReg <<std::endl;
    }
   
    std::cout << "What eight capital letters appear on your CRT? ";
    std::cout << sumEnergy << std::endl; 

    return 1;
}
