//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;

typedef struct PQueue
{
	Student** items;
	int size;
	int currentPosition;
}PriorityQueue;

#define LINE_BUFFER 256
#define PQUEUE_INITIAL_SIZE 3
Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
void InitPriorityQueue(PriorityQueue*);
void Enqueue(PriorityQueue*, Student*);
Student* dequeue(PriorityQueue*);
//PQueue implementation is based on the regNo order(lower-higher)
int main()
{
	FILE* fp = fopen("Data.txt", "r");
	PriorityQueue pq = { .items = NULL,.size = 0,.currentPosition = 0 };
	InitPriorityQueue(&pq);
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
			Enqueue(&pq, stud);

		}

		Student* stud = NULL;
		while((stud = dequeue(&pq)) != NULL)
			printStudent(stud);

	}
}

void reHeapDown(PriorityQueue* pq, int parentIndex)
{
	int childIndexLeft = 2 * parentIndex + 1;
	int childIndexRight = 2 * parentIndex + 2;
	int maxIndex = parentIndex;
	if (childIndexLeft < pq->currentPosition)
	{
		if (pq->items[parentIndex]->regNo > pq->items[childIndexLeft]->regNo)
		{
			maxIndex = childIndexLeft;
		}
		if (childIndexRight < pq->currentPosition && pq->items[maxIndex] > pq->items[childIndexRight])
			maxIndex = childIndexRight;
		if (parentIndex != maxIndex)
		{
			Student* tmp = pq->items[maxIndex];
			pq->items[maxIndex] = pq->items[parentIndex];
			pq->items[parentIndex] = tmp;
			reHeapDown(pq, maxIndex);
		}
	}
}

Student* dequeue(PriorityQueue* pq)
{
	Student* result = NULL;
	if (pq->currentPosition > 0)
	{
		result = pq->items[0];
		pq->items[0] = pq->items[pq->currentPosition-1];
		pq->currentPosition--;
		reHeapDown(pq, 0);
	}
	return result;
}

void reHeapUp(PriorityQueue* pq, int childIndex)
{
	int parentIndex = (childIndex - 1) / 2;
	if (pq->items[parentIndex]->regNo > pq->items[childIndex]->regNo)
	{
		Student* tmp = pq->items[parentIndex];
		pq->items[parentIndex] = pq->items[childIndex];
		pq->items[childIndex] = tmp;
		reHeapUp(pq, parentIndex);
	}
}

void Enqueue(PriorityQueue* pq, Student* stud)
{
	//valid positions?
	if (pq->currentPosition < pq->size)
	{
		pq->items[pq->currentPosition] = stud;
		reHeapUp(pq, pq->currentPosition);
		pq->currentPosition++;
	}

}

void InitPriorityQueue(PriorityQueue* pq)
{
	if (pq->items == NULL || pq->size == 0 || pq->currentPosition == 0)
	{
		pq->items = (Student**)malloc(sizeof(Student*) * PQUEUE_INITIAL_SIZE);
		memset(pq->items, 0, sizeof(Student*) * PQUEUE_INITIAL_SIZE);
		pq->size = PQUEUE_INITIAL_SIZE;
		pq->currentPosition = 0;
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