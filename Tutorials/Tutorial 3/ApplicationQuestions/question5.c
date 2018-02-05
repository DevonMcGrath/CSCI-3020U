/*

- Create two pointers, a character pointer professor, and a pointer for the
grade struct you created and call it grades, it will hold an array of grade
structures.-
-

Using dynamic memory, use calloc to allocate 256 characters for the
professor pointer.
Prompts the professor for their name, and the number of students to
mark.
Store the professor’s name using the professor pointer and in an integer
num_students the number of students to mark.
Using dynamic memory, use malloc to allocate memory for the grades
pointer to hold the number of students the professor needs to mark.
For each student to mark (num_students) prompt the professor for the
student id and the mark and store it in the grade struct in grades (you can
use grades just like an array).
After getting all of the student ids and marks from the professor call the
grade_students function to grade the students, calculate grade statistics,
and store all the results to grades.txt
Don’t forget to free all of your dynamic memory
*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct grade{
  int student_id;
  int mark;

};

void grade_students (struct grade *grade, int num_students){
  FILE* fp= fopen("grades.txt","w");
  int sum =0;
  for (int i=0;i<num_students;i++){
    sum+= grade[i].mark;
    char out[50];
    sprintf(out,"%i,%i \n",grade[i].student_id, grade[i].mark);
    fputs(out,fp);
  }
  float mean = sum/num_students;
  float meanSum = 0;
  for (int i=0;i<num_students;i++){
    meanSum+= pow(grade[i].mark - mean,2);
  }
  float std = sqrtf(meanSum/num_students);
  char bottom[50];
  sprintf(bottom,"%f,%f \n",mean, std);
  fputs(bottom,fp);

  fclose(fp); 
}

int main(void){
	int student_count;
	char* professor;
	int* student_ids;
	struct grade* grades;
	professor = calloc(256,sizeof(char));

	printf("Please enter your name: ");
	scanf("%s",professor);
	printf("Please enter number of students to mark: ");
	scanf("%i",&student_count);
	student_ids =  malloc(student_count*sizeof(int));
	grades =  malloc(student_count*sizeof(int));
	
	for (int i=0;i<	student_count;i++){
		printf("Please enter student id: ");
		scanf("%i",&grades[i].student_id);
		printf("Please enter mark: ");
		scanf("%i",&grades[i].mark);
	}
	grade_students(grades,student_count);

	free(student_ids);
	free(professor);
	free(grades);
        
}