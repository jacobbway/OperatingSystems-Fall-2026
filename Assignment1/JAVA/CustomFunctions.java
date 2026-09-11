package Assignment1.JAVA;

import java.util.Arrays;

public class CustomFunctions {
    
    public CustomFunctions(){};

    public static void QuickSort(int inputArray[], int l, int h)
    {
        // Create an auxiliary stack
        int[] stack = new int[h - l + 1];

        // initialize top of stack
        int top = -1;

        // push initial values of l and h to stack
        stack[++top] = l;
        stack[++top] = h;

        // Keep popping from stack while is not empty
        while (top >= 0)
        {
            h = stack[top--];
            l = stack[top--];

            int p = partition(inputArray, l, h);

            if (p - 1 > l)
            {
                stack[++top] = l;
                stack[++top] = p - 1;
            }

            if (p + 1 < h)
            {
                stack[++top] = p + 1;
                stack[++top] = h;
            }
        }
    }

    static int partition(int inputArray[], int low, int high)
    {
        int pivot = inputArray[high];

        int i = (low - 1);
        for (int j = low; j <= high - 1; j++)
        {
            if (inputArray[j] <= pivot)
            {
                i++;
                int temp = inputArray[i];

                inputArray[i] = inputArray[j];
                inputArray[j] = temp;
            }
        }

        int temp = inputArray[i + 1];
        inputArray[i + 1] = inputArray[high];
        inputArray[high] = temp;

        return i + 1;
    }

    static void swap(int[] inputArray, int i, int j)
    {
        int temp = inputArray[i];
        inputArray[i] = inputArray[j];
        inputArray[j] = temp;
    }

    public static void CountSort(int[] inputArray)
    {
        int maxValue = -1;

        for(int curValue : inputArray)
        {
            if (curValue > maxValue) maxValue = curValue;
        }

        int[] countArray = new int[maxValue + 1];
        Arrays.fill(countArray, 0);

        for(int curValue : inputArray)
        {
            countArray[curValue]++;
        }

        int currentPos = 0;
        for(int i = 0; i < countArray.length; i++)
        {
            for(int j = 0; j < countArray[i]; j++)
            {
                inputArray[currentPos] = i;
                currentPos++;
            }
        }
    }
}
