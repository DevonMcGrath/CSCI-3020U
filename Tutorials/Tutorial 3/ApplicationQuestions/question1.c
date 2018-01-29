#include <stdlib.h>
#include <stdio.h>
/*
-Prompts the user for their first name, age, and height (hint use a
	character array for strings).
- Prints back to the console, their first name, age, and height
- You will need to review the scanf documentation to complete this
*/

int main(void)
{
char fname[100];
char age[10];
char height[100];
printf("Enter first name: ");
scanf("%s",fname);
printf("Enter age name: ");
scanf("%s",age);
printf("Enter height name: ");
scanf("%s",height);

printf ("Name: %s, Age: %s, Height: %s \n",fname,age,height);

return 0;
}