#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>


struct cardsPlay{
  std::vector<int> cardsExtracted;
  std::vector<int> cardsOwned;
};

std::vector<int> findMatches(std::vector<int> cardsExtracted, std::vector<int> cardsOwned)
{
  std::vector<int> matches;
  for (int card: cardsExtracted)
    if ( std::find(cardsOwned.begin(), cardsOwned.end(), card) != cardsOwned.end() )
      matches.push_back(card);
      
 return matches;
}

std::map<int, int> findCopies(std::map<int, cardsPlay> gamePlay)
{
  std::map<int, int> cardCopies;
  std::vector<int> matches, matches_;
  for (int i = 0; i < gamePlay.size(); i++)
    cardCopies[i] = 1;
  for(std::map<int, cardsPlay >::const_iterator it = gamePlay.begin(); it != gamePlay.end(); ++it){
    matches = findMatches(it->second.cardsExtracted, it->second.cardsOwned);
    for (int i = 1; i <= (matches.size()); i++){
      cardCopies[it->first+i] = cardCopies[it->first+i] + cardCopies[it->first];
    }
  }
  return cardCopies;
}

int main(void)
{
    std::ifstream inFile;
    std::stringstream buffer, second_buffer;
    std::string line, gameInfo, cardStr, cubeColor, gameCube;
    int cardID, cardPoints = 0;
    long int cardTotalPoints = 0;
    char punctuation;
    std::vector<int> cardsExtracted, cardsOwned;
    std::map<int, cardsPlay> gamePlay;
    cardsPlay playingCards;
    std::map<int, int> cardCopies, cardCopy;

    inFile.open("input");
//    inFile.open("demo");
    int cardIndex = 0;
    for( std::string line; getline( inFile, line ); ){
      std::stringstream game(line);
      getline(game, gameInfo, ':');
      std::istringstream(gameInfo) >> cardStr >> cardID >> punctuation;
      int i = 0;
      playingCards.cardsExtracted.clear();
      playingCards.cardsOwned.clear();
      while (getline(game, gameInfo, '|')) {
        std::stringstream cards(gameInfo);
        while (getline(cards, cardStr, ' ')) {
          if (cardStr != ""){
            if (i == 0)
              playingCards.cardsExtracted.push_back(std::stoi(cardStr));
            else  
              playingCards.cardsOwned.push_back(std::stoi(cardStr));
          }
        }
        i = i + 1;
      }
      gamePlay[cardIndex] = playingCards;
      cardIndex = cardIndex + 1; 
    }
    
    cardCopies = findCopies(gamePlay);
    int totalCardCopies = 0;
    for(std::map<int, int >::const_iterator it = cardCopies.begin(); it != cardCopies.end(); ++it){
      std::cout << it->first << " | " << it->second << '\n';
      totalCardCopies = totalCardCopies + it->second;
    }

    std::cout << "How many total scratchcards do you end up with? "; 
    std::cout << totalCardCopies << '\n';
    inFile.close();
}
