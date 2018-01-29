#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

double euclid_dist (int x1, int y1, int x2, int y2){ 
    double x =(double) x2-x1;   
    double y= (double) y2-y1;
    return sqrt(pow(x,2) + pow(y,2));
    
}


int main(void){
    srand(time(NULL));

    for (int i=0;i<10;i++){
        int x1 = rand() % 101;  
        int y1 = rand() % 101;  
        int x2 = rand() % 101;  
        int y2 = rand() % 101;  
        double dist = euclid_dist(x1,y1,x2,y2);
        printf("x1: %d y1: %d x2: %d y2: %d distance: %f\n",x1,y2,x2,y2,dist);
        

    }
}