#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>

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

template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                   flip_pair<A,B>);
    return dst;
}

int main(void)
{
    std::stringstream calories;
    calories = readFile((char*)"input");
    std::string calorie;
    std::map<unsigned long int, unsigned long int> calorieCounts; 
    unsigned long int calorieSum = 0;
    unsigned long int elfCount = 0;

    while (getline (calories, calorie, '\n')) {
        if (calorie == "")
        {
            calorieCounts[elfCount] = calorieSum;
            calorieSum = 0;
            elfCount++;
        }
        else
            calorieSum += stoi(calorie);

    }
    
    std::multimap<unsigned long int, unsigned long int> sortedCalorieCounts = flip_map(calorieCounts);

    for(const auto& elem : sortedCalorieCounts)
    {
        std::cout << elem.first << " " << elem.second << "\n";
    }
    
    std::cout << "How many Calories are those Elves carrying in total? ";
    std::cout << ((--sortedCalorieCounts.end())->first) + ((--(--sortedCalorieCounts.end()))->first) + ((--(--(--sortedCalorieCounts.end())))->first)<<"\n";

    return 1;
}
