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


void printLayout(auto visitedLayout)
{ 
  std::cout << "Layout --------------------------------------\n";
  for (auto v: visitedLayout){
    for (auto c: v){
      std::cout << c << " ";
    }
    std::cout << '\n';
  }
  std::cout << "---- --------------------------------------\n";
}


bool is_valid(int x, int y, int n, int m, std::vector<std::string> layout, std::vector<std::vector<int>> visitedLayout)
{
  if ( ( ( x >= 0 ) && ( x < n ) ) && ( ( y >= 0 ) && ( y < m ) ) )
    if ((visitedLayout.at(y).at(x) == 0) or \
        (layout.at(y).at(x) == '.') or \
        (layout.at(y).at(x) == '\\') or \
        (layout.at(y).at(x) == '/'))
      return true;
  return false;
}

void energize(int x, int y, int n, int m, \
              std::vector<std::string> layout, \
              std::vector<std::vector<int>> &visitedLayout, \
              int dir_x, int dir_y)
{
  if ( is_valid(x, y, n, m, layout, visitedLayout) ){
  //  printLayout(visitedLayout);
    std::cout << "Energized: " << x << ' ' << y << ' ' << visitedLayout.at(y).at(x) + 1 << '\n';
    std::cout << "dir_x: " << dir_x << " dir_y: " << dir_y << '\n';
    if (layout.at(y).at(x) == '.'){       //continue moving towards dir_x or dir_y
      visitedLayout.at(y).at(x)++;
      std::cout << '.' << ' ' << dir_x << ' ' << dir_y << '\n';
      if (dir_x != 0)
        energize(x + dir_x, y, n, m, layout, visitedLayout, dir_x, 0);
      else if (dir_y != 0)
        energize(x, y + dir_y, n, m, layout, visitedLayout, 0, dir_y);
    }
    else if (layout.at(y).at(x) == '|'){
      visitedLayout.at(y).at(x) = 1;
      std::cout << "|" << ' ' << dir_x << ' ' << dir_y << '\n';
      if (dir_x != 0){
        std::cout << "dir_x != 0\n";
        energize(x, y - 1, n, m, layout, visitedLayout, 0, -1);
        energize(x, y + 1, n, m, layout, visitedLayout, 0,  1);
      }
      else{
        std::cout << "dir_x == 0\n";
        energize(x, y + dir_y, n, m, layout, visitedLayout, 0, dir_y);
      }
    }
    else if (layout.at(y).at(x) == '-'){
      visitedLayout.at(y).at(x) = 1;
      std::cout << '-' << ' ' << dir_x << ' ' << dir_y << '\n';
      if (dir_y != 0){
        std::cout << "dir_y != 0\n";
        energize(x - 1, y, n, m, layout, visitedLayout, -1, 0);
        energize(x + 1, y, n, m, layout, visitedLayout,  1, 0);
      }
      else{
        std::cout << "dir_y == 0\n";
        energize(x + dir_x, y, n, m, layout, visitedLayout, dir_x, 0);
      }
    }
    else if (layout.at(y).at(x) == '\\'){
      visitedLayout.at(y).at(x) = 1;
      std::cout << '\\' << ' ' << dir_x << ' ' << dir_y << '\n';
      if (dir_x == -1)
        energize(x, y - 1, n, m, layout, visitedLayout,  0, -1);
      else if (dir_x == 1)
        energize(x, y + 1, n, m, layout, visitedLayout,  0,  1);
      else if (dir_y == -1) 
        energize(x - 1, y, n, m, layout, visitedLayout, -1,  0);
      else if (dir_y == 1)
        energize(x + 1, y, n, m, layout, visitedLayout,  1,  0);
    }
    else if (layout.at(y).at(x) == '/'){
      visitedLayout.at(y).at(x) = 1;
      std::cout << '/' << ' ' << dir_x << ' ' << dir_y << '\n';
      if (dir_x == -1)
        energize(x, y + 1, n, m, layout, visitedLayout,  0,  1);
      else if (dir_x == 1)
        energize(x, y - 1, n, m, layout, visitedLayout,  0, -1);
      else if (dir_y == -1) 
        energize(x + 1, y, n, m, layout, visitedLayout,  1,  0);
      else if (dir_y == 1)
        energize(x - 1, y, n, m, layout, visitedLayout, -1,  0);
    }
  }
}

int main(void)
{
  std::ifstream inFile;
  std::vector<std::string> layout;
  std::vector<std::vector<int>> energizedLayout;

  inFile.open("input.txt");
//  inFile.open("test.txt");
  for( std::string layoutLine; getline( inFile, layoutLine ); ){
    std::cout << layoutLine << '\n';
    layout.push_back(layoutLine);
    energizedLayout.push_back(std::vector<int>(layoutLine.length(), 0));
  }

  int n = layout.at(0).length();
  int m = layout.size();

//  printLayout(energizedLayout);
  energize(0, 0, n, m, layout, energizedLayout, 1, 0);
//  printLayout(energizedLayout);

  int energizedTiles = 0; 
  for (auto v: energizedLayout)
    for (auto i: v)
      if (i > 0)
        energizedTiles++;  
  std::cout << "how many tiles end up being energized? "; 
  std::cout << energizedTiles << '\n';
  inFile.close();
}
