#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>

#define RED 12
#define GREEN 13 
#define BLUE 14

int main(void)
{
    std::ifstream inFile;
    std::stringstream buffer, second_buffer;
    std::string line, gameInfo, gameStr, cubeColor, gameCube;
    int gameID = 0, sumProducts = 0, cubeCount = 0 ;
    int min_red = 0, min_green = 0, min_blue = 0;
    char punctuation;

    inFile.open("input");
    for( std::string line; getline( inFile, line ); ){
      std::stringstream game(line);
      getline(game, gameInfo, ':');
      std::istringstream(gameInfo) >> gameStr >> gameID >> punctuation;
      min_red = 0;
      min_green = 0;
      min_blue = 0;
      while (getline(game, gameInfo, ';')) {
        std::stringstream gameSet(gameInfo);
        while (getline(gameSet, gameCube, ',')) {
          std::istringstream(gameCube) >> cubeCount >> cubeColor;
          if (cubeColor == "red")
            if (min_red < cubeCount)
              min_red = cubeCount;
          if (cubeColor == "green")
            if (min_green < cubeCount)
              min_green = cubeCount;
          if (cubeColor == "blue")
            if (min_blue < cubeCount)
              min_blue = cubeCount;
        }
      }
      // here sum up product
      sumProducts = sumProducts + (min_red * min_green * min_blue);
    }

    std::cout << "What is the sum of the IDs of those games? "; 
    std::cout << sumProducts << '\n';
    inFile.close();
}
