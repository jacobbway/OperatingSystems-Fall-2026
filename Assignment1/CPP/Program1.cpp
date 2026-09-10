#include <iostream>
#include <chrono>
#include "CustomFunctions.h"

int main()
{
    int minNumber = 1;
    int maxNumber = 10000;
    int numElementsInVector = 100000000; // 100 million

    std::vector<int> filledVector1, filledVector2 = CreateFilledVector(minNumber, maxNumber, numElementsInVector);

    return 0;
}