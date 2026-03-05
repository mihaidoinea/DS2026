//#define _CRT_SECURE_NO_WARNINGS
//S03
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name; 
} Student, *PStudent;
//typedef struct Student Student;
#define LINE_BUFFER 256

Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);

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
void deleteStudent(Student* pStud)
{
	if (pStud != NULL)
	{
		if (pStud->name != NULL)
			free(pStud->name);
		free(pStud);
	}
}
void printStudent(Student* pStud)
{
	if(pStud != NULL)
		printf("RegNo=%d, GroupNo=%d, Name=%s", 
			pStud->regNo, 
			pStud->groupNo, 
			pStud->name);
}

Student* createStudent(unsigned int regNo, 
	short int groupNo, 
	const char* name)
{
	Student* pStud = (Student*)malloc(sizeof(Student));
	if (pStud != NULL)
	{
		pStud->regNo = regNo;
		pStud->groupNo = groupNo;
		pStud->name = (char*)malloc(strlen(name) + 1);
		if (pStud->name != NULL)
		{
			strcpy_s(pStud->name, strlen(name) + 1, name);
		}
		else
		{
			free(pStud);
			pStud = NULL;
		}
	}
	return pStud;
}