#include <iostream>
#include <variant>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>
#include <algorithm>

struct Value;
struct Value{
    std::variant<int, std::vector<Value>> value;
};

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

std::string fromValue(Value value)
{
    if (std::holds_alternative<int>(value.value)){
        return std::to_string(std::get<int>(value.value));
    }
    auto vector = std::get<std::vector<Value>>(value.value);
    if (vector.empty()){
        return "[]";
    }
    std::string text = "[" + fromValue(vector.at(0));
    for (int i = 1; i < vector.size(); i++) {
        text += "," + fromValue(vector.at(i));
    }
    return text + "]";
}

Value decomposeSignal(std::string signal, int &index)
{
    Value decomposedSignal;
    int endDecompose = 0, newNumber = 0;
    std::string number = "";
    for (int i = index; i < signal.length(); i++)
    {
        char c = signal.at(i);
        if (c == '[')
        {
            i++;
            decomposedSignal.value.push_back(decomposeSignal(signal, i));
            
        }
        else if (c == ']')
        {
            decomposedSignal.push_back({std::stoi(number)});
            index = i+1;
            return decomposedSignal;
        }
        else if (c == ',')
        {
            decomposedSignal.push_back({std::stoi(number)});
            number = "";
        }
        else 
            number = number + signal[i];
    }
    index = signal.length();
    return decomposedSignal;
}

int compareDistress(std::string signal1, std::string signal2)
{
    int indexRight = 0;
    int startIndex = 0;
    std::cout << "decomposeSignal 1" << std::endl;
    decomposeSignal(signal1, startIndex);
    startIndex = 0;
    std::cout << "decomposeSignal 2" << std::endl;
    decomposeSignal(signal2, startIndex);

    return indexRight;
}

int main(void)
{
    std::stringstream signals;
    std::string signal, signal1, signal2;
    int pairIndex, i;
    int sumIndexes = 0;

    signals = readFile((char*)"input.test");
//    signals = readFile((char*)"input");
    i = 0;
    pairIndex = 1;
    while (getline (signals, signal, '\n')) {
        if (i == 0)
            signal1 = signal;
        if (i == 1)
            signal2 = signal;
        if (signal == "")
        {
            std::cout << "\n";
            std::cout << "pairIndex: " << pairIndex << std::endl;
            std::cout << "Signal 1: " << signal1 << std::endl;
            std::cout << "Signal 2: " << signal2 << std::endl;
            if (compareDistress(signal1, signal2) > 0)
            {
                std::cout << "=======================> Adding index: " << pairIndex << "\n";
                sumIndexes += pairIndex;
            }
            i = -1;
            pairIndex++;
        }
        i++;
    }
    std::cout << "What is the sum of the indices of those pairs? ";
    std::cout << sumIndexes << std::endl; 

    return 1;
}
