#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#pragma pack(1)

typedef struct Student
{
	unsigned int regNo;
	unsigned short group;
	char* name;
} Student, *PStudent;
//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256

PStudent createStudent(unsigned int, unsigned short,const char*);
void printStudent(Student* pStud);

int main()
{
	Student stud = {12000, 17, "Popescu Ioan"};
	printf("sizeof(Student) = %d\n", sizeof(Student));
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		char line[LINE_SIZE];
		//char* delimiter = ",";
		char delimiter[] = { ',','\0' };
		char* token = NULL;
		char* context = NULL;
		unsigned int regNo;
		unsigned short groupNo;
		while (fgets(line, LINE_SIZE, pFile))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);
			//printf("Remaining line: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);
			//printf("Remaining line: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			//printf("Remaining line: %s\n", context);
			Student* pStud = createStudent(regNo, groupNo, token);
			printStudent(pStud);
		}
	}
	
	return 0;
}

void printStudent(Student* pStud)
{
	if (pStud != NULL)
	{
		printf("Name: %s, regNo: %d, groupNo: %d\n",
			pStud->name,
			pStud->regNo,
			pStud->group);
	}
}

PStudent createStudent(unsigned int regNo, 
	unsigned short groupNo, 
	const char* name)
{
	Student* stud = (Student*)malloc(sizeof(Student));
	if (stud != NULL)
	{
		stud->regNo = regNo;
		stud->group = groupNo;
		stud->name = (char*)malloc(strlen(name)+1);
		if (stud->name != NULL)
		{
			strcpy_s(stud->name, strlen(name)+1, name);
		}
		else
		{
			free(stud);
			stud = NULL;
		}
	}
	return stud;
}