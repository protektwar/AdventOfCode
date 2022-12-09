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

int findVisibleTrees(int treesMatrix[N][M], int treeVisibleMatrix[N][M])
{
    int i, j;
    int totalVisibleTrees = 0;
    int visibleTreesLeft, visibleTreesRight, visibleTreesUp, visibleTreesDown;
    int maxLineLeft, maxLineRight, maxLineUp, maxLineDown;
    for ( i = 0; i < N; i++)
    {
        treeVisibleMatrix[i][0] =1;
        treeVisibleMatrix[i][M-1] =1;
    }
    for ( j = 0; j < M; j++)
    {
        treeVisibleMatrix[0][j] =1;
        treeVisibleMatrix[N-1][j] =1;
    }
    for ( i = 1; i < N-1; i++ )
    {
        maxLineLeft = treesMatrix[i][0];
        maxLineRight = treesMatrix[i][M-1];
        for ( j = 1; j < M-1; j++)
        {
            if (treesMatrix[i][j] > maxLineLeft)
            {
                treeVisibleMatrix[i][j] = 1;
                maxLineLeft = treesMatrix[i][j];
            }

            if (treesMatrix[i][M-j-1] > maxLineRight)
            {
                treeVisibleMatrix[i][M-j-1] = 1;
                maxLineRight = treesMatrix[i][M-j-1];
            }
        }
        printMatrix(treesMatrix, treeVisibleMatrix);
    }
    for ( i = 1; i < M-1; i++ )
    {
        maxLineUp = treesMatrix[0][i];
        maxLineDown = treesMatrix[N-1][i];
        for ( j = 1; j < N-1; j++)
        {
            if (treesMatrix[j][i] > maxLineUp)
            {
                treeVisibleMatrix[j][i] = 1;
                maxLineUp = treesMatrix[j][i];
            }
        
            if (treesMatrix[N-j-1][i] > maxLineDown)
            {
                treeVisibleMatrix[N-j-1][i] = 1;
                maxLineDown = treesMatrix[N-j-1][i];
            }
            
        }
    }
    return totalVisibleTrees;
}

int main(void)
{
    std::stringstream trees;
    std::string line;
    int i, j;
    int totalVisibleTrees = 0;
    int treeMatrix[N][M];
    int treeVisibleMatrix[N][M];

    i = 0;
    trees = readFile((char*)"input");
    while (getline (trees, line, '\n')) {
        for (j = 0; j < line.length(); j++)
            treeMatrix[i][j] = line[j] - '0';
        i++;
    }
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            treeVisibleMatrix[i][j] = 0;

//    printMatrix(treeMatrix);
    totalVisibleTrees = findVisibleTrees(treeMatrix, treeVisibleMatrix);
//    totalVisibleTrees += N*2 + (M-2)*2;
    printMatrix(treeMatrix, treeVisibleMatrix);
    std::cout << totalVisibleTrees << std::endl;

    totalVisibleTrees = 0;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            if (treeVisibleMatrix[i][j] == 1)
                totalVisibleTrees++;
    
    std::cout << "How many trees are visible from outside the grid?";
    std::cout << totalVisibleTrees << std::endl; 

    return 1;
}
