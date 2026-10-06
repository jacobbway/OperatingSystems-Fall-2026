#ifndef CustomFunctions
#define CustomFunctions

#include <unordered_set>

std::vector<int>* CreateFilledVector(int minNumber, int maxNumber, int numElementsInVector);
int QuickSortHelper(std::vector<int> *inputVector, int low, int high);
void QuickSort(std::vector<int> *inputVector, int low = 0, int high = 0);
void CountSort(std::vector<int> *inputVector);
std::string BuildStringAss2(std::vector<char> symbolsToFind, char matchedSymbol, int symbolPos, bool anyMatch, int cmdNmb);
std::vector<std::string> FindSymbolInString(std::vector<std::string> inputVectorOfStrings, std::vector<char> symbolsToFind);

#endif