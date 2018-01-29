#include <stdlib.h>
#include <stdio.h>
int main(void){
    double arr[]={1.2, 5.5, 2.1, 3.3, 3.3};
    int array_size = sizeof(arr) / sizeof(double);

    for (int i=1;i<array_size;i++){
        if (arr[i]>arr[i-1]){
            printf("greater than\n");
        }else if (arr[i] == arr[i-1]){
            printf("the same\n");

        }else{
            printf("less than\n");
        }
    }
}