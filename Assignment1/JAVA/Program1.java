package Assignment1.JAVA;
import java.util.Random;

public class Program1Part1 {
    public static void main(String[] args)
    {
        int minNumber = 1;
        int maxNumber = 10000;
        int arraySize = 1000000;


        int[] randomArray1 = new Random().ints(arraySize, minNumber, maxNumber).toArray();
        int[] randomArray2 = randomArray1.clone();

        long startQuickTime = System.nanoTime();
        CustomFunctions.QuickSort(randomArray1, 0, arraySize - 1);
        long stopQuickTime = System.nanoTime();
        long durationQuick = (stopQuickTime - startQuickTime) / 1000000;

        long startCountTime = System.nanoTime();
        CustomFunctions.CountSort(randomArray2);
        long stopCountTime = System.nanoTime();
        long durationCount = (stopCountTime - startCountTime) / 1000000;

        System.out.println("===============================================");
        System.out.printf("Number of Elements: %d MinNumber: %d MaxNumber: %d", arraySize, minNumber, maxNumber);
        System.out.printf("\nQuick Sort Duration: %d milliseconds", durationQuick);
        System.out.printf("\nCount Sort Duration: %d milliseconds\n", durationCount);
        System.out.println("===============================================");

        maxNumber = 50;
        
        randomArray1 = new Random().ints(arraySize, minNumber, maxNumber).toArray();
        randomArray2 = randomArray1.clone();

        startQuickTime = System.nanoTime();
        CustomFunctions.QuickSort(randomArray1, 0, arraySize - 1);
        stopQuickTime = System.nanoTime();
        durationQuick = (stopQuickTime - startQuickTime) / 1000000;

        startCountTime = System.nanoTime();
        CustomFunctions.CountSort(randomArray2);
        stopCountTime = System.nanoTime();
        durationCount = (stopCountTime - startCountTime) / 1000000;

        System.out.println("===============================================");
        System.out.printf("Number of Elements: %d MinNumber: %d MaxNumber: %d", arraySize, minNumber, maxNumber);
        System.out.printf("\nQuick Sort Duration: %d milliseconds", durationQuick);
        System.out.printf("\nCount Sort Duration: %d milliseconds\n", durationCount);
        System.out.println("===============================================");
    }
}
