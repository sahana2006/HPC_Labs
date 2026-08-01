#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 18250

// Bubble Sort
void bubbleSort(int arr[], int n)
{
    int i, j, temp;

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Partition for Quick Sort
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;
    int temp;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            i++;

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Quick Sort
void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main()
{
    int bubble[SIZE];
    int quick[SIZE];

    srand(time(NULL));

    for (int i = 0; i < SIZE; i++)
    {
        int value = rand() % 1000;

        bubble[i] = value;
        quick[i] = value;
    }

    clock_t start, end;

    start = clock();
    bubbleSort(bubble, SIZE);
    end = clock();

    double bubbleTime =
        ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    quickSort(quick, 0, SIZE - 1);
    end = clock();

    double quickTime =
        ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Bubble Sort Time : %.6f sec\n", bubbleTime);
    printf("Quick Sort Time  : %.6f sec\n", quickTime);

    return 0;
}