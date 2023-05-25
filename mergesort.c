#include <stdio.h>
#include <omp.h>

void merge(int arr[], int left[], int leftn, int right[], int rightn)
{
    int i = 0, j = 0, k = 0;
    while (i < leftn && j < rightn)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < leftn)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < rightn)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}
void mergeSort(int arr[], int n)
{

    if (n < 2)
    {
        return;
    }

    int mid = n / 2;
    int left[mid];
    int right[n - mid];

    #pragma omp parallel sections 
    {
        #pragma omp section 
        {
            for (int i = 0; i < mid; i++)
            {
                left[i] = arr[i];
            }
            mergeSort(left, mid);
        }

        #pragma omp section
        {
            for (int j = mid; j < n; j++)
            {
                right[j - mid] = arr[j];
            }
            mergeSort(right, n - mid);
        }

    }
merge(arr, left, mid, right, n - mid);
}

int main()
{
    int arr[] = {5, 2, 6, 1, 9};
    int n = sizeof(arr) / sizeof(arr[0]);
    mergeSort(arr, n);
    printf("After Sort:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}