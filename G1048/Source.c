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
typedef struct PQueue
{
	PStudent* items;
	int size;
	int currentPos;
}PriorityQueue;
#define LINE_SIZE 256
#define PQInitialSize 100
PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
void enqueue(PriorityQueue*, PStudent);
Student* dequeue(PriorityQueue*);

int main()
{
	FILE* pFile = fopen("Data.txt", "r");
	PriorityQueue pQueue = { .items = NULL,.size = 0,.currentPos = 0 };
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
			enqueue(&pQueue, pStud);
		}

		Student* stud = NULL;
		while ((stud = dequeue(&pQueue)) != NULL)
			printStudent(stud);
	}

	return 0;
}

void reHeapDown(PriorityQueue* pq, int parentIndex)
{
	int childIndexLeft = 2 * parentIndex + 1;
	int childIndexRight = 2 * parentIndex + 2;
	int maxIndex = parentIndex;
	if (childIndexLeft < pq->currentPos)
	{
		if (pq->items[maxIndex]->regNo > pq->items[childIndexLeft]->regNo)
		{
			maxIndex = childIndexLeft;
		}
		if (childIndexRight < pq->currentPos && pq->items[maxIndex]->regNo > pq->items[childIndexRight]->regNo)
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
	if (pq->currentPos > 0)
	{
		result = pq->items[0];
		pq->items[0] = pq->items[pq->currentPos - 1];
		pq->currentPos--;
		reHeapDown(pq, 0);
	}
	return result;
}

void initPQ(PriorityQueue* pq) {
	pq->items = malloc(sizeof(Student*) * PQInitialSize);
	pq->size = PQInitialSize;
	pq->currentPos = 0;
	memset(pq->items, 0, sizeof(Student*) * PQInitialSize);
}

void ReHeapUp(PStudent* items, int currentPos)
{
	int parent_index = (currentPos - 1) / 2;
	if (items[parent_index]->regNo > items[currentPos]->regNo) {
		PStudent aux = items[parent_index];
		items[parent_index] = items[currentPos];
		items[currentPos] = aux;
		ReHeapUp(items, parent_index);
	}

}

void enqueue(PriorityQueue* pq, PStudent stud) {
	if (pq->items == NULL || pq->size == 0)
		initPQ(pq);
	if (pq->currentPos < pq->size)
	{
		pq->items[pq->currentPos] = stud;
		ReHeapUp(pq->items, pq->currentPos);
		pq->currentPos += 1;
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