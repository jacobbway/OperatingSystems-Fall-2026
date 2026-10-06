#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <sys/wait.h>
#include <fstream>
#include <fcntl.h>

int main()
{
    // prompt user for a command
    std::string UserCommand = "";
    std::cout << "Enter a basic command linux command (Example: ls)\n";
    getline(std::cin, UserCommand);

    // convert to c string
    char* UserCString = new char [UserCommand.length() + 1];
    strcpy(UserCString, UserCommand.c_str());

    // create a pipe
    int fd[2];
    if(pipe(fd) < 0)
    {
        std::cout << "Failed to create a pipe\n";
        return 1;
    }

    // create a child
    pid_t Child = fork();

    // write the cstring into pipe
    write(fd[1], UserCString, UserCommand.length() + 1);
    close(fd[1]);

    if(Child < 0)
    {
        std::cout << "Failed to create a fork!\n";
        return 1;
    }
    else if( Child == 0)
    {
        // capture original std::cout and then redirect output to file
        int OriginalSTDCOUT = dup(1);
        int fo = open("./Ass3/outputredir.txt", O_WRONLY | O_APPEND);
        if(fo < 0)
        {
            std::cout << "Couldn't open the output file\n";
            std::exit(1);
        }

        dup2(fo, 1);

        std::cout << UserCommand << std::endl;

        close(fd[1]);
        char buffer[1024];
        int bytesRead = read(fd[0], buffer, sizeof(buffer) - 1);
        buffer[bytesRead] = '\0';

        char* CommandTokens[64];
        int i = 0;

        for(char* token = strtok(buffer, " "); token != nullptr && i < 63; token = strtok(nullptr, " "))
        {
            CommandTokens[i++] = token;
        }
        CommandTokens[i] = nullptr;

        if(execvp(CommandTokens[0], CommandTokens) < 0)
        {
            std::cout << "Failed to execvp\n";
        }
        close(fo);
        fflush(stdout);

        dup2(OriginalSTDCOUT, 1);
        
        return 0;
    }
    else
    {
        wait(0);
        std::cout << "Execvp wrote to a file\n";
    }

    return 0;
}