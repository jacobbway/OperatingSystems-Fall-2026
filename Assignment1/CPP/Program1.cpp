#include <iostream>
#include <chrono>
#include <rand>

std::vector<int> CreateFilledVector(int minNumber, int maxNumber, int numElementsInVector);

int main()
{
    int minNumber = 1;
    int maxNumber = 10000;
    int numElementsInVector = 100000000; // 100 million

    std::vector<int> filledVector1, filledVector2 = CreateFilledVector(minNumber, maxNumber, numElementsInVector);

    return 0;
}

std::vector<int> CreateFilledVector(int minNumber, int maxNumber, int numElementsInVector)
{
    
}