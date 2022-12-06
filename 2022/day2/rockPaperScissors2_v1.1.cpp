#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>

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


int main(void)
{
    std::stringstream games;
    std::string game;
    games = readFile((char*)"input");
    char elf, mySelf;
    int player;
    int score = 0, loseWin, amount, realLoseWin;

    while (getline (games, game, '\n')) {
        player = 0;
        game = game + ' ';
        std::stringstream second_buffer(game);
        for(std::string game_move; second_buffer >> game_move; )
        {
//      while ( getline((std::stringstream) game, game_move, ' ' ) ) {
            if (player == 0)
            {
                elf = game_move[0];
            }
            else
            {
                mySelf = game_move[0];
            }
            player++;
        }
        
        // loseWin values
        // 2 win 
        // 1 draw 
        // 0 lose 
        loseWin = (mySelf+2)%3;
        amount = (elf+1)%3+1;
        realLoseWin = 3 * (loseWin);
        amount = ((realLoseWin+amount+mySelf)%3 + 1);
        // realLoseWin values
        // 0 lose
        // 3 draw 
        // 6 win
        score += realLoseWin + amount;
        std::cout << elf << " " << mySelf << " " << loseWin << " Amount:" << amount << " LoseWin: " << realLoseWin << " " << score;
        std::cout << " " << ((realLoseWin+amount+mySelf)%3 + 1);
        std::cout << '\n';
    }

    std::cout << "What would your total score be if everything goes exactly according to your strategy guide? "; 
    std::cout << score;

}
