#include <stdlib.h>
#include <stdio.h>

struct student{
	char id[9];
	int age;
	char year_start[4];
};

void save_student(struct student input){
	FILE* fp = fopen ("student.txt","a");
	fprintf(fp, "%s,%i,%s",input.id, input.age, input.year_start);
	fclose(fp);
}

int main(void){
struct student in;
printf("Enter id: ");
scanf("%s",in.id);
printf("Enter age: ");
scanf("%d",&in.age);
printf("Enter year started at UOIT: ");
scanf("%s",in.year_start);
save_student(in);
}