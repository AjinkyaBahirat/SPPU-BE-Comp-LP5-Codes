#include<stdio.h>
#include<omp.h>
#include<stdlib.h>

int main(){
    int size = 10000;
    int arr[size];
    for(int i=0;i<size;i++){
        arr[i] = rand() % 10000;
    }
    int minval = arr[0];
    int maxval = arr[0];
    int sum = 0;
    #pragma omp parallel for reduction(min:minval) reduction(max:maxval) reduction(+:sum)
    for(int j = 0;j<size;j++){
        if(arr[j]<minval){
            minval = arr[j];
        }
        else if(arr[j]>maxval){
            maxval = arr[j];
        }
        sum += arr[j];
    } 
    double avg = (double) sum/size;
    printf("Min Value: %d \n",minval);
    printf("Max Value: %d \n",maxval);
    printf("Sum Value: %d \n",sum);
    printf("Average Value: %.2f \n",avg); 
    return 0;
}