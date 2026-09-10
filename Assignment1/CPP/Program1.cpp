#include <iostream>
#include <chrono>
#include <random>

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
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<int> distr(minNumber, maxNumber);
    
    std::vector<int> filledVector(numElementsInVector);

    for(int i = 0; i < filledVector.size(); i++)
    {
        filledVector[i] = distr(gen);
    }

    return filledVector;
}