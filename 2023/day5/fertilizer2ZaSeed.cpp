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
    std::string line, seedIDs, seedIDStr;
    long long int src, dst, range;
    std::vector<long long int> seeds;
    std::vector<std::vector<long long int>> seed_soil_map;
    std::vector<std::vector<long long int>> soil_fertilizer_map;
    std::vector<std::vector<long long int>> fertilizer_water_map;
    std::vector<std::vector<long long int>> water_light_map;
    std::vector<std::vector<long long int>> light_temperature_map;
    std::vector<std::vector<long long int>> temperature_humidity_map;
    std::vector<std::vector<long long int>> humidity_location_map;

//    inFile.open("input");
    inFile.open("demo");
    getline(inFile, line, '\n');
    std::stringstream seedsInfo(line);
    getline(seedsInfo, seedIDs, ':');
    getline(seedsInfo, seedIDs, ':');
    std::stringstream seedIDsstream(seedIDs);
    while (getline(seedIDsstream, seedIDStr, ' '))
    {
      if (seedIDStr != ""){
        seeds.push_back(std::stoll(seedIDStr));
      }
    }
    for(line; getline( inFile, line, '\n' ); ){
      if (line == "")
        continue;
      
      if (line.find("seed-to-soil") != std::string::npos) {
        while (getline(inFile, line)){
          if (line == "")
            break;
          std::istringstream(line) >> dst >> src >> range;
          seed_soil_map.push_back({dst, src, range});
        }
      }
      if (line.find("soil-to-fertilizer") != std::string::npos) {
        while (getline(inFile, line)){
          if (line == "")
            break;
          std::istringstream(line) >> dst >> src >> range;
          soil_fertilizer_map.push_back({dst, src, range});
        }
      }
      if (line.find("fertilizer-to-water") != std::string::npos) {
        while (getline(inFile, line)){
          if (line == "")
            break;
          std::istringstream(line) >> dst >> src >> range;
          fertilizer_water_map.push_back({dst, src, range});
        }
      }
      if (line.find("water-to-light") != std::string::npos) {
        while (getline(inFile, line)){
          if (line == "")
            break;
          std::istringstream(line) >> dst >> src >> range;
          water_light_map.push_back({dst, src, range});
        }
      }
      if (line.find("light-to-temperature") != std::string::npos) {
        while (getline(inFile, line)){
          if (line == "")
            break;
          std::istringstream(line) >> dst >> src >> range;
          light_temperature_map.push_back({dst, src, range});
        }
      }
      if (line.find("temperature-to-humidity") != std::string::npos) {
        while (getline(inFile, line)){
          if (line == "")
            break;
          std::istringstream(line) >> dst >> src >> range;
          temperature_humidity_map.push_back({dst, src, range});
        }
      }
      if (line.find("humidity-to-location") != std::string::npos) {
        while (getline(inFile, line)){
          if (line == "")
            break;
          std::istringstream(line) >> dst >> src >> range;
          humidity_location_map.push_back({dst, src, range});
        }
      }
    }
    long long int offset;

    long long int soil;
    long long int fertilizer;
    long long int water;
    long long int light;
    long long int temperature;
    long long int humidity;
    long long int location;
    bool found = false;

    std::vector<long long int> locations;
    for (long long int seed: seeds){
//      std::cout << seed << '\n';
      found = false;
      for (std::vector<long long int> seed_soil: seed_soil_map){
        if (seed >= seed_soil.at(1) && seed <= (seed_soil.at(1) + seed_soil.at(2) - 1)){
          offset = abs(seed - seed_soil.at(1));
          soil = seed_soil.at(0)+offset;
          found = true;
        }
        if (found)
          break;
      }
      if (!found)
        soil = seed;
//      std::cout << "seed " << seed << " maps to soil " << soil << '\n';
    
      found = false;
      for (std::vector<long long int> soil_fertilizer: soil_fertilizer_map){
        if (soil >= soil_fertilizer.at(1) && soil <= (soil_fertilizer.at(1) + soil_fertilizer.at(2) - 1)){
          offset = abs(soil- soil_fertilizer.at(1));
          fertilizer = soil_fertilizer.at(0)+offset;
          found = true;
        }
        if (found)
          break;
      }
      if (!found)
        fertilizer = soil;
//      std::cout << "soil " << soil << " maps to fertilizer " << fertilizer << '\n';
      
      found = false;
      for (std::vector<long long int> fertilizer_water: fertilizer_water_map){
        if (fertilizer >= fertilizer_water.at(1) && fertilizer <= (fertilizer_water.at(1) + fertilizer_water.at(2) - 1)){
          offset = abs(fertilizer- fertilizer_water.at(1));
          water = fertilizer_water.at(0)+offset;
          found = true;
        }
        if (found)
          break;
      }
      if (!found)
        water = fertilizer;
//      std::cout << "fertilizer " << fertilizer << " maps to water " << water << '\n';

      found = false;
      for (std::vector<long long int> water_light: water_light_map){
        if (water >= water_light.at(1) && water <= (water_light.at(1) + water_light.at(2) - 1)){
          offset = abs(water - water_light.at(1));
          light = water_light.at(0)+offset;
          found = true;
        }
        if (found)
          break;
      }
      if (!found)
        light = water;
//      std::cout << "water " << water << " maps to light " << light << '\n';

      found = false;
      for (std::vector<long long int> light_temperature: light_temperature_map){
        if (light >= light_temperature.at(1) && light <= (light_temperature.at(1) + light_temperature.at(2) - 1)){
          offset = abs(light - light_temperature.at(1));
          temperature = light_temperature.at(0)+offset;
          found = true;
        }
        if (found)
          break;
      }
      if (!found)
        temperature = light;
//      std::cout << "light " << light << " maps to temperature " << temperature << '\n';

      found = false;
      for (std::vector<long long int> temperature_humidity: temperature_humidity_map){
        if (temperature >= temperature_humidity.at(1) && temperature <= (temperature_humidity.at(1) + temperature_humidity.at(2) - 1)){
          offset = abs(temperature - temperature_humidity.at(1));
          humidity = temperature_humidity.at(0)+offset;
          found = true;
        }
        if (found)
          break;
      }
      if (!found)
        humidity = temperature;
//      std::cout << "temperature " << temperature << " maps to humidity " << humidity << '\n';

      found = false;
      for (std::vector<long long int> humidity_location: humidity_location_map){
        if (humidity >= humidity_location.at(1) && humidity <= (humidity_location.at(1) + humidity_location.at(2) - 1)){
          offset = abs(humidity - humidity_location.at(1));
          location = humidity_location.at(0)+offset;
          found = true;
        }
        if (found)
          break;
      }
      if (!found)
        location = humidity;
//      std::cout << "humidity " << humidity << " maps to location " << location << '\n';

      std::cout << seed << '-' << soil << '-' << fertilizer << '-' << water << '-' << light << '-' << temperature << '-' << humidity << '-' << location <<'\n';
      locations.push_back(location);

    }
    std::cout << '\n';
    sort(locations.begin(),locations.end());
    long long int min_loc_number = locations.at(0);
    std::cout << "What is the lowest location number that corresponds to any of the initial seed numbers?: "; 
    std::cout << min_loc_number << '\n';
    inFile.close();
}
