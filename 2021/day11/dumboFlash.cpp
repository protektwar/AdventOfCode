#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>

 #define N 10
 #define M 10
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

int isValidPosition(int i,int j)
{
    if ( (i>=0 and i<N) and (j>=0 and j<M) )
    {
        return 1;
    }
    return 0;
}

void printFlashesMatrix(int flashesMatrix[N][M])
{
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<M; j++)
            printf("%2d",flashesMatrix[i][j]);
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int countFlashes(int i, int j, int step, int flashesMatrix[N][M], int flashedMatrix[N][M], int x_move[], int y_move[])
{
    int flashCount = 0;
    int next_i, next_j;
    if ( flashedMatrix[i][j] != 0 )
    {
        flashesMatrix[i][j] += 1;
    }

    if ( flashesMatrix[i][j] > 9 )
    {
        flashesMatrix[i][j] = 0;
        flashedMatrix[i][j] = 0;
        flashCount += 1;
//        std::cout << "Step: "<< step <<" Flashing\n";
        for (int k=0; k<8; k++)
        {
            next_i = i + x_move[k];
            next_j = j + y_move[k];
            if (isValidPosition(next_i,next_j))
            {
                if ( flashedMatrix[next_i][next_j] != 0 )
//                    if (flashedMatrix != 0)
                {
//                        std::cout << "k: " << k << std::endl;
                        flashesMatrix[next_i][next_j] += 1;
                }

                if ( flashesMatrix[next_i][next_j] > 9 )
                {
                    //flashesMatrix[next_i][next_j] = 0;
                    flashedMatrix[next_i][next_j] = 0;
//                    std::cout << "k: " << k << std::endl;
//                    std::cout << "Step: "<< step <<" Flashing | Before call countFlashes\n";
//                    printFlashesMatrix(flashesMatrix);
                    flashCount += countFlashes(next_i, next_j, step+1, flashesMatrix, flashedMatrix, x_move, y_move);
                }
            }
        }
    }
//    std::cout << "Before exiting countFlashes\n";
//    printFlashesMatrix(flashesMatrix);
//    printFlashesMatrix(flashedMatrix);
//    std::cout << "fc: " << flashCount << " " << std::endl;
//    std::cin.get();
    return flashCount;
}

int main(void)
{
    int flashesMatrix[N][M];
    int flashedMatrix[N][M];
    int i, j, step, sum, k;
    std::string line;

//                   N  NW   W  SW  S  SE  E  NE
    int x_move[] = {-1, -1,  0,  1, 1,  1, 0, -1};
    int y_move[] = { 0, -1, -1, -1, 0,  1, 1,  1};

    std::stringstream smokeFlows;
    smokeFlows = readFile((char*)"input");

// load syntax with values from file
    i = 0;
    while (getline (smokeFlows, line, '\n')) {
        for (k = 0; k < line.length(); k++)
        {
            flashesMatrix[i][k] = line[k] - '0';
        }
        i++;
    }
    printFlashesMatrix(flashesMatrix);
    
    int flashCount = 0, sumBetween;
    sum = 0;
    for (step=0;step<1000;step++)
//    for (step=0;step<3;step++)
    {
        for (i=0;i<N;i++)
            for (j=0;j<M;j++)
                flashedMatrix[i][j] = -1;
        std::cout << "-------------Step: " << step+1 << std::endl;
        //printFlashesMatrix(flashedMatrix);
        sumBetween = 0;
        for (i=0; i<N; i++)
        {
            for (j=0; j<M; j++)
            {
//                std::cout << "new [" << i << "]["<< j<< "] ";
                flashCount = countFlashes(i, j, 0, flashesMatrix, flashedMatrix, x_move, y_move);
                sumBetween += flashCount;
            }
        }
        sum += sumBetween;
//        printFlashesMatrix(flashesMatrix);
//        printFlashesMatrix(flashedMatrix);
        int allTogether = 1;
        for (i=0; i<N; i++)
        {
            for (j=0; j<M; j++)
                if ( flashedMatrix[i][j] != 0 )
                {
                    allTogether = 0;
                    break;
                }
            if ( allTogether == 0 )
                break;
        }
        if (allTogether == 1 )
            break;        
        std::cout << sum << "(+" << sumBetween << ")" << std::endl;
        std::cout << "Matrix after end Step --------------" << std::endl;
//        std::cin.get();
    }
    std::cout << "How many total flashes are there after 100 steps? " << sum << std::endl;
    return 1;
}
     
