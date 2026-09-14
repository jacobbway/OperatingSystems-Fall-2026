#include <iostream>

int main()
{
    std::string userInputString = "";
    std::string userToken = "";

    std::cout << "Enter a string\n";
    std::getline(std::cin, userInputString);

    std::cout << "Enter a token\n";
    std::getline(std::cin, userToken);
    userInputString.find(userToken) != std::string::npos ? std::cout << "Found\n" : std::cout << "Not Found\n";

    return 0;
}