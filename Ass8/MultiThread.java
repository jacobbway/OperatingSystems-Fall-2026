import java.util.Scanner;
import java.util.concurrent.ThreadLocalRandom;

//  javac MultiThread.java
//  java MultiThread


public class MultiThread
{
    public static boolean SingleThread = false;
    public static void main(String[] args) throws InterruptedException
    {
        Scanner in = new Scanner(System.in);
        long[] MatADim, MatBDim;   // {rows, cols}
        long MaxNum;
        String Choice = "";

        System.out.println("Single or multithread? (s = single m = multi");
        Choice = in.nextLine();
        if(Choice.equals("s"))
            SingleThread = true;

        System.out.println(SingleThread);

        while(true)
        {
            System.out.println("Build Matrix A");
            MatADim = GetVectorSize(in);
            MatBDim = MatADim;

            System.out.println("Matrix A Dimensions: " + MatADim[0] + " by " + MatADim[1]);
            System.out.println("Matrix B Dimensions: " + MatBDim[0] + " by " + MatBDim[1]);

            System.out.println("Enter MaxNumber to fill Vectors with: ");
            MaxNum = in.nextLong();
            break;
        }

        long[][] MatA = new long[(int) MatADim[0]][(int) MatADim[1]];
        long[][] MatB = new long[(int) MatBDim[0]][(int) MatBDim[1]];

        for(int i = 1; i < 11; i++)
        {
            System.out.println("---------------------");
            System.out.printf("\nResults #: %d", i);
            FillVector(MatA, MaxNum); FillVector(MatB, MaxNum);
            MatB = TransposeMatB(MatB);
    
            long start = System.nanoTime();
    
            long[][] MatAB = MatProd(MatA, MatB);
    
            long end = System.nanoTime();
            long duration = (end - start) / 1_000;
    
            System.out.println("\nExecution time: " + duration + " microseconds");
        }

        //PrintVector(MatAB);
    }

    static void FillVector(long[][] FillMe, long MaxNum)
    {
        ThreadLocalRandom rand = ThreadLocalRandom.current();

        for(int x = 0; x < FillMe.length; x++)
        {
            for(int y = 0; y < FillMe[x].length; y++)
            {
                FillMe[x][y] = rand.nextLong(0, MaxNum + 1); // range [0, MaxNum]
            }
        }
    }

    /// returns {rows, cols}
    static long[] GetVectorSize(Scanner in)
    {
        System.out.println("Input Dimensions: ");
        long NumCols = in.nextLong();

        return new long[] { NumCols, NumCols };
    }

    static long[][] MatProd(long[][] MatA, long[][] MatB) throws InterruptedException
    {
        long[][] MatAB = new long[MatA.length][];

        if(SingleThread)
        {
            ComputeRows(0, MatA.length, MatA, MatB, MatAB);
            return MatAB;
        }

        int numThreads = Math.max(1, Runtime.getRuntime().availableProcessors());
        numThreads = Math.min(numThreads, MatA.length);
        if(numThreads == 0)
            return MatAB;

        // Each thread gets a contiguous block of rows; the leftover rows go to the first few threads
        int chunk = MatA.length / numThreads;
        int extra = MatA.length % numThreads;
        int start = 0;

        Thread[] threads = new Thread[numThreads];

        for(int t = 0; t < numThreads; t++)
        {
            int end = start + chunk + (t < extra ? 1 : 0);
            final int s = start, e = end;   // lambdas need effectively final copies
            threads[t] = new Thread(() -> ComputeRows(s, e, MatA, MatB, MatAB));
            threads[t].start();
            start = end;
        }

        for(Thread th : threads)
            th.join();

        return MatAB;
    }

    /// computes rows [start, end) of AB. Each thread writes only its own rows, so no lock is needed
    static void ComputeRows(int start, int end, long[][] MatA, long[][] MatB, long[][] MatAB)
    {
        for(int i = start; i < end; i++)
            MatAB[i] = GetRowOfAB(MatA[i], MatB);
    }

    /// turns the cols of mat b into rows so its easier to work with
    static long[][] TransposeMatB(long[][] TransMe)
    {
        int rows = TransMe.length;
        int cols = TransMe[0].length;

        long[][] NewMatB = new long[cols][rows];

        for(int i = 0; i < rows; ++i)
        {
            for(int j = 0; j < cols; ++j)
            {
                NewMatB[j][i] = TransMe[i][j];
            }
        }

        return NewMatB;
    }

    static long GetDotProduct(long[] MatARow, long[] MatBCol)
    {
        long DotProduct = 0;

        if(MatARow.length != MatBCol.length)
            return 0;

        for(int i = 0; i < MatARow.length; i++)
        {
            DotProduct += MatARow[i] * MatBCol[i];
        }

        return DotProduct;
    }

    static long[] GetRowOfAB(long[] MatARow, long[][] MatB)
    {
        long[] ABRow = new long[MatB.length];
        for(int i = 0; i < MatB.length; i++)
        {
            ABRow[i] = GetDotProduct(MatARow, MatB[i]);
        }

        return ABRow;
    }

    /// prints the top-left corner of the matrix (up to the first 10 values of the first 10 rows)
    static void PrintVector(long[][] MatAB)
    {
        int numRows = Math.min(10, MatAB.length);

        for(int i = 0; i < numRows; i++)
        {
            int numCols = Math.min(10, MatAB[i].length);

            StringBuilder sb = new StringBuilder("Row: " + i + " [");
            for(int j = 0; j < numCols; j++)
            {
                if(j > 0)
                    sb.append(", ");
                // print as unsigned so overflow wraps the same way as the C++ unsigned long long
                sb.append(Long.toUnsignedString(MatAB[i][j]));
            }
            sb.append("]");
            System.out.println(sb);
        }
    }
}
