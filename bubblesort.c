#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

int main()
{
    int n = 1000;
    //printf("Enter Size:");
    //scanf("%d", &n);
    int arr[n];
    //printf("Enter Array:");
    for (int i = 0; i < n; i++)
    {
        //scanf("%d", &arr[i]);
        arr[i] = rand() % 1000;
    }
    int i, j;
    int first;
    double start=0, end=0;
    start = omp_get_wtime();
    //omp_set_num_threads(6);
    for (i = 0; i < n - 1; i++)
    {
        first = i % 2;
        #pragma omp parallel for default(none),shared(arr, n, first)
        for (j = first; j < n - 1; j+=1) 
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    end = omp_get_wtime();
    printf("Start Time:%f \n", start);
    printf("End Time:%f\n", end);
    printf("Time:%.2f\n", end - start);
    printf("After Sorting:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
}