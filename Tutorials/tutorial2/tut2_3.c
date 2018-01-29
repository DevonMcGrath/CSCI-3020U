#include <stdlib.h>
#include <stdio.h>
int main(void){
    char hello_world[20]= "hello world";
    int i=0;
    while(1){
        printf("%c",hello_world[i]);
        i++;      
        
        if(hello_world[i]=='\0'){
            printf("\n");
            break;
        }
    }
    
}