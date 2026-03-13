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

typedef struct ListNode
{
	Student* data;
	struct ListNode* next;
}ListNode, *PListNode;

PStudent createStudent(unsigned int, unsigned short, const char*);
void deleteStudent(Student*);
void printStudent(Student*);
void insertIntoLinkedList(ListNode**, Student*);
void printSinglyLinkedList(PListNode);
PListNode insertIntoHeadLinkedList(PListNode, Student*);
void deleteSinglyLinkedList(ListNode**);

int main()
{
	ListNode* simplyLinkedList = NULL;

	Student stud = {.regNo=12300, .groupNo=1055, .name="Popescu Ioan"};
	printf("sizeof(Student)=%d\n", sizeof(Student));

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

			//	insertIntoEndLinkedList(&simplyLinkedList, stud);
			simplyLinkedList = insertIntoHeadLinkedList(simplyLinkedList, stud);
			printSinglyLinkedList(simplyLinkedList);
			printf("\n-------------------------------\n");

		}
		deleteSinglyLinkedList(&simplyLinkedList);

		printSinglyLinkedList(simplyLinkedList);
	}
	return 0;
}

void deleteSinglyLinkedList(ListNode** simplyLinkedList)
{
	while (*simplyLinkedList)
	{
		ListNode* tmp = *simplyLinkedList;
		*simplyLinkedList = (*simplyLinkedList)->next;
		free(tmp->data->name);
		free(tmp->data);
		free(tmp);
	}
}

PListNode createNode(PStudent stud)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node != NULL)
	{
		node->data = stud;
		node->next = NULL;
	}
	return node;
}
PListNode insertIntoHeadLinkedList(PListNode headList, Student* pStud)
{
	ListNode* node = createNode(pStud);
	if (node != NULL)
	{
		node->next = headList;
		return node;
	}
	return headList;
}

void printSinglyLinkedList(PListNode headList)
{
	while (headList)
	{
		printStudent(headList->data);
		headList = headList->next;
	}
}
void insertIntoLinkedList(ListNode** headList, Student* pStud)
{
	ListNode* node = createNode(pStud);
	if (node != NULL) 
	{
		if (*headList != NULL)
		{
			PListNode aux = *headList;
			while (aux->next) // while(headList->next != NULL)
				aux = aux->next;
			aux->next = node;
		}
		else
			*headList = node;
	}
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