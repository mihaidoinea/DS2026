#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#pragma pack(1)
#define LINE_SIZE 256
typedef struct Student
{
	unsigned int regNo;
	unsigned short group;
	char* name;
} Student, * PStudent;

typedef struct QUEUENODE
{
	Student* data;
	struct QUEUENODE* next;
	struct QUEUENODE* prev;

}QUEUENODE;

//DUMMY IMPLEMENTATION
typedef struct QUEUE
{
	struct QUEUENODE* head;
	struct QUEUENODE* tail;
}QUEUE;


//typedef struct Student Student;
//typedef struct Student* PStudent;
PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
QUEUE put(QUEUE, Student*);
Student* get(QUEUE*);
void deleteQueue(QUEUE*);
int main()
{
	QUEUE queue = { .head = NULL, .tail = NULL };
	//queue.head = NULL;
	//queue.tail = NULL;

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
			queue = put(queue, pStud);
			//pStud = get(&queue);
			//printStudent(pStud);
		}
		deleteQueue(&queue);
	}

	return 0;
}

void deleteQueue(QUEUE* queue) {
	Student* stud = NULL;
	while ((stud = get(queue)) != NULL)
	{
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

QUEUE put(QUEUE queue, Student* pStud)
{
	QUEUENODE* nodNou = (QUEUENODE*)malloc(sizeof(QUEUENODE));
	nodNou->data = pStud;
	nodNou->next = nodNou->prev = NULL;

	if (queue.tail == NULL && queue.head == NULL)
	{
		queue.tail = queue.head = nodNou;
	}
	else
	{
		nodNou->prev = queue.tail;
		queue.tail->next = nodNou;
		queue.tail = nodNou;
	}

	return queue;
}


Student* get(QUEUE* queue)
{
	Student* value = NULL;
	if (queue->tail != NULL && queue->head != NULL) {
		value = queue->head->data;
		QUEUENODE* tmp = queue->head;
		queue->head = tmp->next;
		if (queue->head == NULL) {
			queue->tail = NULL;
		}
		else {
			queue->head->prev = NULL;
		}
		free(tmp);
	}
	return value;
}