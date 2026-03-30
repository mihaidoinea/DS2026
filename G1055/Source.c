#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(4)
typedef struct Student
{
	unsigned int regNo;
	unsigned short groupNo;
	char* name;
} Student, * PStudent;
typedef struct QueueNode
{
	Student* info;
	struct QueueNode* next;
	//struct QueueNode* prev;
}QueueNode, Queue;

typedef struct DummyQueue
{
	QueueNode* head;
	QueueNode* tail;
}DummyQueue;

//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256

PStudent createStudent(unsigned int reg, unsigned short group, const char* name);
void deleteStudent(Student* stud);
void printStudent(Student* stud);
//void put(Queue**, Student*);
Queue* put(Queue*, Student*);
Student* get(Queue**);
Student* peek(Queue*);
void deleteQueue(Queue**);
//DummyQueue putDQueue(DummyQueue, Student*);
void putDQueue(DummyQueue*, Student*);
Student* getDQueue(DummyQueue*);

int main()
{
	//Student stud = {.regNo=12300, .groupNo=1055, .name="Popescu Ioan"};
	//printf("sizeof(Student)=%d\n", sizeof(Student));
	DummyQueue queue = { .head = NULL, .tail = NULL };
	Queue* tailQueue = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		char line[LINE_SIZE];
		//char* delimiter = ",";
		char delimiter[] = { ',','\n','\0' };
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
			tailQueue = put(tailQueue, stud);
			//Student* pStud = get(&tailQueue);
			//printStudent(pStud);
		}
		deleteQueue(&tailQueue);
	}
	return 0;
}
Student* getDQueue(DummyQueue* dQueue)
{
	Student* result = NULL;
	if (dQueue->tail != NULL && dQueue->head != NULL)
	{
		result = dQueue->head->info;
		QueueNode* tmp = dQueue->head;
		dQueue->head = tmp->next;
		if (dQueue->head == NULL)
			dQueue->tail = NULL;
		free(tmp);
	}
	return result;
}
QueueNode* createNode(Student* stud)
{
	QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
	if (node != NULL)
	{
		node->info = stud;
		node->next = node;
	}
	return node;
}
void putDQueue(DummyQueue* dQueue, Student* stud)
{
	QueueNode* node = createNode(stud);
	if (dQueue->head == NULL && dQueue->tail == NULL)
	{
		dQueue->head = dQueue->tail = node;
	}
	else
	{
		dQueue->tail->next = node;
		dQueue->tail = node;
	}
}
void deleteQueue(Queue** tailQueue)
{
	Student* stud = NULL;
	while ((stud = get(tailQueue)) != NULL)
	{
		printStudent(stud);
		deleteStudent(stud);
	}
}
Student* peek(Queue* tailQueue)
{
	Student* result = NULL;
	if (tailQueue != NULL)
	{
		result = tailQueue->next->info;
	}
	return result;
}
Student* get(Queue** tailQueue)
{
	Student* result = NULL;
	if (*tailQueue != NULL)
	{
		result = (*tailQueue)->next->info;
		QueueNode* tmp = (*tailQueue)->next;
		(*tailQueue)->next = tmp->next;
		if (tmp->next == tmp)
			(*tailQueue) = NULL;
		free(tmp);
	}
	return result;
}
Queue* put(Queue* tailQueue, Student* stud)
{
	QueueNode* newNode = createNode(stud);
	if (newNode != NULL)
	{
		if (tailQueue == NULL)
		{
			newNode->next = newNode;
		}
		else
		{
			newNode->next = tailQueue->next;
			tailQueue->next = newNode;
		}
		return newNode;
	}
	else
		return tailQueue;
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