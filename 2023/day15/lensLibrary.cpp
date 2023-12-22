#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>


int hash(std::string sequence)
{
  int result = 0;
  for( auto c: sequence){
    result += c;
    result *= 17;
    result %= 256;
  }
  return result;
}

int main(void)
{
    std::ifstream inFile;
    std::string sequenceLine;

//    inFile.open("input.txt");
    inFile.open("test.txt");
    std::cout << hash("HASH") << '\n';
    getline( inFile, sequenceLine );
    std::stringstream sequences(sequenceLine);
    long long int hashSum = 0; 
    for (std::string sequence; getline(sequences, sequence, ','); ){
      hashSum += hash(sequence);  
      std::cout << hash(sequence) << '\n';
    }
    
    std::cout << "What is the sum of the results? " << '\n';
    std::cout << hashSum << '\n';
    inFile.close();
}
