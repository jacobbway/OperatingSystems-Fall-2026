#include <iostream>
#include <fstream>
#include <vector>
#include "CustomFunctions.h"


int main()
{
    std::ifstream inFile;
    inFile.open("./Ass2/commands.txt", std::fstream::in);

    if(!inFile.is_open())
    {
        std::cout << "Input File Failed to open";
        return 1;
    }

    std::vector<std::string> linesFromFile;
    std::string curLine;

    while(std::getline(inFile, curLine))
    {
        linesFromFile.push_back(curLine);
        curLine = "";
    }

    inFile.close();

    std::vector<char> symsToFind = {'|', '<', '>'};

    std::vector<std::string> outPutLines = FindSymbolInString(linesFromFile, symsToFind);

    std::ofstream outFile;
    outFile.open("./Ass2/parsingreslts.txt", std::fstream::out);
    if(!outFile.is_open())
    {
        std::cout << "Output file failed to open\n";
        return 1;
    }

    for(std::string curLine : outPutLines)
    {
        outFile << curLine << '\n';
    }
    outFile.close();

    std::cout << "Oh wow we made it to the end hope it worked!\n";
    return 0;
}