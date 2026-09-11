#ifndef CustomFunctions
#define CustomFunctions

std::vector<int>* CreateFilledVector(int minNumber, int maxNumber, int numElementsInVector);
int QuickSortHelper(std::vector<int> *inputVector, int low, int high);
void QuickSort(std::vector<int> *inputVector, int low = 0, int high = 0);
void CountSort(std::vector<int> *inputVector);

#endif