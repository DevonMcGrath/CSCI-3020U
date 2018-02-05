
#include <stdlib.h>
#include <stdio.h>


int main(void){
	char* professor;
	int* student_ids;
	int* grades;
	int student_count;
	professor = calloc(256,sizeof(char));
	printf("Please enter your name: ");
	scanf("%s",professor);
	printf("Please enter number of students to mark: ");
	scanf("%i",&student_count);
	student_ids =  malloc(student_count*sizeof(int));
	grades =  malloc(student_count*sizeof(int));
	free(professor);
	free(student_ids);
	free(grades);
}