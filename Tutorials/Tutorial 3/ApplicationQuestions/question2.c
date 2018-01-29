#include <stdlib.h>
#include <stdio.h>

/*
2. Create a program that does the following
- Reads the ten integers from the included file question2.txt
- Stores each integer read from the file in an array
- Prints the contents of the array to the terminal
- You will need to review the fopen and fscanf documentation
*/

int main(void)
{
	int int_array[10]  ;
	FILE* fp = fopen("question2.txt","r");
	    //read file into array
    int i;

    for (i = 0; i < 10; i++)
    {
        fscanf(fp, "%1d", &int_array[i]);
    }

    for (i = 0; i < 10; i++)
    {
        printf("Number is: %d\n\n", int_array[i]);
    }
}