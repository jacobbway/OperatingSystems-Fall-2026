#include <iostream>
#include <future>
#include <vector>
#include <random>
#include <ranges>
#include <thread>
#include <algorithm>
#include <chrono>
#include <iomanip>

//  g++ -std=c++20 -O2 -pthread MultiThread.cpp -o MultiThread

// i wrote this as starting a thread for each row of Matrix A but google 
// said starting 10k threads for example is bad, so made compute rows to chunk
// out the matrix to avoid that overhead issue

void FillVector(std::vector<std::vector<unsigned long long>>& FillMe, unsigned long long MaxNum);
std::pair<unsigned long long,unsigned long long> GetVectorSize();
std::vector<std::vector<unsigned long long>> MatProd(std::vector<std::vector<unsigned long long>>& MatA, std::vector<std::vector<unsigned long long>>& MatB);
unsigned long long GetDotProduct(std::vector<unsigned long long>& MatARow, std::vector<unsigned long long>& MatBCol);
std::vector<std::vector<unsigned long long>> TransposeMatB(std::vector<std::vector<unsigned long long>>& TransMe);
std::vector<unsigned long long> GetRowOfAB(std::vector<unsigned long long>& MatARow, std::vector<std::vector<unsigned long long>>& MatB);
void PrintVector(std::vector<std::vector<unsigned long long>>& MatAB);
void ComputeRows(std::size_t start, std::size_t end,
    std::vector<std::vector<unsigned long long>>& MatA,
    std::vector<std::vector<unsigned long long>>& MatB,
    std::vector<std::vector<unsigned long long>>& MatAB);

bool SingleThread = false;

int main()
{
    std::pair<unsigned long long, unsigned long long> MatADim, MatBDim;
    unsigned long long MaxNum;

    std::string Choice = "";

    std::cout << "Do you want to be sequential of multithread? (s = sequential m = multithread)\n";
    std::cin >> Choice;

    if(Choice == "s")
        SingleThread = true;

    while(true)
    {
        unsigned long long BCols;
        std::cout << "Build Matrix A\n";
        MatADim = GetVectorSize();
        std::cout << "Enter # of columns for matrix B!\n";
        std::cin >> BCols;
        MatBDim = std::pair<unsigned long long, unsigned long long>(MatADim.second, BCols);

        if(MatADim.second != MatBDim.first)
        {
            std::cout << "Matrix A Columns and Matrix B Rows must be equal!\n";
            MatADim = std::pair<unsigned long long, unsigned long long>(0,0);
            MatBDim = std::pair<unsigned long long, unsigned long long>(0,0);
            continue;
        }

        std::cout << "Matrix A Dimensions: " << MatADim.first << " by " << MatADim.second << std::endl;
        std::cout << "Matrix B Dimensions: " << MatBDim.first << " by " << MatBDim.second<< std::endl;
        
        std::cout << "Enter MaxNumber to fill Vectors with: \n";
        std::cin >> MaxNum;
        break;
    }

    std::vector<std::vector<unsigned long long>> MatA(MatADim.first, std::vector<unsigned long long>(MatADim.second));
    std::vector<std::vector<unsigned long long>> MatB(MatBDim.first, std::vector<unsigned long long>(MatBDim.second));
    std::vector<std::vector<unsigned long long>> MatAB(MatADim.first, std::vector<unsigned long long>(MatBDim.second));

    FillVector(MatA, MaxNum); FillVector(MatB, MaxNum);
    MatB = TransposeMatB(MatB);

    auto start = std::chrono::steady_clock::now();

    MatAB = MatProd(MatA, MatB);
    
    auto end = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Execution time: " << duration.count() << " milliseconds\n";

    // PrintVector(MatAB);

    return 0;
}

void FillVector(std::vector<std::vector<unsigned long long>>& FillMe, unsigned long long MaxNum)
{
    std::random_device rand;
    std::mt19937 gen(rand());

    std::uniform_int_distribution<unsigned long long> dist(0, MaxNum); // range

    for(int x = 0; x < FillMe.size(); x++)
    {
        for(int y = 0; y < FillMe[x].size(); y++)
        {
            FillMe[x][y] = dist(gen);
        }
    }
}

