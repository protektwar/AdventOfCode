#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
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
    std::string line, networkOrder, nodeName, nodeNameL, nodeNameR, nodeFoundStr, entryNodeStr1, entryNodeStr2;    
    std::map<std::string, std::pair<std::string, std::string>> networkNodes;
    std::vector<std::string> networkNodeA;
    std::vector<long long int> numberss;

    inFile.open("input");
//    inFile.open("test1");
    getline(inFile, networkOrder); 
    getline(inFile, line); 
    for( std::string line; getline( inFile, line ); ){
      std::stringstream hand(line);
      getline(hand, nodeName, '='); getline(hand, nodeNameL, ','); getline(hand, nodeNameR, ',');
      nodeName = trim(nodeName); nodeNameL = trim(nodeNameL); nodeNameR = trim(nodeNameR);
      nodeNameL = nodeNameL.substr(nodeNameL.find('(')+1);
      nodeNameR = nodeNameR.substr(0,nodeNameR.find(')'));
      networkNodes[nodeName] = std::make_pair(nodeNameL, nodeNameR);
      if (nodeName.at(2) == 'A') networkNodeA.push_back(nodeName); 
    }
    std::cout << "test1" << '\n';
    entryNodeStr1 = networkNodeA.at(0); entryNodeStr2 = networkNodeA.at(1);
    std::pair<std::string, std::string> nodePair1, nodePair2; 
    std::cout << "start nodes: " <<networkNodeA.size() << '\n';
    for (int i = 0; i < networkNodeA.size(); i++) {
      int indexNetworkOrder=0;
      long long int totalSteps1 = 0;
      entryNodeStr1 = networkNodeA.at(i);
      //while ((entryNodeStr1.at(2) != 'Z') && (entryNodeStr2.at(2) != 'Z')){
      while ((entryNodeStr1.at(2) != 'Z')){
        nodePair1 = networkNodes[entryNodeStr1]; nodePair2 = networkNodes[entryNodeStr2];
        if (networkOrder.at(indexNetworkOrder % networkOrder.length()) == 'L'){
          entryNodeStr1 = nodePair1.first; entryNodeStr2 = nodePair2.first;
          totalSteps1 = totalSteps1 + 1; 
        }
        else {
          entryNodeStr1 = nodePair1.second; entryNodeStr2 = nodePair2.second;
          totalSteps1 = totalSteps1 + 1; 
        }
//        std::cout << entryNodeStr1 << ' ' << entryNodeStr2 << '\n';
        indexNetworkOrder = indexNetworkOrder + 1;
      }
      std::cout << totalSteps1 << '\n';
      numberss.push_back(totalSteps1);
    }
    long long int totalSteps = 0;
    std::cout << "test2" << '\n';
    std::cout << numberss.size() << '\n';
    std::cout << "test3" << '\n';
    totalSteps = std::lcm(std::lcm(std::lcm(std::lcm(std::lcm(numberss.at(0), numberss.at(1)), numberss.at(2)), numberss.at(3)), numberss.at(4)), numberss.at(5));
   // totalSteps = std::lcm(numberss.at(0), numberss.at(1));
    std::cout << "How many steps does it take before you're only on nodes that end with Z? ";
    std::cout << totalSteps << '\n';
    inFile.close();
}
