#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <vector>
#include "FilesToReuse/CustomFunctions.h"

int main()
{
    std::cout << "Enter a phrase to see if it exists in password.txt\n";
    std::string UserInputPhase = "";
    std::getline(std::cin, UserInputPhase);
    std::cout << "You entered:\n\t" << UserInputPhase << std::endl;
    
    // Tokenize string into a vector
    std::vector<std::string> InputStringVector = TokenizeString(UserInputPhase);
    // Create c string of token vector + 1
    char* InputPhase[InputStringVector.size() + 1];

    // turn each token into a c string
    for(int i = 0; i < InputStringVector.size(); i++)
        InputPhase[i] = (char*)InputStringVector[i].c_str();
    
    // c strings end in NULL
    InputPhase[InputStringVector.size()] = NULL;

    // create two pipes
    int fds[2];
    int fds_1[2];

    if(pipe(fds) == -1)
    {
        std::cerr << "Pipe creation failed\n";
        std::exit(1);
    }
}