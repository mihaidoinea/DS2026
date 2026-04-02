#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#pragma pack(1)

typedef struct Student
{
	unsigned int regNo;
	unsigned short group;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;
//typedef struct Student* PStudent;
typedef struct QueueNode
{
	Student* info;
	struct QueueNode* next;
}Queue, QueueNode;

#define LINE_SIZE 256

PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*);

//void put(Queue**, Student*);
Queue* put(Queue* queueTail, Student* stud)
{
	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode->info = stud;
	newNode->next = NULL;
	if (queueTail == NULL)
	{
		newNode->next = newNode;
		return newNode;
	}
	else
	{
		newNode->next = queueTail->next;
		queueTail->next = newNode;
		return newNode;
	}
}
Student* get(Queue** queueTail)
{
	Student* value = NULL;
	if (*queueTail != NULL)
	{
		value = (*queueTail)->next->info;
		QueueNode* tmp = (*queueTail)->next;
		(*queueTail)->next = tmp->next;
		free(tmp);
	}
	return value;
}

int main()
{
	Queue* queueTail = NULL;
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		char line[LINE_SIZE];
		//char* delimiter = ",";
		char delimiter[] = { ',','\n','\0' };
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

		}
	}

	return 0;
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