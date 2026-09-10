#include <iostream>
#include <chrono>
#include <vector>
#include <thread>
#include "CustomFunctions.h"

int main()
{
    int minNumber = 1;
    int maxNumber = 10000;
    int numElementsInVector = 1000000; // 1 million

    std::vector<int> *filledVector1 = CreateFilledVector(minNumber, maxNumber, numElementsInVector);
    std::vector<int> *filledVector2 = new std::vector<int>(*filledVector1);

    std::chrono::microseconds::rep quickSortDuration = 0;
    std::chrono::microseconds::rep countSortDuration = 0;

    std::thread QuickSortThread([&]() {
        auto startQuickTime = std::chrono::high_resolution_clock::now();
        QuickSort(filledVector1, 0 , (*filledVector1).size() - 1);
        auto stopQuickTime = std::chrono::high_resolution_clock::now();
        quickSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopQuickTime - startQuickTime).count();
    });

    std::thread CountSortThread([&]() {
        auto startCountTime = std::chrono::high_resolution_clock::now();
        CountSort(filledVector2);
        auto stopCountTime = std::chrono::high_resolution_clock::now();
        countSortDuration = std::chrono::duration_cast<std::chrono::microseconds>(stopCountTime - startCountTime).count();
    });

    QuickSortThread.join();
    CountSortThread.join();

    std::cout << "\n==================================================================\n";
    std::cout << "Number of Elements: " << numElementsInVector << " Range of Numbers: " << minNumber << "-" << maxNumber << std::endl;
    std::cout << "Quick Sort Duration: " << quickSortDuration << " microseconds\n";
    std::cout << "Count Sort Duration: " << countSortDuration << " microseconds\n";
    std::cout << "==================================================================\n";
    
    delete filledVector1;
    delete filledVector2;
    
    minNumber = 1;
    maxNumber = 50;

    std::vector<int> *filledVector3 = CreateFilledVector(minNumber, maxNumber, numElementsInVector);
    std::vector<int> *filledVector4 = new std::vector<int>(*filledVector3);

    std::chrono::microseconds::rep quickSortDuration2 = 0;
    std::chrono::microseconds::rep countSortDuration2 = 0;

    std::thread QuickSortThread2([&]() {
        auto startQuickTime = std::chrono::high_resolution_clock::now();
        QuickSort(filledVector3, 0 , (*filledVector3).size() - 1);
        auto stopQuickTime = std::chrono::high_resolution_clock::now();
        quickSortDuration2 = std::chrono::duration_cast<std::chrono::microseconds>(stopQuickTime - startQuickTime).count();
    });

    std::thread CountSortThread2([&]() {
        auto startCountTime = std::chrono::high_resolution_clock::now();
        CountSort(filledVector4);
        auto stopCountTime = std::chrono::high_resolution_clock::now();
        countSortDuration2 = std::chrono::duration_cast<std::chrono::microseconds>(stopCountTime - startCountTime).count();
    });

    QuickSortThread2.join();
    CountSortThread2.join();

    std::cout << "\n=================================================================\n";
    std::cout << "Number of Elements: " << numElementsInVector << " Range of Numbers: " << minNumber << "-" << maxNumber << std::endl;
    std::cout << "Quick Sort Duration: " << quickSortDuration2 << " microseconds\n";
    std::cout << "Count Sort Duration: " << countSortDuration2 << " microseconds\n";
    std::cout << "=================================================================\n";

    delete filledVector3;
    delete filledVector4;

    return 0;
}