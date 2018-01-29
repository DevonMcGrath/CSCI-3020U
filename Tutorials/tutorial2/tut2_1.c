#include <stdlib.h>
#include <stdio.h>
int main(void){
    int int_array[10];
    for (int i=1;i<=10;i++){
        int_array[i-1]=i;
         printf("%d\n",int_array[i-1]);

    }
}