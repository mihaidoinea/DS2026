#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#pragma pack(1)
typedef struct Student
{
	unsigned int regNo;
	unsigned short groupNo;
	char* name;
} Student, *PStudent;
//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256
int main()
{
	Student stud = { .regNo = 13000,.groupNo = 1069,.name = "Popescu Ioan" };
	printf("sizeof(Student)=%d\n", sizeof(Student));

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		char* delimiter = ",";
		char delimiter[] = { ',','\0' };
		char line[LINE_SIZE];
		char* token = NULL, *context = NULL;
		unsigned int regNo; 
		unsigned short groupNo;
		while (fgets(line, LINE_SIZE, pFile))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);
			printf("Remaining string: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);
			printf("Remaining string: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			Student* stud = createStudent(regNo, groupNo, token);

		}
	}
	return 0;
}

PStudent createStudent(unsigned int reg, unsigned short group,
	const char* name)
{
	Student* stud = (Student*)malloc(sizeof(Student));
	if (stud != NULL)
	{
		stud->groupNo = group;
		stud->regNo = reg;
		stud->name = (char*)malloc(strlen(name)+1);
		if (stud->name != NULL)
		{
			strcpy_s(stud->name, strlen(name) + 1, name);
		}
		else
		{
			free(stud);
			stud = NULL;
		}
	}
	return stud;
}
void deleteStudent(Student* stud)
{
	if (stud != NULL)
	{
		if (stud->name != NULL)
		{
			free(stud->name);
		}
		free(stud);
	}
}

