#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include "CustomFunctions.h"

int main()
{
    std::cout << "Enter a phrase to see if it exists in password.txt\n";
    std::string UserInputPhase = "";
    std::getline(std::cin, UserInputPhase);
    std::cout << "You entered:\n\t" << UserInputPhase << std::endl;

    // get passkey file
    std::ifstream PassKeys;
    PassKeys.open("./Ass3/passkeys.txt", std::fstream::in);

    if(!PassKeys.is_open())
    {
        std::cout << "Passkeys.txt failed to open\n";
        return 1;
    }

    // create pipes
    int fd[2], fd_2[2];

    if(pipe(fd) < 0)
    {
        std::cout << "First pipe failed to open\n";
        return 1;
    }
    if(pipe(fd_2) < 0)
    {
        std::cout << "Second pipe failed to open\n";
        return 1;
    }

    pid_t ChildPId = fork();

    // write user phrase to pipe 1
    write(fd[1], UserInputPhase.c_str(), UserInputPhase.length() + 1);

    if(ChildPId == -1)
    {
        std::cout << "Fork failed\n";
        return 1;
    }
    else if (ChildPId == 0)
    {
        std::string StringFromPipe;
        char ch;

        close(fd[1]);
        while(read(fd[0], &ch, 1) > 0)
        {
            if (ch == '\0')
                break;
            StringFromPipe += ch;
        }

        close(fd[0]);

        std::cout << "Child Got String: " << StringFromPipe << std::endl;

        std::string CurLine = "";
        bool PhraseFound = false;
        while(getline(PassKeys, CurLine))
        {
            if(CurLine == StringFromPipe)
            {
                PhraseFound = true;
                break;
            }
        }

        close(fd_2[0]);
        write(fd_2[1], &PhraseFound, sizeof(bool));
        close(fd_2[1]);

        return 0;
    }
    else
    {
        wait(0);
        close(fd_2[1]);
        bool Found = false;
        read(fd_2[0], &Found, sizeof(bool));
        close(fd_2[0]);
        std::cout << "Was Phrase Found: ";
        Found ? std::cout << "True" : std::cout << "False";
        std::cout << std::endl;
    }

    PassKeys.close();

    return 0;
}