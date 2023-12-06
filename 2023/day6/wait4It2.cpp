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
    std::string line, raceTimeStr, timeInfoStr, raceDistanceStr, distanceInfoStr, raceDistanceConcat = "", raceTimeConcat = "";
    long long int raceTime_;
    long long int raceDistance_;


    inFile.open("input");
//    inFile.open("test");
    int cardIndex = 0;
    getline( inFile, line );
    std::stringstream time(line);
    getline(time, timeInfoStr, ':');
    getline(time, timeInfoStr, ':');
    std::stringstream timeInfo(timeInfoStr);
    while (getline(timeInfo, raceTimeStr, ' ')){
        if (raceTimeStr != "")
          raceTimeConcat = raceTimeConcat + raceTimeStr;
    }
    raceTime_ = std::stoll(raceTimeConcat);

    getline( inFile, line );
    std::stringstream distance(line);
    getline(distance, distanceInfoStr, ':');
    getline(distance, distanceInfoStr, ':');
    std::stringstream distanceInfo(distanceInfoStr);
    while (getline(distanceInfo, raceDistanceStr, ' ')){
        if (raceDistanceStr != "")
          raceDistanceConcat = raceDistanceConcat + raceDistanceStr;
    }
    raceDistance_ = std::stoll(raceDistanceConcat);

    int beatenRecord = 0;
    for (int i = 1; i <= raceTime_; i++){
      if (i * (raceTime_-i) > raceDistance_)
          beatenRecord = beatenRecord + 1;
    }

    
    std::cout << "How many ways can you beat the record in this one much longer race? "; 
    std::cout << beatenRecord << '\n';
    inFile.close();
}
