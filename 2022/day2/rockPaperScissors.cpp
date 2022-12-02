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
    int score = 0;

    while (getline (games, game, '\n')) {
        std::cout << game <<'\n';
        player = 0;
        game = game + ' ';
        std::cout << '-' << game << '-';
        std::stringstream second_buffer(game);
        for(std::string game_move; second_buffer >> game_move; )
        {
//      while ( getline((std::stringstream) game, game_move, ' ' ) ) {
            std::cout << game_move << ' ';
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

        if (elf == 'A') //rock
        {
            if (mySelf == 'X') //rock 1
            {
                //draw
                score += 3 + 1;

            }
            else if (mySelf == 'Y') //paper 2
            {
                score += 6 + 2;
            }
            else if (mySelf == 'Z')//Scissors 3
            {
                score += 0 + 3;
            }
        }
        else if (elf == 'B') //paper
        {
            if (mySelf == 'X') // rock 1
            {
                score += 0 + 1;
            }
            else if (mySelf == 'Y') // paper 2
            {
                //draw
                score += 3 + 2;
            }
            else if (mySelf == 'Z') //Scissors 3
            {
                score += 6 + 3;
            }
        }
        else if (elf == 'C') //scissors
        { 
            if (mySelf == 'X') // rock 1
            {
                score += 6+ 1;
            }
            else if (mySelf == 'Y') // paper 2
            {
                score += 0 + 2;
            }
            else if (mySelf == 'Z') // scissors 3
            {
                //draw
                score += 3 + 3;
            }
        }
        std::cout << '\n';
    }

    std::cout << "What would your total score be if everything goes exactly according to your strategy guide?"; 
    std::cout << score;

}