std::pair<unsigned long long,unsigned long long> GetVectorSize()
{
    unsigned long long NumCols, NumRows;

    std::cout << "Input Number of Cols: \n";
    std::cin >> NumCols;
    std::cout << "Input Number of Rows: \n";
    std::cin >> NumRows;

    return std::pair<unsigned long long, unsigned long long>
        (NumRows, NumCols);
}

std::vector<std::vector<unsigned long long>> MatProd(std::vector<std::vector<unsigned long long>>& MatA,
    std::vector<std::vector<unsigned long long>>& MatB)
{
    // MatB is already transposed, so MatB.size() is the column count of the original B
    std::vector<std::vector<unsigned long long>> MatAB(MatA.size(), std::vector<unsigned long long>(MatB.size()));

    if(SingleThread)
    {
        ComputeRows(0, MatA.size(), MatA, MatB, MatAB); 
        return MatAB;
    }

    // One thread per core, but never more threads than rows
    std::size_t numThreads = std::max(1u, std::thread::hardware_concurrency());
    numThreads = std::min(numThreads, MatA.size());
    if(numThreads == 0)
        return MatAB;

    // Each thread gets a contiguous block of rows; the leftover rows go to the first few threads
    std::size_t chunk = MatA.size() / numThreads;
    std::size_t extra = MatA.size() % numThreads;
    std::size_t start = 0;

    std::vector<std::thread> threads;
    threads.reserve(numThreads);

    for(std::size_t t = 0; t < numThreads; t++)
    {
        std::size_t end = start + chunk + (t < extra ? 1 : 0);
        threads.emplace_back(ComputeRows, start, end, std::ref(MatA), std::ref(MatB), std::ref(MatAB));
        start = end;
    }

    for(auto& th : threads)
        th.join();

    return MatAB;
}

/// @brief computes rows [start, end) of AB. Each thread writes only its own rows, so no lock is needed
void ComputeRows(std::size_t start, std::size_t end,
    std::vector<std::vector<unsigned long long>>& MatA,
    std::vector<std::vector<unsigned long long>>& MatB,
    std::vector<std::vector<unsigned long long>>& MatAB)
{
    for(std::size_t i = start; i < end; i++)
        MatAB[i] = GetRowOfAB(MatA[i], MatB);
}

/// @brief turns the cols of mat b into rows so its easier to work with
/// @param TransMe 
/// @return transposed MatrixB
std::vector<std::vector<unsigned long long>> TransposeMatB(std::vector<std::vector<unsigned long long>>& TransMe)
{
    std::size_t rows = TransMe.size();
    std::size_t cols = TransMe[0].size();

    std::vector<std::vector<unsigned long long>> NewMatB(cols, std::vector<unsigned long long>(rows));

    for(std::size_t i = 0; i < rows; ++i)
    {
        for (std::size_t j = 0; j < cols; ++j)
        {
            NewMatB[j][i] = TransMe[i][j];
        }
    }

    return NewMatB;
}

unsigned long long GetDotProduct(std::vector<unsigned long long>& MatARow, std::vector<unsigned long long>& MatBCol)
{
    unsigned long long DotProduct = 0;

    if(MatARow.size() != MatBCol.size())
        return 0;
    
    for(int i = 0; i < MatARow.size(); i++)
    {
        DotProduct += MatARow[i] * MatBCol[i];
    }

    return DotProduct;
}

std::vector<unsigned long long> GetRowOfAB(std::vector<unsigned long long>& MatARow, std::vector<std::vector<unsigned long long>>& MatB)
{
    std::vector<unsigned long long> ABRow(MatB.size());
    for(int i = 0; i < MatB.size(); i++)
    {
        ABRow[i] = GetDotProduct(MatARow, MatB[i]);
    }

    return ABRow;
}

/// @brief prints the top-left corner of the matrix (up to the first 10 values of the first 10 rows)
void PrintVector(std::vector<std::vector<unsigned long long>>& MatAB)
{
    std::size_t numRows = std::min<std::size_t>(10, MatAB.size());

    for(std::size_t i = 0; i < numRows; i++)
    {
        std::size_t numCols = std::min<std::size_t>(10, MatAB[i].size());

        std::cout << "Row: " << i << " [";
        for(std::size_t j = 0; j < numCols; j++)
        {
            if(j > 0)
                std::cout << ", ";
            std::cout << MatAB[i][j];
        }
        std::cout << "]\n";
    }
}