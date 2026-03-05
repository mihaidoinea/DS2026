//#define _CRT_SECURE_NO_WARNINGS
//S03
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.h"

//typedef struct Student Student;
#define LINE_BUFFER 256

int main()
{
	Student* stud1 = NULL;
	PStudent stud2 = NULL;
	printf("sizeof(Student)=%d\n", sizeof(Student));
	FILE* fp = fopen("Data.txt", "r");
	Student array[6];

	printf("sizeof(array)=%d\n", sizeof(array));
	printf("array=%p\n", array);
	printf("&array=%p\n", &array);

	printf("array+1=%p\n", array+1);
	printf("&array+1=%p\n", &array+1);


	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		char* delimiter = ",";
		//char delimiter[] = {',','\0'};
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;
		while (fgets(line, LINE_BUFFER, fp))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);
			
			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);

			token = strtok_s(NULL, delimiter, &context);

			Student* stud = createStudent(regNo, groupNo, token);
			array[1] = *stud;
			*(array + 1) = *stud;
			(array + 1)[0] = *stud;

			printStudent(stud);
			deleteStudent(stud);
		}
	}
}