#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>

#define N 99
#define M 99
//#define N 5
//#define M 5

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

void printMatrix(int treesMatrix[N][M], int treesVisibilityMatrix[N][M])
{
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            if (treesVisibilityMatrix[i][j] == 1)
                std::cout << "\033[1;33m" <<treesMatrix[i][j] << "\033[0m";
            else
                std::cout << treesMatrix[i][j];

        }
        std::cout << std::endl;
    }
}

int calculateScenic(int i, int j, int treesMatrix[N][M])
{
    int k, l; 
    int nord=0, sud=0, est=0, vest = 0;
    if ((i+1) < N)
        for (k = i+1; k < N; k++)
            if (treesMatrix[i][j] > treesMatrix[k][j])
                est++;
            else
            {
                est++;
                break;
            }
    if ((i-1) > -1)
        for (k = i-1; k >= 0; k--)
            if (treesMatrix[i][j] > treesMatrix[k][j])
                vest++;
            else
            {
                vest++;
                break;
            }
    if ((j+1) < M)
        for (l = j+1; l < M; l++)
            if (treesMatrix[i][j] > treesMatrix[i][l])
                sud++;
            else
            {
                sud++;
                break;
            }
    if ((j-1) > -1)
        for (l = j-1; l >= 0; l--)
            if (treesMatrix[i][j] > treesMatrix[i][l])
                nord++;
            else
            {
                nord++;
                break;
            }
    std::cout << nord << " " << sud << " " << est << " " << vest << " " <<nord*sud*est*vest << std::endl;
    return nord*sud*est*vest;
}

int findHighestScenic(int treesMatrix[N][M])
{
    int i, j;
    int highestScenic = 0;
    int currentScenicScore;
    for ( i = 1; i < N-1; i++ )
    {
        for ( j = 1; j < M-1; j++)
        {
            currentScenicScore = calculateScenic(i,j, treesMatrix);
            if  (currentScenicScore > highestScenic)
                highestScenic = currentScenicScore;
        }
    }
    return highestScenic;
}

int main(void)
{
    std::stringstream trees;
    std::string line;
    int i, j;
    int highestScenicScore = 0;
    int treeMatrix[N][M];

    i = 0;
    trees = readFile((char*)"input");
    while (getline (trees, line, '\n')) {
        for (j = 0; j < line.length(); j++)
            treeMatrix[i][j] = line[j] - '0';
        i++;
    }

    highestScenicScore = findHighestScenic(treeMatrix);

    std::cout << "What is the highest scenic score possible for any tree? ";
    std::cout << highestScenicScore << std::endl; 

    return 1;
}
