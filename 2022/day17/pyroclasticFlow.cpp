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
#include <set>
#include <math.h>
#include <unistd.h>

#define N 70
#define M 9

char rock0[1][4] = {{'@','@','@','@'}};
char rock1[3][3] = {{'.','@','.'},
                    {'@','@','@'},
                    {'.','@','.'}};
char rock2[3][3] = {{'.','.','@'},
                    {'.','.','@'},
                    {'@','@','@'}};
char rock3[4][1] = {{'@'},
                    {'@'},
                    {'@'},
                    {'@'}};
char rock4[2][2] = {{'@','@'},
                    {'@','@'}};

struct position2D{
    int x;
    int y;
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

void printMatrix(char chamberMatrix[N][M])
{
    for(int i = 0; i < N; i++) {
        std::string zero = i < 10? "0" : "";
        std::cout << zero << i << " ";
        for(int j = 0; j < M; j++)
            std::cout << chamberMatrix[i][j];
        std::cout << std::endl;
    }
            
}

void copyChamber(char verticalChamber[N][M], char verticalChamberCopy[N][M])
{
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < M; j++)
            verticalChamberCopy[i][j] = verticalChamber[i][j];
}

void tetrisComesToRest(char verticalChamber[N][M])
{
    for(int i = 0; i < N; i++) 
        for(int j = 0; j < M; j++)
            if (verticalChamber[i][j] == '@' )
                verticalChamber[i][j] = '#';
}

int checkTetrisInChamber(int x, int y, int height, int width, char chamberMatrix[N][M])
{
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) { 
//            std::cout << chamberMatrix[y-i][x+j];
            if (chamberMatrix[y-i][x+j] == '#'){
//                std::cout << std::endl;
                return 0;
            }
        }
//        std::cout << std::endl;
    }
    return 1;
}
template<int NN, int MM>
void putTetrisInChamber(int x, int y, char rock[NN][MM], char chamberMatrix[N][M])
{
    for (int i = 0; i < NN; i++)
        for (int j = 0; j < MM; j++) {
            if (rock[NN-i-1][j] != '.')
                chamberMatrix[y-i][x+j] = rock[NN-i-1][j]; 
        }
}

void initVisitedChamber(int chamberVisitedMatrix[N][M])
{
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            chamberVisitedMatrix[i][j] = 0;
        }
    }
}

bool isValid(int x, int y, char chamberMatrix[N][M], int chamberVisitedMatrix[N][M])
{  
//    std::cout << x << " " << y << std::endl;
    if ( x > 0 and x < N-1 and y > 0 and y < M-1) {
        if (chamberMatrix[x][y] == '#' and chamberVisitedMatrix[x][y] == 0) {
//            std::cout << "Valid chamberMatrix[" << x << "][" << y << "]: " << chamberMatrix[x][y] << std::endl;
            return true;
        }
    }
    return false;
}
std::tuple<int, int, int> findCloseLine(int x, int y, int first, int second, int continue_, char chamberMatrix[N][M], int chamberVisitedMatrix[N][M], int x_move[], int y_move[])
{
    int next_x, next_y;

    std::tuple<int, int, int> result;
    
    for (int k = 0; k < 5; k++){
        next_x = x + x_move[k];
        next_y = y + y_move[k];
        if ( isValid(next_x, next_y, chamberMatrix, chamberVisitedMatrix) ) {
            if ((next_y == 1 or continue_) and next_y != 7){
                if (!continue_)
                    first = next_x;
                int continue__ = 1;
                chamberVisitedMatrix[x][y]++;
                result = findCloseLine(next_x, next_y, first, second, continue__, chamberMatrix, chamberVisitedMatrix, x_move, y_move);
                if (std::get<2>(result) == 1)
                    break;
            }
            if (next_y == 7){
                second = next_x;
                result = std::make_tuple(first, second, 1);
                return result;
            }
        }
    }
    return result;
}

