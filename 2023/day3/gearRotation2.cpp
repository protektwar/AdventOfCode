#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>

#define N 140 
//#define N 10 

int ratioCheck[8][2] = {
                        {-1, -1},              // -|   
                        {-1,  0},              // -|------|     
                        {-1,  1},              // -|------|-----| 
                                               //  |      |     |
                        { 0, -1},              // -1,-1 -1,0  -1,1
                        { 0,  1},              //  0,-1   *    0,1 
                                               //  1,-1  1,0   1,1
                        { 1, -1},              // --|     |     |
                        { 1,  0},              // --------|     |
                        { 1,  1}               // --------------|
                       }; 

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

void printMatrix(const char *gearMatrix)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      std::cout << *(gearMatrix + i*N + j) << "-";
    std::cout << '\n';
  }
}

int findPartNumber(int line, int col, const char gearMatrix[N][N], char *gearMatrixPass)
{
  std::string partNumberStr = "";
  int incrementer = 0;
  while ((gearMatrix[line][col+incrementer] >= '0') && (gearMatrix[line][col+incrementer] <= '9')) {
    partNumberStr = partNumberStr + gearMatrix[line][col+incrementer];
    *(gearMatrixPass + line*N + col+incrementer) = '1';
    incrementer = incrementer + 1;
  }
 
  int decrementer = -1; 
  while ((gearMatrix[line][col+decrementer] >= '0') && (gearMatrix[line][col+decrementer] <= '9')) {
    partNumberStr = gearMatrix[line][col+decrementer] + partNumberStr;
    *(gearMatrixPass + line*N + col+decrementer) = '1';
    decrementer = decrementer - 1;
  }
  if (partNumberStr == "")
    partNumberStr = "0";
  
  return std::stoi(partNumberStr);
}

long long int getGearRatio(int line, int col, const char gearMatrix[N][N], char *gearMatrixPass)
{
  long long int gearRatio = 1;
  std::vector<int> partNumbers;
  for (int i = 0; i < 8; i++){
    if ((line+ratioCheck[i][0] >= 0) && \
        (col +ratioCheck[i][1] < 140)) {
      if (*(gearMatrixPass + (line+ratioCheck[i][0])*N + (col+ratioCheck[i][1])) == '0' && (gearMatrix[line+ratioCheck[i][0]][col+ratioCheck[i][1]] >= '0' && gearMatrix[line+ratioCheck[i][0]][col+ratioCheck[i][1]] <= '9' )){
         int partNumber = findPartNumber(line+ratioCheck[i][0], col+ratioCheck[i][1], gearMatrix, gearMatrixPass);
         if (partNumber != 0) {
           partNumbers.push_back(partNumber);
         }
      }
    }
  }
  if (partNumbers.size() == 2)
    for (int partNumber: partNumbers) 
      gearRatio = gearRatio * partNumber;
  else
    gearRatio = 0;
      
  return gearRatio;
}

std::vector<long long int> findGearRatios(const char gearMatrix[N][N])
{
  std::vector<long long int> returnGearRatios;
  char gearMatrixPass[N][N];

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++)
      gearMatrixPass[i][j] = '0';

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      if (gearMatrix[i][j] == '*'){
          gearMatrixPass[i][j] = '1';  
          returnGearRatios.push_back(getGearRatio(i, j, gearMatrix, &gearMatrixPass[0][0]));
      }
    }
    
  return returnGearRatios;
}

int main(void)
{
    std::stringstream bufferFromFile;
    std::string line;
    char gearMatrix[N][N]; 
    long int sumResult = 0;
    std::vector<long long int> gearRatios;
 
    int i = 0;
    bufferFromFile = readFile((char*)"input");
//    bufferFromFile = readFile((char*)"demo");
    while (getline (bufferFromFile, line, '\n')) {
      for (int j = 0; j < line.length(); j++)
        gearMatrix[i][j] = line.at(j);
      i = i + 1;
    }

    gearRatios = findGearRatios(gearMatrix);

    for (long long int gearRatio: gearRatios){
      sumResult = sumResult + gearRatio;
    }

    std::cout << "What is the sum of all of the part numbers in the engine schematic? "; 
    std::cout << sumResult << '\n';

}
