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
    long x;
    long y;
}test;

struct square2D{
    position2D A,B,C,D;
};

bool pointInTriangle(position2D point, position2D A, position2D B, position2D C)
{
    long long a = 1/2 * (-B.y * C.x + A.y * (-B.x + C.x) + A.x * (B.y - C.y) + B.x * C.y);
    int sign = a < 0 ? -1 : 1;
    long long s = (A.y * C.x - A.x * C.y + (C.y - A.y) * point.x + (A.x - C.x) * point.y) * sign;
    long long t = (A.x * B.y - A.y * B.x + (A.y - B.y) * point.x + (B.x - A.x) * point.y) * sign;

    return s > 0 && t > 0 && (s + t) < 2 * a * sign;
}

bool triangleContains(position2D P, position2D A, position2D B, position2D C) {

    long long det = (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
    long long det1 = det * ((B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x));
    long long det2 = det * ((C.x - B.x) * (P.y - B.y) - (C.y - B.y) * (P.x - B.x));
    long long det3 = det * ((A.x - C.x) * (P.y - C.y) - (A.y - C.y) * (P.x - C.x));
//    std::cout << det1 << " " << det2 << " " << det3 << std::endl;
//    std::cout << (det1 >= 0 && det2 >= 0 && det3 >= 0) << std::endl;
    return  det1 >= 0 &&
            det2 >= 0 &&
            det3 >= 0;
/*    return  det * ((B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x)) >= 0 &&
            det * ((C.x - B.x) * (P.y - B.y) - (C.y - B.y) * (P.x - B.x)) >= 0 &&
            det * ((A.x - C.x) * (P.y - C.y) - (A.y - C.y) * (P.x - C.x)) >= 0;
*/
}

float area(int x1, int y1, int x2, int y2, int x3, int y3)
{
    return abs((x1*(y2-y3) + x2*(y3-y1)+ x3*(y1-y2))/2.0);
}

bool isInside(int x, int y, int x1, int y1, int x2, int y2, int x3, int y3)
{
    /* Calculate area of triangle ABC */
    float A = area (x1, y1, x2, y2, x3, y3);
    /* Calculate area of triangle PBC */
    float A1 = area (x, y, x2, y2, x3, y3);
    /* Calculate area of triangle PAC */
    float A2 = area (x1, y1, x, y, x3, y3);
    /* Calculate area of triangle PAB */
    float A3 = area (x1, y1, x2, y2, x, y);
    /* Check if sum of A1, A2 and A3 is same as A */
    return (A == A1 + A2 + A3);
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
    std::stringstream equipmentInfo;
    std::string line, coordValue, coord;
    char equal, punctuation, coordAxis;
    int nrPositionCantContainABeacon = 0;

    equipmentInfo = readFile((char*)"input");
    position2D sensorPos={0,0}, beaconPos={0,0};
    double cateta1, cateta2, ipotenuza;
    long long minX = 999999999999999, maxX = 0;
    long radius = 0;

    std::vector<square2D> squares;
    std::vector<position2D> beacons;
    square2D square;

    while (getline (equipmentInfo, line, '\n')) {
        std::stringstream info(line);
        bool sensor = true;
        int axisY = 0;
        while (getline (info, coord, ' ')) {
            if (coord.find("=") != std::string::npos) {
                std::istringstream(coord) >> coordAxis >> equal >> coordValue >> punctuation;
                if (coordValue.find(":") != std::string::npos || coordValue.find(",") != std::string::npos)
                    coordValue = coordValue.substr(0, coordValue.size()-1);
//                std::cout << coordAxis << " - " << coordValue << std::endl;
                if (axisY == 2)
                    sensor = false;
 //               std:: cout << "sensorbool: " << sensor << " " << axisY <<  std::endl;
                switch (coordAxis) {
                    case 'x':
                        if (sensor)
                            sensorPos.x = std::stoi(coordValue);
                        else
                            beaconPos.x = std::stoi(coordValue);
                        break;
                    case 'y':
                        if (sensor)
                            sensorPos.y = std::stoi(coordValue);
                        else
                            beaconPos.y = std::stoi(coordValue);
                        break;
                }
                axisY++;
            }
        }

            cateta1 = abs(sensorPos.y - beaconPos.y);
            ipotenuza = cateta1  * (2 / sqrt(2)); // c1 / cos45 = c1 * 2 / sqrt(2)
            cateta2 = sqrt(pow(ipotenuza,2) - pow(cateta1,2));

            square.B.x = sensorPos.x;
            square.D.x = sensorPos.x;

            square.A.y = sensorPos.y;
            square.C.y = sensorPos.y;

            if ( (sensorPos.x - beaconPos.x ) > 0 )
            {
                square.A.x = beaconPos.x - round(cateta2);
                square.C.x = square.A.x + 2 * (sensorPos.x - square.A.x);
                square.B.y = sensorPos.y - (sensorPos.x - square.A.x);
                square.D.y = sensorPos.y + (sensorPos.x - square.A.x);
            }
            else if ( (sensorPos.x - beaconPos.x ) < 0 )
            {
                square.C.x = beaconPos.x + int(round(cateta2));
                square.A.x = square.C.x - 2 * (square.C.x - sensorPos.x);
                square.B.y = sensorPos.y - (square.C.x - sensorPos.x);
                square.D.y = sensorPos.y + (square.C.x - sensorPos.x);
            }

            std::cout << " sensorPos.x: " << sensorPos.x;
            std::cout << " sensorPos.y: " << sensorPos.y;
            std::cout << " beaconPos.x: " << beaconPos.x;
            std::cout << " beaconPos.y: " << beaconPos.y;
            std::cout << std::endl;

            std::cout << " A.x: " << square.A.x;
            std::cout << " A.y: " << square.A.y;
            std::cout << " B.x: " << square.B.x;
            std::cout << " B.y: " << square.B.y;
            std::cout << " C.x: " << square.C.x;
            std::cout << " C.y: " << square.C.y;
            std::cout << " D.x: " << square.D.x;
            std::cout << " D.y: " << square.D.y;
            std::cout << std::endl;

            if ( minX > square.A.x )
                minX = square.A.x;
            if ( maxX < square.C.x )
                maxX = square.C.x;

            squares.push_back(square); 
            beacons.push_back(beaconPos);
    }

    position2D punctul, S, P;
    nrPositionCantContainABeacon = 0;

    std::cout << "minX: " << minX << " maxX: " << maxX << std::endl;

    punctul.y = 2000000; 
    P.y = 2000000;
    //P.y = 10;
    for (long long x = minX; x <= maxX; x++)
    {
        bool notfreePlace = false;
        P.x = x;
        for (square2D patrat: squares)
        {
/*            std::cout << " A.x: " << patrat.A.x;
            std::cout << " A.y: " << patrat.A.y;
            std::cout << " B.x: " << patrat.B.x;
            std::cout << " B.y: " << patrat.B.y;
            std::cout << " C.x: " << patrat.C.x;
            std::cout << " C.y: " << patrat.C.y;
            std::cout << " D.x: " << patrat.D.x;
            std::cout << " D.y: " << patrat.D.y;
            std::cout << std::endl;*/

            radius = (patrat.C.x - patrat.A.x) / 2;
            S.x = patrat.A.x + radius;
            S.y = patrat.B.y + radius;
            cateta2 = abs(S.y - P.y);

            if ( (P.x >= (S.x - radius + cateta2)) && (P.x <= (S.x + radius - cateta2)) )
            {
                notfreePlace = true;
            }
        }
        for (position2D beacon_: beacons)
            if (beacon_.x == P.x && beacon_.y == P.y)
                notfreePlace = false;
        if ( notfreePlace )
            nrPositionCantContainABeacon++;
            
    }
    std::cout << "In the row where y=2000000, how many positions cannot contain a beacon? ";
    std::cout << nrPositionCantContainABeacon << std::endl;
/*
    for (long long x = minX; x <= maxX; x++)
    {
        bool notfreePlace = false;
        punctul.x = x; 
        for (square2D patrat: squares)
            if ( punctul.y >= patrat.B.y && punctul.y <= patrat.A.y ) {
                //if (triangleContains(punctul, patrat.A, patrat.B, patrat.C))
                if (isInside(punctul.x, punctul.y, patrat.A.x, patrat.A.y, patrat.B.x, patrat.B.y, patrat.C.x, patrat.C.y))
                    notfreePlace = true;
            }
            else {
                //if (triangleContains(punctul, patrat.A, patrat.C, patrat.D)) 
                if (isInside(punctul.x, punctul.y, patrat.A.x, patrat.A.y, patrat.C.x, patrat.C.y, patrat.D.x, patrat.D.y))
                    notfreePlace = true;
            }
        for (position2D beacon_: beacons)
            if (beacon_.x == punctul.x && beacon_.y == punctul.y)
                notfreePlace = false;
        if ( notfreePlace ) 
            nrPositionCantContainABeacon++;
    }
    std::cout << "In the row where y=2000000, how many positions cannot contain a beacon? ";
    std::cout << nrPositionCantContainABeacon << std::endl; 
*/
/*    nrPositionCantContainABeacon = 0;
    for (square2D patrat: squares){
        if ( punctul.y >= patrat.B.y && punctul.y < patrat.A.y ) {
            for (long long x = patrat.A.x; x <= patrat.C.x; x++) {
                punctul.x = x; 
                if (triangleContains(punctul, patrat.A, patrat.B, patrat.C))
                    nrPositionCantContainABeacon++;
                for (position2D beacon_: beacons)
                    if (beacon_.x == punctul.x && beacon_.y == punctul.y)
                        nrPositionCantContainABeacon--;
            }
        }else {
            for (long long x = patrat.A.x; x <= patrat.C.x; x++) {
                punctul.x = x; 
                if (triangleContains(punctul, patrat.A, patrat.C, patrat.D)) 
                    nrPositionCantContainABeacon++;
                for (position2D beacon_: beacons)
                    if (beacon_.x == punctul.x && beacon_.y == punctul.y)
                        nrPositionCantContainABeacon--;
                    
            }
        }
    }    
    std::cout << "In the row where y=2000000, how many positions cannot contain a beacon? ";
    std::cout << nrPositionCantContainABeacon << std::endl; 
*/
    return 1;
}
