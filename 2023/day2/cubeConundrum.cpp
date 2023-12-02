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
    int gameID = 0, sumGameIDs = 0, cubeCount = 0, redGameCnt = 0, greenGameCnt = 0, blueGameCnt = 0;
    char punctuation;
    bool gameOK = true;

    inFile.open("input");
    for( std::string line; getline( inFile, line ); ){
      std::stringstream game(line);
      getline(game, gameInfo, ':');
      std::istringstream(gameInfo) >> gameStr >> gameID >> punctuation;
      redGameCnt = 0;
      greenGameCnt = 0;
      blueGameCnt = 0;
      gameOK = true;
      while (getline(game, gameInfo, ';')) {
        std::stringstream gameSet(gameInfo);
        while (getline(gameSet, gameCube, ',')) {
          std::istringstream(gameCube) >> cubeCount >> cubeColor;
          //std::cout << cubeColor << ':' << cubeCount << '\n' ;
          if (((cubeCount > RED) && (cubeColor == "red") ) || \
              ((cubeCount > GREEN) && (cubeColor == "green")) || \
              ((cubeCount > BLUE) && (cubeColor == "blue"))) {
            gameOK = false;
            break;
          }
        }
        if (!gameOK)
          break;
      }
      if (gameOK) {
        sumGameIDs = sumGameIDs + gameID;
      }
    }

    std::cout << "What is the sum of the IDs of those games? "; 
    std::cout << sumGameIDs << '\n';
    inFile.close();
}
