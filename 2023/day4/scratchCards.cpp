#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>

int main(void)
{
    std::ifstream inFile;
    std::stringstream buffer, second_buffer;
    std::string line, gameInfo, cardStr, cubeColor, gameCube;
    int cardID, cardPoints = 0;
    long int cardTotalPoints = 0;
    char punctuation;
    std::vector<int> cardsExtracted, cardsOwned;

    inFile.open("input");
    for( std::string line; getline( inFile, line ); ){
      std::stringstream game(line);
      getline(game, gameInfo, ':');
      std::istringstream(gameInfo) >> cardStr >> cardID >> punctuation;
      int i = 0;
      cardsExtracted.clear();
      cardsOwned.clear();
      while (getline(game, gameInfo, '|')) {
        std::stringstream cards(gameInfo);
        while (getline(cards, cardStr, ' ')) {
          if (cardStr != ""){
            if (i == 0)
              cardsExtracted.push_back(std::stoi(cardStr));
            else  
              cardsOwned.push_back(std::stoi(cardStr));
          }
        }
        i = i + 1;
      }
      bool firstCard  = false;
      cardPoints = 0;
      for (int card: cardsExtracted){
        if ( std::find(cardsOwned.begin(), cardsOwned.end(), card) != cardsOwned.end() ){
          if (!firstCard){
            cardPoints = 1;
            firstCard = true;
          }
          else
            cardPoints = cardPoints * 2;
        }
      }
      cardTotalPoints = cardTotalPoints + cardPoints; 
    }

    std::cout << "How many points are they worth in total? "; 
    std::cout << cardTotalPoints << '\n';
    inFile.close();
}
