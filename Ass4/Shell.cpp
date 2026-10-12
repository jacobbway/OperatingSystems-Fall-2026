#include <iostream>
#include <string.h>
#include <vector>


int main()
{
    const std::string ShellString = "<Ass4Shell> ";
    std::string CurLine = "";
    std::vector<std::string> HistoryVector;

    while(true)
    {
        std::cout << ShellString;
        getline(std::cin, CurLine);

        HistoryVector.push_back(CurLine);

        char* InputString = new char [CurLine.length() + 1];
        strcpy(InputString, CurLine.c_str());

        
    }
}