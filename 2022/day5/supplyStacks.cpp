#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>

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
    std::stringstream inputFile;
    std::string line;
    std::deque<std::deque<char>> supplyStacks = {{},{},{},{},{},{},{},{},{}};
//    std::deque<std::stack<char>> supplyStacks = {{},{},{},{},{},{},{},{},{}};
    std::deque<char> stack;
    int i, j;
    char stackPackage;

    inputFile = readFile((char*)"input");
    int moves = 0;
    while (getline (inputFile, line, '\n')) {
        if (line == "") { // move starts
            moves = 1;
            for(std::deque<char> c_q : supplyStacks) {
                std::cout << "----" << std::endl;
                for (char c: c_q) {
                    std::cout << c;
                }
                std::cout << std::endl;
            }
            continue;
        }
        if (moves == 1) {
            std::cout << line << std::endl;
            std::stringstream moves(line);
            int move = 0;
            int from = 0;
            int to = 0;
            int how_many_moves = 0;
            int move_from = -1;
            int move_to = -1; 
            for(std::string word; moves >> word; ) {
                if ( move == 1 )
                {
                    how_many_moves = std::stoi(word);
                    move = 0;
                }
                if ( from == 1) 
                {
                    move_from = std::stoi(word);
                    from = 0;
                }
                if ( to == 1)
                {
                    move_to = std::stoi(word);
                    to = 0;
                }

                if ( word == "move" )
                    move = 1;
                if ( word == "from" )
                    from = 1;
                if ( word == "to" )
                    to = 1;
            }

            std::cout << "before " << how_many_moves << " " << move_from << " " << move_to << std::endl;  
            for ( j = 0; j < how_many_moves; j++) {
                stackPackage = supplyStacks.at(move_from-1).back();
                supplyStacks.at(move_from-1).pop_back();
                supplyStacks.at(move_to-1).push_back(stackPackage);
            }
            std::cout << "After " << std::endl;  
            for(std::deque<char> c_q : supplyStacks) {
                std::cout << "----" << std::endl;
                for (char c: c_q) {
                    std::cout << c;
                }
                std::cout << std::endl;
            }
        }
        else {  //read stacks
//           std::cout << line<< std::endl;
           for ( i = 0; i < 9; i++ ) {
               if ( (line.at(1+(i*4)) != ' ') && !std::isdigit(line.at(1+(i*4)))) {
                   std::cout << line.at(1+(i*4)) << " ";
                   supplyStacks[i].push_front(line.at(1+(i*4)));
               }
               else
                   std::cout << "  ";
           }
           //supplyStacks.push_back(stack);
           std::cout << std::endl;
        }
    }
    
    std::cout << "After the rearrangement procedure completes, what crate ends up on top of each stack? ";
    for (i = 0; i < 9 ; i++)
        std::cout << supplyStacks[i].back();

    std::cout << std::endl;

    return 1;
}
