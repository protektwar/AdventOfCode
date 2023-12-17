#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <ranges>
#include <cstddef>        // std::size_t

int main(void)
{
    std::ifstream inFile;
    std::string line, numberStr;

    inFile.open("input");
//    inFile.open("test");
    int sum = 0;
    std::vector<int> temp; 
    std::vector<int> temp1; 
    std::vector<std::vector<std::vector<int>>> serieVectors; 
    std::vector<std::vector<int>> seriesVector; 
    for( std::string line; getline( inFile, line ); ){
      std::stringstream series(line);
      temp.clear();
      seriesVector.clear();
      while (getline(series, numberStr, ' ')){
        if (numberStr != ""){ 
          temp.push_back(std::stoi(numberStr));
        }
      }
      do {
        sum = 0;
        seriesVector.push_back(temp);
        for (int i = 0; i < temp.size()-1; i++){
          temp1.push_back(temp.at(i+1) - temp.at(i));
          sum = sum + (temp.at(i+1) - temp.at(i));
        }
        temp.clear();
        temp.assign(temp1.begin(), temp1.end());
        temp1.clear();
      } while (sum != 0);
      serieVectors.push_back(seriesVector);
    }

    long long int extrapolatedValuesSum = 0;
    for(std::vector<std::vector<int>> s_vectors: serieVectors){
      std::reverse(s_vectors.begin(), s_vectors.end());
      int numberA = 0;
      for(std::vector<int> s_vector: s_vectors){
        numberA = numberA + s_vector.back(); 
      }
      extrapolatedValuesSum = extrapolatedValuesSum + numberA;
      
    }

    
    std::cout << "What is the sum of these extrapolated values? "; 
    std::cout << extrapolatedValuesSum << '\n';
    inFile.close();
}
