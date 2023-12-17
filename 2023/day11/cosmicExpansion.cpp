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

struct position2D{
    int x;
    int y;
}point2D, start, end;

int main(void)
{
    std::ifstream inFile;
    std::string galaxyLine;
    std::vector<position2D> galaxyWorld;

    inFile.open("input");
//    inFile.open("test");
    int row = 1;
    int col = 1;
    for( std::string line; getline( inFile, galaxyLine ); ){
      col = 1;
      position2D galaxyPoint;
      for (char c: galaxyLine){
        if (c == '#'){
          galaxyPoint.x = col;
          galaxyPoint.y = row; 
          galaxyWorld.push_back(galaxyPoint);
        }
        col++;
      }
      row++;
    }
    
    long long int distanceFarthest = 0;
    std::vector<std::pair<int, int>> pairs;
    for (int i = 0; i < galaxyWorld.size() ; i++)
      for (int k = i+1; k < galaxyWorld.size(); k++)
        pairs.push_back(std::make_pair(i,k));

    std::vector<int> distances;
    int distance = 0;
    for (auto pair: pairs){
      distance = abs(galaxyWorld.at(pair.first).x - galaxyWorld.at(pair.second).x) + abs(galaxyWorld.at(pair.first).y - galaxyWorld.at(pair.second).y);
      distances.push_back(distance);
    }
    std::vector<int> cols;
    std::vector<int> rows;
    for (int i = 0; i < galaxyWorld.size(); i++){
      if (!std::count(cols.begin(), cols.end(), galaxyWorld.at(i).x))
        cols.push_back(galaxyWorld.at(i).x);
      if (!std::count(rows.begin(), rows.end(), galaxyWorld.at(i).y))
        rows.push_back(galaxyWorld.at(i).y);
    }
    sort(cols.begin(), cols.end());
    sort(rows.begin(), rows.end());

    for (auto dist: distances)
      distanceFarthest += dist;
    for (int i = 1; i < col; i++)
      if (!std::count(cols.begin(), cols.end(), i))
        for (auto pair: pairs)
          if ((i > galaxyWorld.at(pair.first).x && i < galaxyWorld.at(pair.second).x) || (i > galaxyWorld.at(pair.second).x && i < galaxyWorld.at(pair.first).x))
            distanceFarthest += 1;

    for (int i = 1; i < row; i++)
      if (!std::count(rows.begin(), rows.end(), i))
        for (auto pair: pairs)
          if (i > galaxyWorld.at(pair.first).y && i < galaxyWorld.at(pair.second).y)
            distanceFarthest += 1;
    
    std::cout << "How many steps along the loop does it take to get from the starting position to the point farthest from the starting position? "; 
    std::cout << distanceFarthest << '\n';
    inFile.close();
}
