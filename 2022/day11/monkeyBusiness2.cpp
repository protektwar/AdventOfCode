#include <iostream>
#include <numeric>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>


struct monkeyDef{
    std::vector<long> items;
    char operation;
    int quantity;
    int old;
    int division;
    int monkeyTrue;
    int monkeyFalse;
} monkeys[7];

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

int main(void)
{
    std::stringstream monkeyInputs;
    std::string line, word, chunkWords;
    int lineCnt = 0;
    int wordCnt;
    int monkeyNumber = 0;
    std::vector<int> divisors;

    monkeyInputs = readFile((char*)"input");
    while (getline (monkeyInputs, line, '\n')) {
        if (line == "") 
        {
            lineCnt = 0;
            continue;
        }
        std::istringstream strToSplit(line);
        if (lineCnt == 0)
        {
            strToSplit >> word >> word;
            monkeyNumber = word[0] - '0';
        }
        if (lineCnt == 1)
        {
            wordCnt = 0;
            while(getline (strToSplit, chunkWords, ':')) {
                if (wordCnt == 1)
                {
                    std::istringstream items(chunkWords);
                    while (getline (items, word, ',')) {
                        monkeys[monkeyNumber].items.push_back(std::stoi(word));
                    }
                }
                wordCnt ++;
            }

        }
        if (lineCnt == 2)
        {
            wordCnt = 0;
            while(getline (strToSplit, chunkWords, '=')) {
                if (wordCnt == 1)
                {
                    std::string oper, quantity;
                    std::istringstream operation(chunkWords);
                    operation >> word >> oper >> quantity;
                    monkeys[monkeyNumber].operation = oper[0];
                    if (quantity == "old")
                        monkeys[monkeyNumber].old = 1;
                    else
                    {
                        monkeys[monkeyNumber].old = 0;
                        monkeys[monkeyNumber].quantity = std::stoi(quantity);
                    }

                }
                wordCnt ++;
            }

        }
        if (lineCnt == 3)
        {
            wordCnt = 0;
            while(getline (strToSplit, chunkWords, ' ')) {
                if (wordCnt == 5)
                {
                    monkeys[monkeyNumber].division = std::stoi(chunkWords);
                    divisors.push_back(monkeys[monkeyNumber].division);
                }
                wordCnt ++;
            }

        }
        if (lineCnt == 4)
        {
            wordCnt = 0;
            while(getline (strToSplit, chunkWords, ' ')) {
                if (wordCnt == 9)
                {
                    monkeys[monkeyNumber].monkeyTrue = std::stoi(chunkWords);
                }
                wordCnt ++;
            }

        }
        if (lineCnt == 5)
        {
            wordCnt = 0;
            while(getline (strToSplit, chunkWords, ' ')) {
                if (wordCnt == 9)
                {
                    monkeys[monkeyNumber].monkeyFalse = std::stoi(chunkWords);
                }
                wordCnt ++;
            }

        }
        lineCnt++;
    }

    int monkeyBusinessLevel[8];
    int monkeyRoundSkip[8];
    int currentMonkey;
    long newWorryLevel; 

//    for (currentMonkey = 0; currentMonkey < monkeyNumber + 1; currentMonkey++)
//    {
//        std::cout << "Monkey " << currentMonkey << std::endl;
//        for (int itms : monkeys[currentMonkey].items)
//            std::cout << itms << " ";
//        std::cout << std::endl;
//    }

    for (currentMonkey = 0; currentMonkey < monkeyNumber + 1; currentMonkey++)
        monkeyBusinessLevel[currentMonkey] = 0;

    for (currentMonkey = 0; currentMonkey < monkeyNumber + 1; currentMonkey++)
        monkeyRoundSkip[currentMonkey] = 0;

    for (int round = 0; round < 10000; round++)
    {
/*        if (round == 20 || round % 1000 == 0 )
            std::cin.get();*/
//        std::cout << "\n-----> !!! Round " <<  round+1 << std::endl;
        for (currentMonkey = 0; currentMonkey < monkeyNumber + 1; currentMonkey++)
        {
            if (monkeys[currentMonkey].items.empty())
            {
                monkeyRoundSkip[currentMonkey] = 1;
//                std::cout << "Monkey " << currentMonkey << " empty item list\n";
            }
            else
                monkeyRoundSkip[currentMonkey] = 0;
        }
        for (currentMonkey = 0; currentMonkey < monkeyNumber + 1; currentMonkey++)
        {
//            std::cout << "===> Monkey " << currentMonkey << " with items:" << std::endl;
//            for (long itms : monkeys[currentMonkey].items)
//                std::cout << itms << " ";
//            std::cout << std::endl;
/*            if (monkeyRoundSkip[currentMonkey] == 1)
            {
                std::cout << "-------->skipping round\n";
                continue;
            }
            else
            {*/
                for (long itm : monkeys[currentMonkey].items)
                {
//                    std::cout << "Item with worry level: " << itm << std::endl;
                    switch (monkeys[currentMonkey].operation){
                        case '*':
//                            std::cout << itm << " * " << monkeys[currentMonkey].quantity;
                            if (monkeys[currentMonkey].old == 1)
                            {
//                                std::cout << " with self " << std::endl;
                                newWorryLevel = itm * itm; 
                            }
                            else
                                newWorryLevel = itm * monkeys[currentMonkey].quantity;
//                            std::cout << " = " << newWorryLevel << "\n";
                            break;
                        case '+':
//                            std::cout << itm << " + " << monkeys[currentMonkey].quantity;
                            if (monkeys[currentMonkey].old == 1)
                            {
//                                std::cout << " with self " << std::endl;
                                newWorryLevel = itm + itm; 
                            }
                            else
                                newWorryLevel = itm + monkeys[currentMonkey].quantity;
//                            std::cout << " = " << newWorryLevel << "\n";
                            break;
                        case '-':
//                            std::cout << itm << " - " << monkeys[currentMonkey].quantity;
                            if (monkeys[currentMonkey].old == 1)
                            {
//                                std::cout << " with self " << std::endl;
                                newWorryLevel = itm - itm; 
                            }
                            else
                                newWorryLevel = itm - monkeys[currentMonkey].quantity;
//                            std::cout << " = " << newWorryLevel << "\n";
                            break;
                        case '/':
//                            std::cout << itm << " / " << monkeys[currentMonkey].quantity;
                            if (monkeys[currentMonkey].old == 1)
                            {
//                                std::cout << " with self " << std::endl;
                                newWorryLevel = itm / itm; 
                            }
                            else
                                newWorryLevel = itm / monkeys[currentMonkey].quantity;
//                            std::cout << " = " << newWorryLevel << "\n";
                            break;
                    }
                    monkeyBusinessLevel[currentMonkey]++;
//                    newWorryLevel %= 96577;
                    newWorryLevel %= 9699690;
                    if (newWorryLevel % monkeys[currentMonkey].division == 0)
                    {
//                        std::cout << "divisible by " << monkeys[currentMonkey].division << std::endl;
                        monkeys[monkeys[currentMonkey].monkeyTrue].items.push_back(newWorryLevel);
//                        std::cout << "throwing to --------------------> " << monkeys[currentMonkey].monkeyTrue << std::endl;
                    }
                    else
                    {
//                        std::cout << "not divisible by " << monkeys[currentMonkey].division << std::endl;
                        monkeys[monkeys[currentMonkey].monkeyFalse].items.push_back(newWorryLevel);
//                        std::cout << "throwing to --------------------> " << monkeys[currentMonkey].monkeyFalse << std::endl;
                    }
                }
                monkeys[currentMonkey].items.clear();
//            }
//            std::cout << std::endl;
//            for (int currentMonkey_ = 0; currentMonkey_ < monkeyNumber + 1; currentMonkey_++)
//                std::cout << monkeyBusinessLevel[currentMonkey_] << " ";
//            std::cout << std::endl;
        }

    }
   
    std::cout << "What is the level of monkey business after 10000 rounds? ";

    std::sort(std::begin(monkeyBusinessLevel), std::end(monkeyBusinessLevel));
    std::cout << (long long)monkeyBusinessLevel[6] * monkeyBusinessLevel[7] << std::endl; 
    for (currentMonkey = 0; currentMonkey < monkeyNumber + 1; currentMonkey++)
        std::cout << monkeyBusinessLevel[currentMonkey] << " ";
    std::cout << std::endl;
    return 1;
}
