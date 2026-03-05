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
	//Student* parray[6];
	printf("sizeof(array)=%d\n", sizeof(array));
	printf("array=%p\n", array);
	printf("&array=%p\n", &array);

	printf("array+1=%p\n", array+1);
	printf("&array+1=%p\n", &array+1);

	//1.ptr to a Student
	//2.array of elements of type Student
	//Student* array; // Student array[6];
	Student** parray = NULL; // Student* parray[6];
	int size = 0;
	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		char* delimiter = ",";
		//char delimiter[] = {',','\0'};
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;
		short index = 0;
		while (fgets(line, LINE_BUFFER, fp))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);
			
			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);

			token = strtok_s(NULL, delimiter, &context);

			Student* stud = createStudent(regNo, groupNo, token);
			//array[index++] = *stud;
			//parray[index++] = stud;
			//array[index].groupNo = groupNo;
			//array[index].regNo = regNo;
			//array[index].name
			//array[1] = *stud;
			//*(array + 1) = *stud;
			//(array + 1)[0] = *stud;

		
			//1. array allocation
			Student** tmp = parray;
			parray = (Student**)malloc(sizeof(Student*) * (++size));
			if (size - 1 > 0)
			{
				//copy the old ones into the new location
				for (register int i = 0; i < size - 1; i++)
					parray[i] = tmp[i];
				free(tmp);
			}
			//copy the new student
			parray[size - 1] = stud;

			printStudent(parray[size - 1]);
			deleteStudent(stud);
		}
	}
}