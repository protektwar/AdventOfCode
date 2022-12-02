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
    int score = 0, loseWin, amount, a;

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
        // 0 lose
        // 3 draw 
        // 6 win
        
        loseWin = (mySelf-elf+2)%3;
        amount = (mySelf+2)%3+1;
        a = 3 * loseWin;
//        score += 3*loseWin + amount;
        score += a + amount;
        std::cout << elf << " " << mySelf << " " << loseWin << " " << amount << " " << score << " "<< a<< '\n';


        // 2 draw
        // 1 win 
        // 0 lose 
    }

    std::cout << "What would your total score be if everything goes exactly according to your strategy guide? "; 
    std::cout << score;

}
