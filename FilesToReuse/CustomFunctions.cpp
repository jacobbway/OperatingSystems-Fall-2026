#include <vector>
#include <random>
#include <regex>
#include <unordered_set>
#include <iostream>#include <sstream>


/// @brief Creates a vector filled with range of numbers of a size
/// @param minNumber lowest number of range
/// @param maxNumber highest number of range
/// @param numElementsInVector # of elements in vector
/// @return a vector filled with psuedo random numbers from a range
std::vector<int>* CreateFilledVector(int minNumber, int maxNumber, int numElementsInVector)
{
    std::random_device randomDevice;
    std::mt19937 gen(randomDevice());
    std::uniform_int_distribution<int> distr(minNumber, maxNumber);
    
    std::vector<int> *filledVector = new std::vector<int>(numElementsInVector);

    for(int i = 0; i < numElementsInVector; i++)
    {
        (*filledVector)[i] = distr(gen);
    }

    return filledVector;
}

/// @brief Helper for quick sort
/// @param inputVector 
/// @param low 
/// @param high 
/// @return an index to use as a pivot
int QuickSortHelper(std::vector<int> *inputVector, int low, int high)
{
    int pivotValue = (*inputVector)[high];
    int index = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        if ((*inputVector)[j] <= pivotValue)
        {
            index++;
            std::swap((*inputVector)[index], (*inputVector)[j]);
        }
    }

    std::swap((*inputVector)[index +1], (*inputVector)[high]);
    return index+1;
}

/// @brief uses quick sort to sort a vector of ints
/// @param inputVector the vector to sort
/// @param low 
/// @param high 
void QuickSort(std::vector<int> *inputVector, int low = 0, int high = 0)
{
    std::vector<int> stack(high - low + 1);
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) 
    {
        high = stack[top--];
        low = stack[top--];

        int pivot = QuickSortHelper(inputVector, low, high);

        if (pivot - 1 > low)
        {
            stack[++top] = low;
            stack[++top] = pivot - 1;
        }

        if (pivot + 1 < high)
        {
            stack[++top] = pivot + 1;
            stack[++top] = high;
        }
    }
}

/// @brief performs counting sort on a vector of ints
/// @param inputVector 
void CountSort(std::vector<int> *inputVector)
{
    if ((*inputVector).empty()) return;

    int sizeOfVector = (*inputVector).size();
    int maxValueInVector = -1;

    for(int i = 0; i < sizeOfVector; i++)
    {
        if ((*inputVector)[i] > maxValueInVector) maxValueInVector = (*inputVector)[i];
    }

    std::vector<int> countingVector(maxValueInVector + 1, 0);

    for(int i = 0; i < sizeOfVector; i++)
    {
        countingVector[(*inputVector)[i]]++;
    }

    (*inputVector).clear();

    for(int i = 0; i < countingVector.size(); i++)
    {
        for(int j = 0; j < countingVector[i]; j++)
        {
            (*inputVector).emplace_back(i);
        }
    }
}

std::string BuildStringAss2(std::vector<char> symbolsToFind, char matchedSymbol, int symbolPos, bool anyMatch, int cmdNmb)
{
    std::string addString = "Command ";
    addString += std::to_string(cmdNmb);
    addString += ": ";
    
    for(char c : symbolsToFind)
    {
        if (c == matchedSymbol) 
        {
            addString +=  c;
            addString += " found at position ";
            addString += std::to_string(symbolPos);
        } 
        else 
        {
            addString += "No ";
            addString += c;
        }
        addString += ", ";
    }

    addString.erase(addString.length() - 2);

    return addString;
}

std::vector<std::string> FindSymbolInString(std::vector<std::string> inputVectorOfStrings, std::vector<char> symbolsToFind)
{
    std::vector<std::string> outputVector;
    outputVector.reserve(inputVectorOfStrings.size());
    std::string RegexString = "[";

    for(char c : symbolsToFind)
    {
        RegexString += c;
    }

    RegexString += "]";

    std::regex RegexMatcher(RegexString);
    std::smatch match;

    int cmdNmbr = 0;

    for(std::string curLine : inputVectorOfStrings)
    {
        if(std::regex_search(curLine, match, RegexMatcher) == true)
        {
            outputVector.push_back(BuildStringAss2(symbolsToFind, match.str(0)[0], match.position(), true, cmdNmbr));
        }
        else 
        {
            outputVector.push_back(BuildStringAss2(symbolsToFind, '\0', -1, false, cmdNmbr));
        }
        ++cmdNmbr;
    }

    return outputVector;
}

std::vector<std::string> TokenizeString(std::string InputString)
{
    std::vector<std::string> TempVector;
    std::stringstream StreamObject = std::stringstream(InputString);
    std::string CurToken;
    while(StreamObject >> CurToken)
        TempVector.push_back(CurToken);
    return TempVector;
}