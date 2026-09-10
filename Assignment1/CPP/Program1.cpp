#include <iostream>
#include <chrono>
#include <vector>
#include "CustomFunctions.h"

int main()
{
    int minNumber = 1;
    int maxNumber = 10000;
    int numElementsInVector = 100;//000000; // 100 million

    std::vector<int> filledVector1 = CreateFilledVector(minNumber, maxNumber, numElementsInVector);
    std::vector<int> filledVector2 = filledVector1;

    for(auto curItem : filledVector1) 
    {
        std::cout << curItem << std::endl;
    }

    auto startQuickTime = std::chrono::high_resolution_clock::now();
    QuickSort(filledVector1);
    auto stopQuickTime = std::chrono::high_resolution_clock::now();
    auto quickSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopQuickTime - startQuickTime);

    auto startCountTime = std::chrono::high_resolution_clock::now();
    CountSort(filledVector2);
    auto stopCountTime = std::chrono::high_resolution_clock::now();
    auto countSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopCountTime - startCountTime);

    for (int i = 0; i < filledVector1.size(); i++)
    {
        std::cout << "Quick Sort: " << filledVector1[i] << " Count Sort: " << filledVector2[i] << std::endl;
    }

    std::cout << "Quick Sort Duration: " << quickSortDuration.count() << " microseconds\n";
    std::cout << "Count Sort Duration: " << countSortDuration.count() << " microseconds\n";

    return 0;
}