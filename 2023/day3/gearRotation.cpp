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

bool checkAdjacent(int line, int col, int partLength, const char gearMatrix[N][N])
{
  for (int i = line - 1; i <= line + 1; i++)
    for (int j = col-partLength-1; j <= col; j++)
      if (((i >= 0) && (i < N)) && ((j >= 0) && (j < N))){
        if ( (j < col-partLength) || (j > col-1) || (i != line) ) {
          if ( (gearMatrix[i][j] != '.') || \
               ((gearMatrix[i][j] <= '0') && (gearMatrix[i][j] >= '9') )
             ){
            return true;
          }
        }
      }
  return false;
}

std::vector<long long int> findPartNumbers(const char gearMatrix[N][N])
{
  std::vector<long long int> returnPartNumbers;
  std::string partNumber = "";

  for (int i = 0; i < N; i++)
    for (int j = 0; j < N; j++) {
      if ((gearMatrix[i][j] >= '0') && (gearMatrix[i][j] <= '9')){
        partNumber = partNumber + gearMatrix[i][j];
        if (j == (N-1)){
          if (partNumber != ""){
            if (checkAdjacent(i, j+1, partNumber.length(), gearMatrix)){
              returnPartNumbers.push_back(std::stoi(partNumber));
            }
            partNumber = "";
          }
        }
      }
      else {
        if (partNumber != ""){
          if (checkAdjacent(i, j, partNumber.length(), gearMatrix)){
            returnPartNumbers.push_back(std::stoi(partNumber));
          }
          partNumber = "";
        }
      }
    }
  return returnPartNumbers;
}

int main(void)
{
    std::stringstream bufferFromFile;
    std::string line;
    char gearMatrix[N][N]; 
    long int sumResult = 0;
    std::vector<long long int> partNumbers;
 
    int i = 0;
    bufferFromFile = readFile((char*)"input");
    //bufferFromFile = readFile((char*)"demo");
    while (getline (bufferFromFile, line, '\n')) {
      for (int j = 0; j < line.length(); j++)
        gearMatrix[i][j] = line.at(j);
      i = i + 1;
    }

    partNumbers = findPartNumbers(gearMatrix);

    for (long long int partNumber: partNumbers){
      sumResult = sumResult + partNumber;
    }

    std::cout << "What is the sum of all of the part numbers in the engine schematic? "; 
    std::cout << sumResult << '\n';

}
