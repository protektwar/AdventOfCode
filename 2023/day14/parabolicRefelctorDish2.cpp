#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <set>
#include <algorithm>
#include <ranges>
#include <boost/math/special_functions/factorials.hpp>

void printBoard(std::vector<std::vector<char>> board)
{
  std::cout << "Board: \n";
  for (auto rowRocks: board){
    for (auto rock: rowRocks)
      std::cout << rock;
    std::cout << '\n';
  }
  std::cout << "------- \n";
}

void tiltBoardNorth(std::vector<std::vector<char>> &board)
{
  for (auto it = board.begin(); it != board.end(); ++it){ 
    int index = it - board.begin();
    std::vector<char> rowRocks = board.at(index);
    if (index != 0){
      for (int rockPos = 0; rockPos < rowRocks.size(); rockPos++){
        if (rowRocks.at(rockPos) == 'O'){
          for (int i = index-1; i >= 0; i--){
            if (((board.at(i).at(rockPos) == '#') || (board.at(i).at(rockPos) == 'O'))){
              break;
            }
            if (board.at(i).at(rockPos) == '.'){
              board.at(i).at(rockPos) = 'O';
              board.at(i+1).at(rockPos) = '.';
            }
          }
        }
      }
    }
  }
}

void tiltBoardSouth(std::vector<std::vector<char>> &board)
{
  for (auto it = board.end(); it != board.begin(); --it){ 
    int index = (it - board.begin())-1;
    std::vector<char> rowRocks = board.at(index);
    if (index != ((board.end()-board.begin())-1)){
      for (int rockPos = 0; rockPos < rowRocks.size(); rockPos++){
        if (rowRocks.at(rockPos) == 'O'){
          for (int i =index+1 ; i <= ((board.end()-board.begin())-1); i++){
            if (((board.at(i).at(rockPos) == '#') || (board.at(i).at(rockPos) == 'O'))){
              break;
            }
            if (board.at(i).at(rockPos) == '.'){
              board.at(i-1).at(rockPos) = '.';
              board.at(i).at(rockPos) = 'O';
            }
          }
        }
      }
    }
  }
}

void tiltBoardWest(std::vector<std::vector<char>> &board)
{
  for (auto col = 0; col < board.at(0).size(); col++){ 
    if (col != 0){
      for (auto it=board.begin(); it != board.end(); ++it){
        int row = it - board.begin();
        if (board.at(row).at(col) == 'O'){
          for (int i = col-1; i >= 0; i--){
            if (((board.at(row).at(i) == '#') || (board.at(row).at(i) == 'O'))){
              break;
            }
            if (board.at(row).at(i) == '.'){
              board.at(row).at(i) = 'O';
              board.at(row).at(i+1) = '.';
            }
          }
        }
      }
    }
  }
}

void tiltBoardEast(std::vector<std::vector<char>> &board)
{
  for (int col = (board.at(0).size()-1); col >= 0; col--){
    if (col != (board.at(0).size()-1)){
      for (auto it=board.begin(); it != board.end(); ++it){
        int row = it - board.begin();
        if (board.at(row).at(col) == 'O'){
          for (int i = col+1; i <= (board.at(0).size()-1); i++){
            if (((board.at(row).at(i) == '#') || (board.at(row).at(i) == 'O'))){
              break;
            }
            if (board.at(row).at(i) == '.'){
              board.at(row).at(i-1) = '.';
              board.at(row).at(i) = 'O';
            }
          }
        }
      }
    }
  }
}

int main(void)
{
    std::ifstream inFile;
    std::string rowBoard;
    std::vector<std::vector<char>> rocksBoard;

    inFile.open("input.txt");
//    inFile.open("test.txt");
    for( std::string line; getline( inFile, rowBoard ); ){
      std::vector<char> rowRocks;
      for (char c: rowBoard)
          rowRocks.push_back(c);
      rocksBoard.push_back(rowRocks);
    }
    for (int cycle = 0; cycle < 1000; cycle++){
      printBoard(rocksBoard);
      tiltBoardNorth(rocksBoard);
      tiltBoardWest(rocksBoard);
      tiltBoardSouth(rocksBoard);
      tiltBoardEast(rocksBoard);
    } 
    printBoard(rocksBoard);
    
    long long int totalLoad = 0;
    for (auto it = rocksBoard.begin(); it != rocksBoard.end(); ++it){ 
      int index = it - rocksBoard.begin();
      std::vector<char> rowRocks = rocksBoard.at(index);
      int rocksNr = 0;
      for (int rockPos = 0; rockPos < rowRocks.size(); rockPos++){
        if (rowRocks.at(rockPos) == 'O')
          rocksNr++;
      }   
      totalLoad = totalLoad + ((rowRocks.size()-index)*rocksNr);
    }   
    std::cout << "What is the total load on the north support beams? "; 
    std::cout << totalLoad << '\n';
    inFile.close();
}