int scrollDownChamber(char chamberMatrix[N][M], int chamberVisitedMatrix[N][M], int x_move[], int y_move[])
{
    std::tuple<int, int, int> scrolling;
    std::vector<int> scrollingLinesLeft, scrollingLinesRight;
    int scrollingLine;
    for (int l = N-2; l > 0; l--) {
        initVisitedChamber(chamberVisitedMatrix);
        scrolling = findCloseLine(l, 0, N-1, N-1, 0, chamberMatrix, chamberVisitedMatrix, x_move, y_move);
        if (std::get<0>(scrolling) != 0 && std::get<1>(scrolling) != 0 ) { 
            if (std::get<0>(scrolling) > std::get<1>(scrolling)) {
                scrollingLinesLeft.push_back(std::get<0>(scrolling));
            }
            else {
                scrollingLinesRight.push_back(std::get<1>(scrolling));
            } 
            break;
        }
    }
    if (scrollingLinesLeft.size() > 0 or scrollingLinesRight.size() > 0) {
        if (scrollingLinesLeft.size() > 0 and scrollingLinesRight.size() > 0) {
            std::sort(scrollingLinesLeft.begin(), scrollingLinesLeft.end());
            std::sort(scrollingLinesRight.begin(), scrollingLinesRight.end());
            if (scrollingLinesLeft.at(0) < scrollingLinesRight.at(0)){
                scrollingLine = scrollingLinesRight.at(0);
            }
            else{
                scrollingLine = scrollingLinesLeft.at(0);
            }
        }
        else if (scrollingLinesLeft.size() > 0) {
            std::sort(scrollingLinesLeft.begin(), scrollingLinesLeft.end());
            scrollingLine = scrollingLinesLeft.at(0);
        }
        else if (scrollingLinesRight.size() > 0) {
            std::sort(scrollingLinesRight.begin(), scrollingLinesRight.end());
            scrollingLine = scrollingLinesRight.at(0);
        } 

        for (int i = scrollingLine-1; i > 0; i--) {
            for (int j = 1; j < M-1; j++) { 
                chamberMatrix[N-2-(scrollingLine-i-1)][j] = chamberMatrix[i][j];
            }
        }
//        getchar();
        return (N-1-scrollingLine);
    }
//    getchar();
    return 0; 
}

void initChamber(char chamberMatrix[N][M], int chamberVisitedMatrix[N][M])
{
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) {
            chamberMatrix[i][j] = '.';
            chamberVisitedMatrix[i][j] = 0;
        }
    }

    for(int i = 0; i < N; i++) {
        chamberMatrix[i][0] = '#';
        chamberMatrix[i][M-1] = '#';
    }

    for(int j = 0; j < M; j++) 
        chamberMatrix[N-1][j] = '#';


}

