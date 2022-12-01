#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <map>

#define N 100
#define M 150

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

unsigned long int syntaxChecker(std::vector<char> syntaxLine)
{
    std::vector<char> syntax; 
    char poppedChar;
    char openSyntax[] = {'(', '[', '{', '<'};
    char closedSyntax[] = {')', ']', '}', '>'};
    char *endOpenSyntax = openSyntax + sizeof(openSyntax) / sizeof(openSyntax[0]);
    char *endClosedSyntax = closedSyntax + sizeof(closedSyntax) / sizeof(closedSyntax[0]);
    char* position;
    unsigned long int sum;

    for (char syntaxChar: syntaxLine){
        position = std::find(openSyntax, endOpenSyntax, syntaxChar);
        if ( position != endOpenSyntax )
            syntax.push_back(syntaxChar);

        position = std::find(closedSyntax, endClosedSyntax, syntaxChar);
        if ( position != endClosedSyntax )
        {
            poppedChar = syntax.back();
            syntax.pop_back();
            switch (syntaxChar)
            {
                case ')':
                    if ( poppedChar != '(' )
                        return 0;
                    break;
                case ']':
                    if ( poppedChar != '[' )
                        return 0; 
                    break;
                case '}':
                    if ( poppedChar != '{' )
                        return 0;
                    break;
                case '>':
                    if ( poppedChar != '<' )
                        return 0; 
                    break;
            }
        }
    }
    sum = 0;
    std::cout << std::endl;
    for(int i = syntax.size() -1 ; i >= 0 ; i--)    
//    for (char syntaxChar: syntax)
    {
        std::cout << syntax[i];
        switch (syntax[i])
        {
            case '(':
                sum *= 5;
                sum += 1;
                break;
            case '[':
                sum *= 5;
                sum += 2;
                break;
            case '{':
                sum *= 5;
                sum += 3;
                break;
            case '<':
                sum *= 5;
                sum += 4;
                break;
        }
    }

    return sum; 
}

int main(void)
{
//    char syntax[N][M];
    std::map<int, std::vector<char>> syntax;
    std::vector<char> syntaxLine;

    int i, j, k;
    unsigned long int sum;
    std::string line;

    std::stringstream smokeFlows;
    smokeFlows = readFile((char*)"input");

// load syntax with values from file
    i = 0;
    while (getline (smokeFlows, line, '\n')) {
        for (k = 0; k < line.length(); k++)
        {
            syntaxLine.push_back(line[k]);
        }
        syntax[i] = syntaxLine;
        syntaxLine.clear();
        i++;
    }

    for (const auto& [key, value] : syntax){
        std::cout << '[' << key << "] = ";
        for (auto syntaxChar: value)
            std::cout << syntaxChar;
        std::cout << std::endl;
    }
/*    
    ): 1 points.
    ]: 2 points.
    }: 3 points.
    >: 4 points.
*/
    std::vector<unsigned long int> syntaxScores;
    for (const auto& [lineNumber, syntaxLine] : syntax){
        std::cout << "Line number: "<< lineNumber << " "; 
        if ( auto incompleteSyntaxSum = syntaxChecker(syntaxLine); incompleteSyntaxSum != 0)
        {
            std::cout << "Syntax OK" << incompleteSyntaxSum << std::endl;
            for (auto character: syntaxLine)
            {
                std::cout << character;
            }
            syntaxScores.push_back(incompleteSyntaxSum);
        }

        std::cout << std::endl;
    }

    std::sort(syntaxScores.begin(),syntaxScores.end());
std::cout << "What is the middle score? " << syntaxScores.size() << " " << syntaxScores.size()/2;
std::cout << " " << syntaxScores[23] << std::endl;
    return 1;
}
     
