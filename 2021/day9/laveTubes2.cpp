#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm> 
#include <stdlib.h>

//#define N 8
#define N 100
#define M 100
//#define N 5
//#define M 10

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

int isValid(int i, int j, int smokeFlowMatrixMins[N][M])
{
    if (i >= 0 and i < N and j >= 0 and j < M)
        if (smokeFlowMatrixMins[i][j] == -1)
            return 1;
    return 0; 
}

int isValidBasin(int i, int j, int smokeFlowMatrixBasins[N][M])
{
    if (i >= 0 and i < N and j >= 0 and j < M)
        if (smokeFlowMatrixBasins[i][j] == -2)
            return 1;
    return 0; 
}

void printMatrix(int smokeFlowsMatrix[N][M], int smokeFlowMatrixMins[N][M])
{
     for (int i = 0; i < N; i++)
     {
         for (int j = 0; j < M; j++)
         {
             if (smokeFlowsMatrix[i][j] != smokeFlowMatrixMins[i][j])
                 std::cout << "\033[1;33m" << smokeFlowsMatrix[i][j] << "\033[0m";
             else
                 std::cout << smokeFlowMatrixMins[i][j];
         }
         std::cout << std::endl;
     }
}

void printBasinsMatrix(int smokeFlowMatrixMins[N][M], int smokeFlowMatrixBasins[N][M])
{
     for (int i = 0; i < N; i++)
     {
         for (int j = 0; j < M; j++)
         {
             if (smokeFlowMatrixBasins[i][j] != smokeFlowMatrixMins[i][j])
                 std::cout << "\033[1;33m" << smokeFlowMatrixMins[i][j] << "\033[0m";
             else{
                 if (smokeFlowMatrixMins[i][j] != -1)
                    std::cout << smokeFlowMatrixMins[i][j];
                 else
                    std::cout << "\033[1;33m" << " " << "\033[0m";
             }
         }
         std::cout << std::endl;
     }
}

void findMin(int i, int j, int smokeFlowsMatrix[N][M], int smokeFlowMatrixMins[N][M], int x_move[], int y_move[])
{
    int next_i, next_j;
    for (int k=0; k < 4; k++)
    {
        next_i = i + x_move[k];
        next_j = j + y_move[k];
        if ( isValid(next_i, next_j, smokeFlowMatrixMins) )
		{
            if (smokeFlowsMatrix[i][j] >= smokeFlowsMatrix[next_i][next_j])
			{
				if (smokeFlowsMatrix[i][j] == smokeFlowsMatrix[next_i][next_j])
				{
					smokeFlowMatrixMins[next_i][next_j] = smokeFlowsMatrix[next_i][next_j]; 
				}
                smokeFlowMatrixMins[i][j] = smokeFlowsMatrix[i][j];
                findMin(next_i, next_j, smokeFlowsMatrix, smokeFlowMatrixMins, x_move, y_move);
	   		 }
            if (smokeFlowsMatrix[i][j] < smokeFlowsMatrix[next_i][next_j])  
			{
                smokeFlowMatrixMins[i][j] = -1; 
                smokeFlowMatrixMins[next_i][next_j] = smokeFlowsMatrix[next_i][next_j];
            	findMin(next_i, next_j, smokeFlowsMatrix, smokeFlowMatrixMins, x_move, y_move);
			}
		}
	}
}

std::vector<std::pair<int,int>> findBasins(int i, int j,\
                int smokeFlowMatrixMins[N][M], \
                int smokeFlowMatrixBasins[N][M],\
                std::vector<std::pair<int,int>> basinValues,\
                int x_move[], int y_move[])
{
    int next_i, next_j;
    for (int k=0; k < 4; k++)
    {
        next_i = i + x_move[k];
        next_j = j + y_move[k];
        if ( isValidBasin(next_i, next_j, smokeFlowMatrixBasins) )
        {
            if ( smokeFlowMatrixMins[i][j] != 9 )
            {
                smokeFlowMatrixBasins[i][j] = smokeFlowMatrixMins[i][j];
                //printf("push_back(%d)",smokeFlowMatrixMins[i][j]);
                if ( auto it = std::ranges::find( basinValues.begin(), basinValues.end(), std::make_pair(i,j)); it == basinValues.end() )
                {
                    printf("adding");
                    basinValues.push_back(std::make_pair(i, j));
                }
                basinValues = findBasins(next_i, next_j, smokeFlowMatrixMins, smokeFlowMatrixBasins, basinValues, x_move, y_move);
            }
        }
	}
    return basinValues;
}
int main(void)
{
    int i, j, sum;
    int x_move[] = {-1,  0,  1,  0};
    int y_move[] = { 0, -1,  0,  1};
    int smokeFlowsMatrix[N][M], smokeFlowMatrixMins[N][M], smokeFlowMatrixBasins[N][M];
    std::vector<std::pair<int,int>> basinValues;
    long unsigned int k;
    std::string line;

    std::stringstream smokeFlows;
    smokeFlows = readFile((char*)"input");

// load smokeFlowsMatrix with values from file
    i = 0;
    while (getline (smokeFlows, line, '\n')) {
        for (k = 0; k < line.length(); k++)
		    smokeFlowsMatrix[i][k] = line[k] - '0';
        i++;
    }
// init min Matrix
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
            smokeFlowMatrixMins[i][j] = -1;

    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
		    smokeFlowMatrixBasins[i][j] = -2;

// find solution
    int sum_old = -1;
    sum = 0;    
    while (sum_old != sum)
    {
		sum_old = sum;
        for (i = 0; i < N; i++)
   		    for (j = 0; j < M; j++)
		        findMin(i, j, smokeFlowsMatrix, smokeFlowMatrixMins, x_move, y_move);

// calculate sum from soltion    
	    sum = 0;
	    for (i = 0; i < N; i++)
	    {
			for (j = 0; j < M; j++)
		    	if (smokeFlowsMatrix[i][j] != smokeFlowMatrixMins[i][j]){
					std::cout << "\033[1;33m" << smokeFlowsMatrix[i][j] << "\033[0m";
					sum += smokeFlowsMatrix[i][j] + 1;
			    }
			    else
					std::cout << smokeFlowMatrixMins[i][j];
			std::cout << std::endl;
	    }
	    printf("sum of risk levels: %d\n",sum);
    }
    std::vector<int> basinSizes;
    for (i = 0; i < N; i++)
        for (j = 0; j < M; j++)
        {
            printf("[%d][%d]: %d %d\n",i,j, smokeFlowMatrixMins[i][j], smokeFlowMatrixBasins[i][j]);
            basinValues.clear();
            basinValues = findBasins(i, j, smokeFlowMatrixMins, smokeFlowMatrixBasins, basinValues, x_move, y_move);
            printf("basin found(%ld) ",basinValues.size());
            basinSizes.push_back(basinValues.size());
            for (auto& p: basinValues)
                std::cout << "[ " << p.first << " ][ " << p.second << " ]-";
            printf("\n");
    //        printBasinsMatrix(smokeFlowMatrixMins, smokeFlowMatrixBasins);
        }
    for (const auto& p: basinValues)
        std::cout << "[ " << p.first << " ][ " << p.second << " ]-" ;
    printf("\n");
    std::sort(basinSizes.begin(), basinSizes.end(), std::greater<int>());
    for (int i: basinSizes)
    {
        std::cout << i << " ";
    }
    printf("\n");
    printf("Top 3: %d * %d * %d = %d",basinSizes[0], basinSizes[1], basinSizes[2], basinSizes[0] * basinSizes[1] * basinSizes[2]);
            
    return 1;
}
     
