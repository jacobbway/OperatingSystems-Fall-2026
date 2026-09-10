#include <iostream>
#include <chrono>
#include <vector>
#include "CustomFunctions.h"

int main()
{
    int minNumber = 1;
    int maxNumber = 10000;
    int numElementsInVector = 10000000; // 10 million

    std::vector<int> filledVector1 = CreateFilledVector(minNumber, maxNumber, numElementsInVector);
    std::vector<int> filledVector2 = filledVector1;

    auto startQuickTime = std::chrono::high_resolution_clock::now();
    QuickSort(filledVector1);
    auto stopQuickTime = std::chrono::high_resolution_clock::now();
    auto quickSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopQuickTime - startQuickTime);

    auto startCountTime = std::chrono::high_resolution_clock::now();
    CountSort(filledVector2);
    auto stopCountTime = std::chrono::high_resolution_clock::now();
    auto countSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopCountTime - startCountTime);

    std::cout << "\n=======================================================================\n";
    std::cout << "Number of Elements: " << numElementsInVector << " Range of Numbers: " << minNumber << "-" << maxNumber << std::endl;
    std::cout << "Quick Sort Duration: " << quickSortDuration.count() << " microseconds\n";
    std::cout << "Count Sort Duration: " << countSortDuration.count() << " microseconds\n";
    std::cout << "=======================================================================\n";

    int minNumber = 1;
    int maxNumber = 50;
    int numElementsInVector = 10000000; // 10 million

    filledVector1 = CreateFilledVector(minNumber, maxNumber, numElementsInVector);
    filledVector2 = filledVector1;

    startQuickTime = std::chrono::high_resolution_clock::now();
    QuickSort(filledVector1);
    stopQuickTime = std::chrono::high_resolution_clock::now();
    quickSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopQuickTime - startQuickTime);

    startCountTime = std::chrono::high_resolution_clock::now();
    CountSort(filledVector2);
    stopCountTime = std::chrono::high_resolution_clock::now();
    countSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopCountTime - startCountTime);

    std::cout << "\n=======================================================================\n";
    std::cout << "Number of Elements: " << numElementsInVector << " Range of Numbers: " << minNumber << "-" << maxNumber << std::endl;
    std::cout << "Quick Sort Duration: " << quickSortDuration.count() << " microseconds\n";
    std::cout << "Count Sort Duration: " << countSortDuration.count() << " microseconds\n";
    std::cout << "=======================================================================\n";
    return 0;
}