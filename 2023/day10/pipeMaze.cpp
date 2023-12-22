#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>
#include <ranges>

struct point2D{
  int x;
  int y;
};

/*
| is a vertical pipe connecting north and south.
- is a horizontal pipe connecting east and west.
L is a 90-degree bend connecting north and east.
J is a 90-degree bend connecting north and west.
7 is a 90-degree bend connecting south and west.
F is a 90-degree bend connecting south and east.
. is ground; there is no pipe in this tile.
S is the starting position of the animal; there is a pipe on this tile, but your sketch doesn't show what shape the pipe has.
*/

void printMaze(auto visitedMaze)
{
  std::cout << "Maze --------------------------------------\n";
  for (auto v: visitedMaze){
    for (auto c: v){
      if (c != -1){
        if (c > 9)
          std::cout << c << "  ";
        else
          std::cout << ' ' << c << "  ";
      }
      else
        std::cout << "--" << "  ";
    }
    std::cout << '\n';
  }
  std::cout << "---- --------------------------------------\n";
}

bool is_valid(int x, int y, int n, int m, 
              std::vector<std::string> pipeMaze,
              std::vector<std::vector<long int>> pipesVisited)
{
  if ( ( x >= 0 && x < n) && ( y >= 0 && y < m) )
    if ( (pipesVisited.at(y).at(x) == -1) && (pipeMaze.at(y).at(x) != '.') )
      return true;
  return false;
}

void findPath(int x, int y, int n, int m, \
              std::vector<std::string> pipeMaze, \
              std::vector<std::vector<long int>> &pipesVisited, \
              long int steps, int delta_y, int delta_x)
{
    pipesVisited.at(y).at(x) = steps;
    int next_x, next_y;
    next_x = x + delta_x;
    next_y = y + delta_y;
    if (pipesVisited.at(next_y).at(next_x) == 0){
      std::cout << "How many steps along the loop does it take to get from the starting position to the point farthest from the starting position? " << (steps + 1) / 2 << '\n'; 
    }
    if ( is_valid(next_x, next_y, n, m, pipeMaze, pipesVisited) ) { 
      if (delta_x == 1 and delta_y == 0) {               //right
        if (pipeMaze.at(next_y).at(next_x) == '-'){       
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  0,  1);
        }
        else if (pipeMaze.at(next_y).at(next_x) == 'J'){  
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1, -1,  0);
        }
        else if (pipeMaze.at(next_y).at(next_x) == '7'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  1,  0);
        }
      }
      else if (delta_x == -1 and delta_y == 0) {         //left
        if (pipeMaze.at(next_y).at(next_x) == '-'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  0, -1);
        }
        else if (pipeMaze.at(next_y).at(next_x) == 'F'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  1,  0);
        }
        else if (pipeMaze.at(next_y).at(next_x) == 'L'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1, -1,  0);
        }
      }
      else if (delta_x == 0 and delta_y == -1){           //up
        if (pipeMaze.at(next_y).at(next_x) == '|'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1, -1,  0);
        }
        else if (pipeMaze.at(next_y).at(next_x) == 'F'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  0,  1);
        }
        else if (pipeMaze.at(next_y).at(next_x) == '7'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  0, -1);
        }
        
      }
      else if (delta_x == 0 and delta_y == 1){            //down
        if (pipeMaze.at(next_y).at(next_x) == '|'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  1,  0);
        }
        else if (pipeMaze.at(next_y).at(next_x) == 'J'){ 
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  0, -1);
        }
        else if (pipeMaze.at(next_y).at(next_x) == 'L'){
          findPath(next_x, next_y, n, m, pipeMaze, pipesVisited, steps+1,  0,  1);
        }
      }
    }
}


int main(void)
{
    std::ifstream inFile;
    std::string pipesLine;
    std::vector<std::string> pipeMaze;
    std::vector<std::vector<long int>> pipesVisited;
    point2D entryPoint;
    int x_move[] = {-1,  0, 1, 0};
    int y_move[] = { 0, -1, 0, 1};

    inFile.open("input.txt");
//    inFile.open("test.txt");
    size_t col = 0;
    int rows = 0;
    for( std::string line; getline( inFile, pipesLine ); ){
      if (pipesLine.find("S") != std::string::npos){
        col = pipesLine.find("S");
        entryPoint.x = col;
        entryPoint.y = rows; 
      }
      pipeMaze.push_back(pipesLine);
      pipesVisited.push_back(std::vector<long int>(pipesLine.length(),-1));
      rows++;
    }
    int n = pipeMaze.at(0).length();
    int m = rows;

    int steps = 0;
//    printMaze(pipesVisited);
//    pipesVisited.at(entryPoint.y).at(entryPoint.x) = steps;
    int next_x, next_y;
    int delta_x, delta_y;
    for (int k=0; k < 4; k++) {
      next_x = entryPoint.x + x_move[k];
      next_y = entryPoint.y + y_move[k];
      delta_x = next_x - entryPoint.x;
      delta_y = next_y - entryPoint.y;  
      if ( is_valid(next_x, next_y, n, m, pipeMaze, pipesVisited) ) { 
        findPath(entryPoint.x , entryPoint.y, n, m, pipeMaze, pipesVisited, steps, delta_y,  delta_x);
      }
    }

    inFile.close();
}
