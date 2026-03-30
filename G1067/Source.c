//#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define LINE_BUFFER 256
#pragma pack(1)

typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;

typedef struct QueueNode {
	Student* info;
	struct QueueNode* next;
}QueueNode;
//DUMMY IMPLEMENTATION
typedef struct Queue {
	QueueNode* head;
	QueueNode* tail;
}Queue;
//typedef struct Student Student;


Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
Queue put(Queue, Student*);
Student* get(Queue*);
void deleteQueue(Queue* queue);

int main()
{

	Queue queue = {
	.head = NULL,
	.tail = NULL
	};
	//queue.head = NULL;
	//queue.tail = NULL;

	FILE* fp = fopen("Data.txt", "r");

	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		//char* delimiter = ",";
		char delimiter[] = { ',','\n','\0' };
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

			queue = put(queue, stud);
			//stud = get(&queue);
			//printStudent(queue.tail->info);
			//printStudent(stud);

		}
		deleteQueue(&queue);

	}
}
QueueNode* createNode(Student* stud) {

	QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
	newNode->info = stud;
	newNode->next = NULL;
	return newNode;
}
//void put(Queue*, Student*);
Queue put(Queue queue, Student* stud) {


	QueueNode* queueNode = createNode(stud);

	if (queue.head == NULL && queue.tail == NULL) {
		queue.head = queue.tail = queueNode;
	}
	else {
		queue.tail->next = queueNode;
		queue.tail = queueNode;
	}

	return queue;
}

Student* get(Queue* queue) {
	Student* stud = NULL;
	if (queue->head != NULL && queue->tail != NULL)
	{
		stud = queue->head->info;
		QueueNode* tmp = queue->head;
		queue->head = tmp->next;
		if (queue->head == NULL) {
			queue->tail = NULL;
		}
		free(tmp);
	}

	return stud;
}

void deleteQueue(Queue* queue) {
	Student* stud = NULL;
	while ((stud = get(queue)) != NULL) {
		printStudent(stud);
		deleteStudent(stud);
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
	if (pStud != NULL)
		printf("RegNo=%d, GroupNo=%d, Name=%s\n",
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