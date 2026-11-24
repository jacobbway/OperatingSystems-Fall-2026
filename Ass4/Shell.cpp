#include <iostream>
#include <string.h>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>
#include <regex>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void PrintCWD();
void TokenizeStringForEXECVP(char* InputString, char* CommandString[]);
void PrintHistory(std::vector<std::string> VectToPrint);
int ContainsRedirect(std::string InputStr);

void RedirectOutput(char* args[]);
void RedirectInput(char* args[]);
void ExecutePipe(char* args[]);
void ExecuteCommand(char* args[]);

int main()
{
    const std::string ShellString = "<Ass4Shell> ";
    std::string CurLine = "";
    std::vector<std::string> HistoryVector;

    std::cout << "======================================\n";
    std::cout << "\tWelcome to Ass4Shell!\n";
    std::cout << "======================================\n";

    while(true)
    {
        std::cout << ShellString;
        getline(std::cin, CurLine);

        HistoryVector.push_back(CurLine);

        char* InputString = new char [CurLine.length() + 1];
        strcpy(InputString, CurLine.c_str());

        if(CurLine == "exit")
        {
            std::cout << "======================================\n";
            std::cout << "\tThanks for using Ass4Shell!\n";
            std::cout << "======================================\n";
            delete[] InputString;
            break;
        }        
        else if(CurLine == "pwd")
        {
            PrintCWD();
            delete[] InputString;
            continue;
        }
        else if(CurLine == "help")
        {
            std::cout << "\thelp - Shows this screen\n";
            std::cout << "\texit - exits the shell\n";
            std::cout << "\tpwd - prints working directory\n";
            std::cout << "\thistory - prints all entries\n";
            delete[] InputString;
            continue;
        }
        else if(CurLine == "history")
        {
            PrintHistory(HistoryVector);
            delete[] InputString;
            continue;
        }
        else
        {
            char* args[64];
            TokenizeStringForEXECVP(InputString, args);
            if (args[0] == nullptr)
            {
                delete[] InputString;
                continue;
            }

            int redirectType = ContainsRedirect(CurLine);

            if (redirectType == 2)
                RedirectOutput(args);
            else if (redirectType == 3)
                RedirectInput(args);
            else if (redirectType == 4)
                ExecutePipe(args);
            else
                ExecuteCommand(args);

            delete[] InputString;
        }
    }
}

int ContainsRedirect(std::string InputStr)
{
    if (InputStr.find(">>") != std::string::npos)
        return 1;
    else if (InputStr.find(">") != std::string::npos)
        return 2;
    else if (InputStr.find("<<") != std::string::npos)
        return 0;
    else if (InputStr.find("<") != std::string::npos)
        return 3;
    else if (InputStr.find("|") != std::string::npos) 
        return 4;
    else
        return 0;
}

void PrintCWD()
{
    try
    {
        std::filesystem::path cwd = std::filesystem::current_path();
        std::cout << cwd << std::endl;
    }
    catch (const std::filesystem::filesystem_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

void TokenizeStringForEXECVP(char* InputString, char* CommandString[])
{

    int i = 0;

    for(char * Token = strtok(InputString, " "); Token != nullptr && i < 63; Token = strtok(nullptr, " "))
    {
        CommandString[i++] = Token;
    }
    CommandString[i] = nullptr;
}

void PrintHistory(std::vector<std::string> VectToPrint)
{
    std::cout << "//////////////////////////////////////\n";
    std::cout << "\tSTART OF HISTORY\n\n";
    int count = 1;
    for(std::string CurStr : VectToPrint)
    {
        std::cout << count++ << " " << CurStr << std::endl;
    }
    std::cout << "\n\tEND OF HISTORY\n";
    std::cout << "//////////////////////////////////////\n";
}

void RedirectOutput(char* args[])
{
    int i = 0;
    while (args[i] != nullptr && strcmp(args[i], ">") != 0) i++;
    char* filename = args[i + 1];
    args[i] = nullptr;

    int outFd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666);
    int origOut = dup(1);
    dup2(outFd, 1);
    close(outFd);

    if (fork() == 0)
    {
        if (execvp(args[0], args) < 0)
        {
            std::cout << "Failed to execvp or you entered nonsense\n";
            exit(1);
        }
    }
    wait(0);

    dup2(origOut, 1);
    close(origOut);
}

void RedirectInput(char* args[])
{
    int i = 0;
    while (args[i] != nullptr && strcmp(args[i], "<") != 0) i++;
    char* filename = args[i + 1];
    args[i] = nullptr;

    int inFd = open(filename, O_RDONLY);
    int origIn = dup(0);
    dup2(inFd, 0);
    close(inFd);

    if (fork() == 0)
    {
        if (execvp(args[0], args) < 0)
        {
            std::cout << "Failed to execvp or you entered nonsense\n";
            exit(1);
        }
    }
    wait(0);

    dup2(origIn, 0);
    close(origIn);
}

void ExecutePipe(char* args[])
{
    int i = 0;
    while (args[i] != nullptr && strcmp(args[i], "|") != 0) i++;
    args[i] = nullptr;
    char** cmd1 = args;
    char** cmd2 = &args[i + 1];

    int fds[2];
    pipe(fds);

    int origIn = dup(0);
    int origOut = dup(1);

    if (fork() == 0)
    {
        dup2(fds[1], 1);
        close(fds[1]);
        close(fds[0]);
        if (execvp(cmd1[0], cmd1) < 0)
            exit(1);
    }
    wait(0);

    dup2(fds[0], 0);
    close(fds[0]);
    dup2(origOut, 1);
    close(fds[1]);

    if (fork() == 0)
    {
        if (execvp(cmd2[0], cmd2) < 0)
            exit(1);
    }
    wait(0);

    dup2(origIn, 0);
    dup2(origOut, 1);
    close(origIn);
    close(origOut);
}

void ExecuteCommand(char* args[])
{
    if (fork() == 0)
    {
        if (execvp(args[0], args) < 0)
        {
            std::cout << "Failed to execvp or you entered nonsense\n";
            exit(1);
        }
    }
    wait(0);
}