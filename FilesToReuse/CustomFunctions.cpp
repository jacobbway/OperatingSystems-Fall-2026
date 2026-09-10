#include <vector>
#include <random>


/// @brief Creates a vector filled with range of numbers of a size
/// @param minNumber lowest number of range
/// @param maxNumber highest number of range
/// @param numElementsInVector # of elements in vector
/// @return a vector filled with psuedo random numbers from a range
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
/// @brief uses quick sort to sort a vector of ints
/// @param inputVector the vector to sort
/// @param low 
/// @param high 
void QuickSort(std::vector<int> &inputVector, int low = 0, int high = -1)
{
    if (high == -1) high = inputVector.size() - 1;

    if (low < high)
    {
        int pivotIndex = QuickSortHelper(inputVector, low, high);
        QuickSort(inputVector, low, pivotIndex+1);
        QuickSort(inputVector, pivotIndex+1, high);
    }
}

/// @brief Helper for quick sort
/// @param inputVector 
/// @param low 
/// @param high 
/// @return an index to use as a pivot
int QuickSortHelper(std::vector<int> &inputVector, int low, int high)
{
    int pivotIndex = inputVector[high];
    int index = low - 1;

    for (int j = index; j <= pivotIndex; j++)
    {
        if (inputVector[j] <= pivotIndex)
        {
            index += 1;
            inputVector[index], inputVector[j] = inputVector[j] , inputVector[index];
        }
    }

    inputVector[index+1], inputVector[high] = inputVector[high], inputVector[index+1];
    return index+1;
}