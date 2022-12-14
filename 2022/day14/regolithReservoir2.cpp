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


struct position2D{
    int x;
    int y;
}point2D, start, end;

int signOfNumber(int number)
{
    if (number > 0)
        return 1;
    if (number < 0)
        return -1;
    if (number == 0)
        return 0;
    return 0; 
}

bool operator<(const position2D& lhs, const position2D& rhs)
{
//    std::cout << "lhs x: " << lhs.x << " lhs.y: " << lhs.y << std::endl;
//    std::cout << "rhs x: " << rhs.x << " rhs.y: " << rhs.y << std::endl;
//    std::cout << (lhs.x != rhs.x || lhs.y != rhs.y) << std::endl;
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

std::set<position2D> drawLine(int x1, int y1, int x2, int y2)
{ 
    int u = x2-x1;
    int v = y2-y1;
    int d1x = signOfNumber(u);
    int d1y = signOfNumber(v);
    int d2x = signOfNumber(u);
    int d2y = 0;
    int m = abs(u);
    int n = abs(v);
    std::set<position2D> result;
    position2D point_2D;
    if (not (m > n)) {
        d2x = 0;
        d2y = signOfNumber(v);
        m = abs(v);
        n = abs(u);
    }
    
    int s = int(m/2);

    for (int i = 0; i < round(m)+1; i++) {
        point_2D.x = x1;
        point_2D.y = y1;
//        std::cout << x1 << " " << y1 << std::endl;
        result.insert(point_2D);
        s = s + n;
        if (not (s < m)) {
            s = s - m;
            x1 = x1 + round(d1x);
            y1 = y1 + round(d1y);
        }
        else{
            x1 = x1 + round(d2x);
            y1 = y1 + round(d2y);
        }
    }
//    for (auto it1 = result.begin(); it1 != result.end(); it1++)
//        std::cout << "drawLine SET: " << it1->x << " " << it1->y << " " << std::endl;
    return result;
}

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
    std::stringstream reservoirPoints;
    std::string coord, point;
    char comma;
    int numberOfSandParticle = 0, line = 0;
    position2D startSandPos={500,0};
    std::map<int, std::vector<position2D>> points2D;
    std::set<position2D> allPoints;
    int maxY = 0; 

    reservoirPoints = readFile((char*)"input");
    while (getline (reservoirPoints, coord, '\n')) {
        std::stringstream coords(coord);
        while (getline (coords, point, ' ')) {
            if (point != "->") {
                std::istringstream(point) >> point2D.x >> comma >>  point2D.y;
                points2D[line].push_back(point2D);
                if ( maxY < point2D.y )
                    maxY = point2D.y;
            }
        }
        line++;
    }
    for (auto elem: points2D)
    {
        start = *elem.second.begin();
        for (auto it = elem.second.begin() + 1; it != elem.second.end(); it++)
        {
            end = *it;
//            std::cout << start.x << " " << start.y << " " << end.x << " " << end.y << std::endl;
            auto setToBeAdded = drawLine(start.x, start.y, end.x, end.y);
//            std::cout << "ADDING!!!" << std::endl;
            for (auto it1 = setToBeAdded.begin(); it1 != setToBeAdded.end(); it1++) {
//                std::cout << "drawLine SET: " << it1->x << " " << it1->y << " " << std::endl;
                allPoints.insert(*it1);  
            }
            start = end;
        }
    }   

    std::cout << "Lowest point: " << maxY+2 << std::endl;
//    for (auto it_ = allPoints.begin(); it_ != allPoints.end(); it_++)
//        std::cout << "allPoints: " << it_->x << " " << it_->y << " " << std::endl;
//    std::cout << std::endl;

    bool sanding = true;
    bool found;
    position2D orig;
    maxY += 2;
    while (sanding){
        orig.x = startSandPos.x;
        orig.y = startSandPos.y+1;
//        std::cout << "Sx: " << startSandPos.x << " Sy: " << startSandPos.y << std::endl; 
//        std::cout << "Ox: " << orig.x << " Oy: " << orig.y << std::endl; 
        found = allPoints.contains(orig);
        if (found || orig.y == maxY ) {
            orig.x = startSandPos.x -1;
            found = allPoints.contains(orig);
            if (found || orig.y == maxY) {
                orig.x = startSandPos.x + 1;
                found = allPoints.contains(orig);
                if (found || orig.y == maxY) {
                    allPoints.insert(startSandPos);
                    if (startSandPos.x == 500 && startSandPos.y == 0 && numberOfSandParticle > 0)
                    {
                        std::cout << "breaking\n";
                        numberOfSandParticle++;
                        break;
                    }
                    numberOfSandParticle++;
                    startSandPos = {500, 0};
                }
                else
                    startSandPos = orig;
            }
            else
                startSandPos = orig;
        }
        else
            startSandPos = orig;
/*        
        if (startSandPos.x == 500 && startSandPos.y == 0 )
        {
            break;
        }
        */
//        std::cout << std::endl;
    }

    std::cout << "How many units of sand come to rest? ";
    std::cout << numberOfSandParticle << std::endl; 

    return 1;
}
