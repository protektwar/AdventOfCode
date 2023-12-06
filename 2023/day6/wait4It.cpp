#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <algorithm>


int main(void)
{
    std::ifstream inFile;
    std::string line, raceTimeStr, timeInfoStr, raceDistanceStr, distanceInfoStr;
    std::vector<int> raceTimes;
    std::vector<int> raceDistances;


    inFile.open("input");
//    inFile.open("demo");
    int cardIndex = 0;
    getline( inFile, line );
    std::stringstream time(line);
    getline(time, timeInfoStr, ':');
    getline(time, timeInfoStr, ':');
    std::stringstream timeInfo(timeInfoStr);
    while (getline(timeInfo, raceTimeStr, ' ')){
        if (raceTimeStr != "")
          raceTimes.push_back(std::stoi(raceTimeStr));
    }

    getline( inFile, line );
    std::stringstream distance(line);
    getline(distance, distanceInfoStr, ':');
    getline(distance, distanceInfoStr, ':');
    std::stringstream distanceInfo(distanceInfoStr);
    while (getline(distanceInfo, raceDistanceStr, ' ')){
        if (raceDistanceStr != "")
          raceDistances.push_back(std::stoi(raceDistanceStr));
    }

    std::vector<int> recordBeatenTimes;
    int beatenRecords;
//    for (int raceTime: raceTimes){
    for (auto it = raceTimes.begin(); it != raceTimes.end(); ++it){
      beatenRecords = 0;
      int index = it - raceTimes.begin();
      int raceTime = raceTimes.at(index);
      for (int i = 1; i <= raceTime; i++){
        if (i * (raceTime-i) > raceDistances.at(index))
          beatenRecords = beatenRecords + 1;
      }
      recordBeatenTimes.push_back(beatenRecords);
    }

    long long int recordBeatenProduct = 1;    
    for (int recordBeatenTime: recordBeatenTimes)
      recordBeatenProduct = recordBeatenProduct * recordBeatenTime;
    
    std::cout << "What do you get if you multiply these numbers together? "; 
    std::cout << recordBeatenProduct << '\n';
    inFile.close();
}
