#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>
#include <deque>
#include <algorithm>

//#define N 5 
//#define M 8
#define N 41
#define M 144
struct point2D{
    int x;
    int y;
} startPoint, exitPoint;

void printMatrix(char matrix[N][M]);

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

int isValid(int x, int y, char landscapePathMatrix[N][M])
{
    if ( x >= 0 and x < N and y >= 0 and y < M)
        if (landscapePathMatrix[x][y] == '.')
            return 1;
     return 0;
}

int findShortesPath(int step, int x, int y, point2D exitPoint, \
                    char lsMatrix[N][M], \
                    char lsPathMatrix[N][M], \
                    int x_move[], int y_move[], \
                    char dir[], std::vector<int> &solutions)
{
    int next_x, next_y;
    int steps;
//    std::cout << "----------- find enter " << step << "-------\n";
//    printMatrix(lsPathMatrix);
//    std::cout << "  lsMatrix["<< x << "]["<< y << "]: " << lsMatrix[x][y] << std::endl;
    for (int k = 0; k < 4; k++)
    {
//        std::cout << "x_move[" << k << "]: " << x_move[k] << std::endl;
//        std::cout << "y_move[" << k << "]: " << y_move[k] << std::endl;
//        std::cout << "direction[" << k << "]: " << dir[k] << std::endl;
        next_x = x + x_move[k];
        next_y = y + y_move[k]; 
//        std::cout << "P lsMatrix["<< next_x << "]["<< next_y << "]: " << lsMatrix[next_x][next_y] << std::endl;
        if ( isValid(next_x, next_y, lsPathMatrix) )
        {
//            std::cout << "N lsMatrix["<< next_x << "]["<< next_y << "]: " << lsMatrix[next_x][next_y] << std::endl;
//            std::cout << "direction[" << k << "]: " << dir[k] << std::endl;
            char upHill = lsMatrix[next_x][next_y];
            char downHill = lsMatrix[x][y];
            if ((((upHill - downHill) >=0 ) or ((upHill - downHill) <= 1)) or (lsMatrix[x][y] == 'S') or (lsMatrix[next_x][next_y] == 'E'))
            {
//                std::cout << "direction: " << dir[k] << std::endl;
                if (lsMatrix[next_x][next_y] != 'E')
                {
                    lsPathMatrix[x][y] = dir[k];
                    steps = findShortesPath(step+1, next_x, next_y, exitPoint, lsMatrix, lsPathMatrix, x_move, y_move, dir, solutions);
//                    if (steps != step)
                        lsPathMatrix[x][y] = '.'; 
                }
                else
                {
                    if (lsMatrix[x][y] == 'z')
                    {
                        std::cout << "End! steps: " << step+1 << std::endl;
                        solutions.push_back(step+1);
                        std::cout << solutions.back() << std::endl;
                        return step+1;
                    }
                }
                
            }
        }
    }
//    std::cout << "---------------------------------\n";
//    printMatrix(lsPathMatrix);
//    std::cout << "----------- find exit ------------\n";
    return step; 
}

void printMatrix(char matrix[N][M])
{
    for (int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
            std::cout << matrix[i][j];
        std::cout << std::endl;
    }
}

int main(void)
{
    std::stringstream landscape;
    std::string hills;
    int i, j, steps = 0;
    char landscapeMatrix[N][M];
    char landscapePathMatrix[N][M];
    std::vector<int> solutions;
//                  N   E   S   W
    int x_move[] = { -1,  0,  1,  0};
    int y_move[] = {  0,  1,  0, -1};
    char direction[] = {'^','>','v','<'};

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            landscapePathMatrix[i][j] = '.';
    i = 0;
    landscape = readFile((char*)"input");
    while (getline (landscape, hills, '\n')) {
        for (j = 0; j < hills.length(); j++)
        {
            if ((hills[j]) == 'S')
            {
                startPoint.x = i;
                startPoint.y = j;
            }
            else if ((hills[j] == 'E'))
            {
                exitPoint.x = i;
                exitPoint.y = j;
            }
            landscapeMatrix[i][j] = hills[j];
        }
        i++;
    }
    steps = findShortesPath(0, startPoint.x, startPoint.y, exitPoint, landscapeMatrix, landscapePathMatrix, x_move, y_move, direction, solutions); 
    printMatrix(landscapeMatrix); 
    printMatrix(landscapePathMatrix); 
    std::cout << "What is the fewest steps required to move from your current position to the location that should get the best signal? ";
    std::cout << solutions.size() << std::endl;
    for (int solution: solutions)
        std::cout << solution << " ";
    std::cout << std::endl;
    std::sort(solutions.begin(),solutions.end());
    std::cout << solutions[0] << std::endl; 

    return 1;
}
