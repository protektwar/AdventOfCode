#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>


#define N 40
#define M 60

struct vec_2d{
    int x;
    int y;
} rope[10],delta;

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
    char direction;
    int steps;
    int i, j, k, l;
    std::vector<std::pair<int,int>> tails;
    char ropeMatrix[N][M];

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            ropeMatrix[i][j] = '0';

    for (i = 0; i < 10; i++)
    {
        rope[i].x = 20;
        rope[i].y = 30;
    }
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
                    rope[0].x -= 1;
                    break;
                case 'R':
                    rope[0].y += 1;
                    break;
                case 'D':
                    rope[0].x += 1;
                    break;
                case 'L':
                    rope[0].y -= 1;
                    break;
            }
            std::cout << "head x: " << rope[0].x << " head.y: " << rope[0].y << std::endl;
//            ropeMatrix[rope[0].x][rope[0].y] = 'H';
            for (i = 1; i < 10 ; i++)
            {                
                delta.x = rope[i-1].x - rope[i].x;
                delta.y = rope[i-1].y - rope[i].y;
                if (delta.x == 0)
                {
                    rope[i].y += delta.y/2;
                }
                else if (delta.y == 0)
                {
                    rope[i].x += delta.x/2;
                }
                else
                {
                    if (abs(delta.x) == 1 && abs(delta.y) == 2)
                    {
                        rope[i].x += delta.x;
                        rope[i].y += delta.y/2;
                    }
                    else if (abs(delta.y) == 1 && abs(delta.x) == 2)
                    {
                        rope[i].x += delta.x/2;
                        rope[i].y += delta.y;
                    }
                    else //if (abs(delta.x) == 2 && abs(delta.y) == 2)
                    {
                        rope[i].x += delta.x/2;
                        rope[i].y += delta.y/2;
                    }
                }
//                ropeMatrix[rope[i].x][rope[i].y] = '0'+i;
                std::cout << "tail[" << i << "].x: " << rope[i].x << " tail[" << i << "].y: " << rope[i].y << std::endl;
            }
/*
            for (i = 0; i < N; i++)
            {                
                for (j = 0; j < M; j++)
                    std::cout << ropeMatrix[i][j] ;
                std::cout << std::endl;
            }
            for (i = 0; i < N; i++)
                for (j = 0; j < M; j++)
                    ropeMatrix[i][j] = '0' ;*/
            if ( auto it = std::ranges::find(tails.begin(), tails.end(), std::make_pair(rope[9].x,rope[9].y)); it == tails.end() )
                tails.push_back(std::make_pair(rope[9].x, rope[9].y));
        }
    }
   
    std::cout << "How many positions does the tail of the rope visit at least once? ";
    std::cout << tails.size() << std::endl; 

    return 1;
}
