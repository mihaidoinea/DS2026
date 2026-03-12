#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(4)
typedef struct Student
{
	unsigned int regNo;
	unsigned short groupNo;
	char* name;
} Student, *PStudent;
//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256

PStudent createStudent(unsigned int reg, unsigned short group, const char* name);
void deleteStudent(Student* stud);
void printStudent(Student* stud);
void insertIntoArray(Student*** masiv, Student* stud, short* index);
Student** insertIntoArrayReturn(Student** masiv, Student* stud, short* index);
int main()
{

	//1. vector alocat static de elemente de tip Student
	Student masiv1[6];
	//2a. vector alocat dinamic de elemente de tip Student
	//2b. pointer la un element de tip Student
	Student* masiv2 = NULL;
	//3a. vector alocat static de elemente de tip Student*
	//3b. vector alocat static de vector de elemente de tip Student
	Student* masiv3[6];
	//4a.pointer la pointer la un element de tip Student
	//4b.vector alocat dinamic de elemente de tip pointer la Student
	//4c.matrice de elemente de tip Student
	Student** masiv4 = NULL;

	short index = 0;

	Student stud = {.regNo=12300, .groupNo=1055, .name="Popescu Ioan"};
	printf("sizeof(Student)=%d\n", sizeof(Student));

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		char line[LINE_SIZE];
		//char* delimiter = ",";
		char delimiter[] = { ',','\0' };
		char* token = NULL, * context = NULL;
		unsigned int reg;
		unsigned short group;
		char buffer[LINE_SIZE];
		while (fgets(line, LINE_SIZE, pFile))
		{
			token = strtok_s(line, delimiter, &context);
			reg = atoi(token);
			//printf("Remaining string: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			strcpy_s(buffer, strlen(token) + 1, token);

			token = strtok_s(NULL, delimiter, &context);
			group = atoi(token);
			//printf("Remaining string: %s\n", context);

			Student* stud = createStudent(reg, group, buffer);

			//1.
			masiv1[index] = *stud;
			//masiv1[index].groupNo = group;
			//masiv1[index].regNo = reg;
			
			//3.
			masiv3[index] = stud;
			//insertIntoArray(&masiv4, stud, &index);
			masiv4 = insertIntoArrayReturn(masiv4, stud, &index);

			printStudent(masiv4[index-1]);
			deleteStudent(stud);

		}
	}
	return 0;
}
Student** insertIntoArrayReturn(Student** masiv, Student* stud, short* index)
{
	//4.
	Student** tmp = masiv;
	masiv = (Student**)malloc(((*index) + 1) * sizeof(Student*));
	if (masiv != NULL)
	{
		if (*index > 0)
		{
			for (register short i = 0; i < *index; i++)
				masiv[i] = tmp[i];
			free(tmp);
		}
		masiv[*index] = stud;
	}
	(*index)++;
	return masiv;
}
void insertIntoArray(Student*** masiv, Student* stud, short* index)
{
	//4.
	Student** tmp = *masiv;
	*masiv = (Student**)malloc(((*index) + 1) * sizeof(Student*));
	if (*masiv != NULL)
	{
		if (*index > 0)
		{
			for (register short i = 0; i < *index; i++)
				(*masiv)[i] = tmp[i];
			free(tmp);
		}
		(*masiv)[*index] = stud;
	}
	(*index)++;
}

PStudent createStudent(unsigned int reg, unsigned short group, const char* name)
{
	Student* stud = (Student*)malloc(sizeof(Student));
	if (stud != NULL)
	{
		stud->groupNo = group;
		stud->regNo = reg;
		stud->name = (char*)malloc(strlen(name) + 1);
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
			free(stud->name);
		free(stud);
	}
}
void printStudent(Student* stud)
{
	if (stud != NULL && stud->name != NULL)
	{
		printf("RegNo:%d, Name:%s, group:%d\n",
			stud->regNo, stud->name, stud->groupNo);
	}
}