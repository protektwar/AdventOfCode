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

char syntaxChecker(std::vector<char> syntaxLine)
{
    std::vector<char> syntax; 
    char poppedChar;
    char openSyntax[] = {'(', '[', '{', '<'};
    char closedSyntax[] = {')', ']', '}', '>'};
    char *endOpenSyntax = openSyntax + sizeof(openSyntax) / sizeof(openSyntax[0]);
    char *endClosedSyntax = closedSyntax + sizeof(closedSyntax) / sizeof(closedSyntax[0]);
    char* position;

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
                        return syntaxChar;
                    break;
                case ']':
                    if ( poppedChar != '[' )
                        return syntaxChar;
                    break;
                case '}':
                    if ( poppedChar != '{' )
                        return syntaxChar;
                    break;
                case '>':
                    if ( poppedChar != '<' )
                        return syntaxChar;
                    break;
            }
        }
    }

    return ' '; 
}

int main(void)
{
//    char syntax[N][M];
    std::map<int, std::vector<char>> syntax;
    std::vector<char> syntaxLine;

    int i, j, k, sum;
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
    ): 3 points.
    ]: 57 points.
    }: 1197 points.
    >: 25137 points.
*/
    sum = 0;
    for (const auto& [lineNumber, syntaxLine] : syntax){
        std::cout << "Line number: "<< lineNumber << " "; 
        if ( char error = syntaxChecker(syntaxLine); error == ' ' )
            std::cout << "Syntax OK";
        else
        {
            std::cout << "SyntaxError " << error;
            switch (error)
            {
                case ')':
                    sum += 3;
                    break;
                case ']':
                    sum += 57;
                    break;
                case '}':
                    sum += 1197;
                    break;
                case '>':
                    sum += 25137;
                    break;
            }
        }

        std::cout << std::endl;
    }
std::cout << "What is the total syntax error score for those errors? " << sum << std::endl;
    return 1;
}
     
