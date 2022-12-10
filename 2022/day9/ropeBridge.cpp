#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>


#define N 20
#define M 20

struct vec_2d{
    int x;
    int y;
} head, tail, delta;
std::stringstream readFile(char * filename)
{
    std::ifstream inFile;
    std::string line;
    std::stringstream buffer;

    inFile.open(filename);
    for( std::string line; getline( inFile, line ); )
    {   
        buffer << line << std::endl;
    }   

    return buffer;
}

int main(void)
{
    std::stringstream movements;
    std::string move, word;
    char direction, lastDirection = 'O';
    int steps;
    int i, j, k, l, totalTailMoves = 0 ;
    int x = 10, y = 10;
    int heading = 0;
    std::vector<std::pair<int,int>> tails;
    head.x = 0; head.y = 0;
    tail.x = 0; tail.y = 0;

    movements = readFile((char*)"input");
    while (getline (movements, move, '\n')) {
        std::stringstream toSplitString(move);
        int wordCnt = 0;
        while (getline (toSplitString, word,' ')){
            if (wordCnt == 0)
                direction = word[0];
            else
                steps = std::stoi(word);
            wordCnt ++;
        }
        std::cout << "dir: " << direction << " steps: " << steps << std::endl;
        for (int step = 0; step < steps; step++)
        {
            switch (direction){
                case 'U':
                    head.x += 1;
                    break;
                case 'R':
                    head.y += 1;
                    break;
                case 'D':
                    head.x -= 1;
                    break;
                case 'L':
                    head.y -= 1;
                    break;
            }
            std::cout << "head x: " << head.x << " head.y: " << head.y << std::endl;
            delta.x = head.x - tail.x;
            delta.y = head.y - tail.y;
            std::cout << "delta x: " << delta.x << " delta.y: " << delta.y << std::endl;
            if (delta.x == 0)
            {
                std::cout << "y\n";
                tail.y += delta.y/2;
            }
            else if (delta.y == 0)
            {
                std::cout << "x\n";
                tail.x += delta.x/2;
            }
            else
            {
                std::cout << "xy\n";
                if (abs(delta.x) == 1 && abs(delta.y) == 2)
                {
                    tail.x += delta.x;
                    tail.y += delta.y/2;
                }
                else if (abs(delta.y) == 1 && abs(delta.x) == 2)
                {
                    tail.x += delta.x/2;
                    tail.y += delta.y;
                }
            }
            std::cout << "tail x: " << tail.x << " tail.y: " << tail.y << std::endl;
            if ( auto it = std::ranges::find(tails.begin(), tails.end(), std::make_pair(tail.x,tail.y)); it == tails.end() )
                tails.push_back(std::make_pair(tail.x, tail.y));
        }
        std::cout << "---------------------\n";
    }
   
    std::cout << "How many positions does the tail of the rope visit at least once? ";
    std::cout << tails.size() << std::endl; 

    return 1;
}
