#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

std::stringstream readFile(char * filename)
{
    std::ifstream inFile;
    std::string line;

    inFile.open(filename);
    std::getline(inFile, line);
    printf("%s", line.c_str());
    std::stringstream iss(line);

    return iss;
}

int main()
{
    std::vector<int> initialStateList;
    std::stringstream initialState = readFile((char *) "input");

    for (int k; initialState >> k;) {
        initialStateList.push_back(k);
        if (initialState.peek() == ',')
            initialState.ignore();
    }
    for (std::size_t p = 0; p < initialStateList.size(); p++)
        std::cout << initialStateList[p] << std::endl;   

    for (int day = 0; day < 256; day++)
    {
        //#listLength += spawnCount;
        printf("day: %d | list size: %ld\n",day,initialStateList.size());
        for (unsigned long long i = 0; i < initialStateList.size(); i++)
	{
	    if (initialStateList[i] == 0)
            {
                initialStateList[i] = 6;
		initialStateList.push_back(8);
		continue;
            }
    	    initialStateList[i]--;
	}
    }
    printf("%ld",initialStateList.size());
    return 1; 
}
