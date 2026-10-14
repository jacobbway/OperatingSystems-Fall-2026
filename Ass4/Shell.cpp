#include <iostream>
#include <string.h>
#include <vector>
#include <filesystem>
#include <unistd.h>
#include <sys/wait.h>
#include <regex>

void PrintCWD();
void TokenizeStringForEXECVP(char* InputString, char* CommandString[]);
void PrintHistory(std::vector<std::string> VectToPrint);
int ContainsRedirect(std::string InputStr);

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
            break;
        }        
        else if(CurLine == "pwd")
        {
            PrintCWD();
            continue;
        }
        else if(CurLine == "help")
        {
            std::cout << "\thelp - Shows this screen\n";
            std::cout << "\texit - exits the shell\n";
            std::cout << "\tpwd - prints working directory\n";
            std::cout << "\thistory - prints all entries\n";
            continue;
        }
        else if(CurLine == "history")
        {
            PrintHistory(HistoryVector);
            continue;
        }
        else
        {
            switch(ContainsRedirect(CurLine))
            {
                case 1:
                    std::cout << ">> found\n";
                    break;
                case 2:
                    std::cout << "> found\n";
                    break;
                case 3:
                    std::cout << "< found\n";
                    break;
                case 4:
                    std::cout << "| found\n";
                    break;
                case 0:
                default:
                    break;
            }
            pid_t Child = fork();
    
            if(Child == 0)
            {
                char* ExecVPString[64];
                TokenizeStringForEXECVP(InputString, ExecVPString);
                if(execvp(ExecVPString[0], ExecVPString) < 0)
                {
                    std::cout << "Failed to execvp or you entered nonsense\n";
                    return 0;
                }
            }
            else
                wait(0);
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
    std::cout << "\tSTART OF HISTORY\n";
    for(std::string CurStr : VectToPrint)
    {
        std::cout << CurStr << std::endl;
    }
    std::cout << "\n\n\tEND OF HISTORY\n";
    std::cout << "//////////////////////////////////////\n";
}