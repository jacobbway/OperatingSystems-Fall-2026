#include <iostream>
#include <cstring>
#include <regex>
#include <iterator>

int main()
{
    std::string inputString = "";
    std::regex spaceToken("\\s+");

    std::cout << "Enter string\n";
    std::getline(std::cin, inputString);

    std::sregex_token_iterator iter(inputString.begin(), inputString.end(), spaceToken, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> tokens(iter, end);

    std::vector<const char*> c_strings;
    c_strings.reserve(tokens.size());

    for (const auto& token : tokens)
    {
        c_strings.push_back(token.c_str());
    }

    const char** c_str_array = c_strings.data();
    size_t array_size = tokens.size();

    std::cout << "Tokenized c_string from std::string:\n";
    for(size_t i = 0; i < array_size; ++i)
    {
        std::cout << "Token [" << i << "]:" << c_str_array[i] << "\n";
    }

    return 0;
}