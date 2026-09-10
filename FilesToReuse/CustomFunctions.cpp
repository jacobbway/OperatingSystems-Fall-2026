#include <vector>

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