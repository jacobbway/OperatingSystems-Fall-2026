#ifndef CustomFunctions
#define CustomFunctions

std::vector<int> CreateFilledVector(int minNumber, int maxNumber, int numElementsInVector);
_PSTL_PRAGMA_VECTOR_UNALIGNED QuickSort(std::vector<int> &inputVector, int low = 0, int high = -1);
int QuickSortHelper(std::vector<int> &inputVector, int low, int high);

#endif