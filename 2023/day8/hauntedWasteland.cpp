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
#include <cstddef>        // std::size_t


inline std::string trim(const std::string &s)
{
   auto wsfront=std::find_if_not(s.begin(),s.end(),[](int c){return std::isspace(c);});
   auto wsback=std::find_if_not(s.rbegin(),s.rend(),[](int c){return std::isspace(c);}).base();
   return (wsback<=wsfront ? std::string() : std::string(wsfront,wsback));
}

int main(void)
{
    std::ifstream inFile;
    std::string line, networkOrder, nodeName, nodeNameL, nodeNameR, nodeFoundStr, entryNodeStr;
    std::map<std::string, std::pair<std::string, std::string>> networkNodes;

    inFile.open("input");
//    inFile.open("test1");
    getline(inFile, networkOrder); 
    getline(inFile, line); 
    for( std::string line; getline( inFile, line ); ){
      std::stringstream hand(line);
      getline(hand, nodeName, '=');
      getline(hand, nodeNameL, ',');
      getline(hand, nodeNameR, ',');
      nodeName = trim(nodeName);
      nodeNameL = trim(nodeNameL);
      nodeNameR = trim(nodeNameR);
      nodeNameL = nodeNameL.substr(nodeNameL.find('(')+1);
      nodeNameR = nodeNameR.substr(0,nodeNameR.find(')'));
      std::cout << "NodeName: " << nodeName << ' ';
      std::cout << "NodeNameL: " << nodeNameL << ' ';
      std::cout << "NodeNameR: " << nodeNameR << '\n';
      networkNodes[nodeName] = std::make_pair(nodeNameL, nodeNameR);
    }

    int indexNetworkOrder=0;
    long long int totalSteps = 0;
    entryNodeStr = networkNodes.begin()->first;
    std::pair<std::string, std::string> nodePair; 
    while (entryNodeStr != "ZZZ"){
      std::cout << (indexNetworkOrder % networkOrder.length()) << '\n';
      nodePair = networkNodes[entryNodeStr];
      std::cout << entryNodeStr << '\n';
      if (networkOrder.at(indexNetworkOrder % networkOrder.length()) == 'L'){
        entryNodeStr = nodePair.first;
        totalSteps = totalSteps + 1; 
      }
      else {
        entryNodeStr = nodePair.second;
        totalSteps = totalSteps + 1; 
      }
      indexNetworkOrder = indexNetworkOrder + 1;
    }

    std::cout << "How many steps are required to reach ZZZ? "; 
    std::cout << totalSteps << '\n';
    inFile.close();
}