int main(void)
{
    std::stringstream gasFlow;
    std::string line;
    int towerTallUnits = 0;
    int unitCount = 0;
    char currentFlow;
    int chamberWidth = 7;
    char verticalChamber[N][M];
    int verticalChamberVisited[N][M];
    char verticalChamberCopy[N][M];
    int resting = N-1;
    int restingCorrectionAfterScrollDown = 0;
    position2D start={3, resting-4};
//                    0   1   2   3   4    
//                    E  NE   N  SE   S
    int x_move[] = {  0, -1, -1,  1,  1};
    int y_move[] = {  1,  1,  0,  1,  0};

    initChamber(verticalChamber, verticalChamberVisited);
    copyChamber(verticalChamber, verticalChamberCopy);

    gasFlow = readFile((char*)"input");
    getline (gasFlow, line, '\n');
    while (unitCount != 2022) {
        for (std::string::size_type st = 0; st < line.length(); st++) {
            system("clear");
            currentFlow = line.at(st);
            if ((unitCount % 5) == 0){ 
                putTetrisInChamber<1,4>(start.x,start.y,rock0,verticalChamber);
            }
            if ((unitCount % 5) == 1){ 
                putTetrisInChamber<3,3>(start.x,start.y,rock1,verticalChamber);
            }
            if ((unitCount % 5) == 2){ 
                putTetrisInChamber<3,3>(start.x,start.y,rock2,verticalChamber);
            }
            if ((unitCount % 5) == 3){ 
                putTetrisInChamber<4,1>(start.x,start.y,rock3,verticalChamber);
            }
            if ((unitCount % 5) == 4){ 
                putTetrisInChamber<2,2>(start.x,start.y,rock4,verticalChamber);
            }
            printMatrix(verticalChamber);
            usleep(100000);
            copyChamber(verticalChamberCopy, verticalChamber);
            
            if ((unitCount % 5) == 0) {
                switch (currentFlow) {
                    case '>':
                        start.x++;
                        if (start.x+4 > chamberWidth+1 or !checkTetrisInChamber(start.x,start.y,1,4,verticalChamber))
                            start.x -= 1;
                        break;
                    case '<':
                        start.x--;
                        if (start.x == 0 or !checkTetrisInChamber(start.x,start.y,1,4,verticalChamber))
                            start.x++;
                        break;
                }
                if (checkTetrisInChamber(start.x,start.y,1,4,verticalChamber)) 
                    putTetrisInChamber<1,4>(start.x,start.y,rock0,verticalChamber);
            }
            if ((unitCount % 5) == 1) {
                switch (currentFlow) {
                    case '>':
                        start.x++;
                        if (start.x+3 > chamberWidth+1 or !checkTetrisInChamber(start.x,start.y,3,3,verticalChamber))
                            start.x -= 1;
                        break;
                    case '<':
                        start.x--;
                        if (start.x == 0 or !checkTetrisInChamber(start.x,start.y,3,3,verticalChamber))
                            start.x++;
                        break;
                }
                if (checkTetrisInChamber(start.x,start.y,3,3,verticalChamber))
                    putTetrisInChamber<3,3>(start.x,start.y,rock1,verticalChamber);
            }
            if ((unitCount % 5) == 2) {
                switch (currentFlow) {
                    case '>':
                        start.x++;
                        if (start.x+3 > chamberWidth+1 or !checkTetrisInChamber(start.x,start.y,3,3,verticalChamber))
                            start.x -= 1;
                        break;
                    case '<':
                        start.x--;
                        if (start.x == 0 or !checkTetrisInChamber(start.x,start.y,3,3,verticalChamber))
                            start.x++;
                        break;
                }
                if (checkTetrisInChamber(start.x,start.y,3,3,verticalChamber))
                    putTetrisInChamber<3,3>(start.x,start.y,rock2,verticalChamber);
            }
            if ((unitCount % 5) == 3) {
                switch (currentFlow) {
                    case '>':
                        start.x++;
                        if (start.x+1 > chamberWidth+1 or !checkTetrisInChamber(start.x,start.y,4,1,verticalChamber))
                            start.x -= 1;
                        break;
                    case '<':
                        start.x--;
                        if (start.x == 0 or !checkTetrisInChamber(start.x,start.y,4,1,verticalChamber))
                            start.x++;
                        break;
                }
                if (checkTetrisInChamber(start.x,start.y,4,1,verticalChamber))
                    putTetrisInChamber<4,1>(start.x,start.y,rock3,verticalChamber);
            }
            if ((unitCount % 5) == 4) {
                switch (currentFlow) {
                    case '>':
                        start.x++;
                        if (start.x+2 > chamberWidth+1 or !checkTetrisInChamber(start.x,start.y,2,2,verticalChamber))
                            start.x -= 1;
                        break;
                    case '<':
                        start.x--;
                        if (start.x == 0 or !checkTetrisInChamber(start.x,start.y,2,2,verticalChamber))
                            start.x++;
                        break;
                }
                if (checkTetrisInChamber(start.x,start.y,2,2,verticalChamber))
                    putTetrisInChamber<2,2>(start.x,start.y,rock4,verticalChamber);
            }
            start.y++;
            if ((unitCount % 5) == 0){
                if (!checkTetrisInChamber(start.x,start.y,1,4,verticalChamber)) {
                    putTetrisInChamber<1,4>(start.x,start.y-1,rock0,verticalChamber);
                    tetrisComesToRest(verticalChamber);
                    copyChamber(verticalChamber, verticalChamberCopy);
                    unitCount++;
                    start.x = 3;
                    if (resting > (resting - (resting-start.y) - 1))
                        resting = resting - (resting-start.y) - 1;
                    start.y = resting - 4;
                }
            }
            if ((unitCount % 5) == 1){
                if (!checkTetrisInChamber(start.x,start.y,3,3,verticalChamber)){
                    putTetrisInChamber<3,3>(start.x,start.y-1,rock1,verticalChamber);
                    tetrisComesToRest(verticalChamber);
                    copyChamber(verticalChamber, verticalChamberCopy);
                    unitCount++;
                    start.x = 3;
                    if (resting > (resting - (resting-start.y) - 3))
                        resting = resting - (resting-start.y) - 3;
                    start.y = resting - 4;
                }
            }
            if ((unitCount % 5) == 2){
                if (!checkTetrisInChamber(start.x,start.y,3,3,verticalChamber)) {
                    putTetrisInChamber<3,3>(start.x,start.y-1,rock2,verticalChamber);
                    tetrisComesToRest(verticalChamber);
                    copyChamber(verticalChamber, verticalChamberCopy);
                    unitCount++;
                    start.x = 3;
                    if (resting > (resting - (resting-start.y) - 3))
                        resting = resting - (resting-start.y) - 3;
                    start.y = resting - 4;
                }
            }
            if ((unitCount % 5) == 3){
                if (!checkTetrisInChamber(start.x,start.y,4,1,verticalChamber)) {
                    putTetrisInChamber<4,1>(start.x,start.y-1,rock3,verticalChamber);
                    tetrisComesToRest(verticalChamber);
                    copyChamber(verticalChamber, verticalChamberCopy);
                    unitCount++;
                    start.x = 3;
                    if (resting > (resting - (resting-start.y) - 4))
                        resting = resting - (resting-start.y) - 4;
                    start.y = resting - 4;
                }
            }
            if ((unitCount % 5) == 4){
                if (!checkTetrisInChamber(start.x,start.y,2,2,verticalChamber)) {
                    putTetrisInChamber<2,2>(start.x,start.y-1,rock4,verticalChamber);
                    tetrisComesToRest(verticalChamber);
                    copyChamber(verticalChamber, verticalChamberCopy);
                    unitCount++;
                    start.x = 3;
                    if (resting > (resting - (resting-start.y) - 2))
                        resting = resting - (resting-start.y) - 2;
                    start.y = resting - 4;
                }
            }
            system("clear");
            printMatrix(verticalChamber);
            usleep(50000);
            copyChamber(verticalChamberCopy, verticalChamber);
            restingCorrectionAfterScrollDown = scrollDownChamber(verticalChamber, verticalChamberVisited, x_move, y_move);
            if (restingCorrectionAfterScrollDown > 0) {
                resting += restingCorrectionAfterScrollDown;
                start.y = start.y + restingCorrectionAfterScrollDown;
            }

            copyChamber(verticalChamber, verticalChamberCopy);
            usleep(50000);
//            std::cin.get();
//            std::cout << "E x: " << start.x << " y: " << start.y << std::endl;
//            std::cout << "resting " << resting << std::endl;
//            std::cout << "minResting " << minResting << std::endl;
        }
    }
    std::cout << std::endl;

    std::cout << "How many units tall will the tower of rocks be after 2022 rocks have stopped falling? ";
    std::cout << towerTallUnits << std::endl; 
    return 1;
}
