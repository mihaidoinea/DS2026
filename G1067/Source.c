//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma pack(1)
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name; 
} Student, *PStudent;
//typedef struct Student Student;
#define LINE_BUFFER 256

//Singly-linked list definition
typedef struct ListNode {
	Student* data;
	struct ListNode* next;
}ListNode, *PListNode;

void insertStudentToEndList(ListNode**, Student*);
void printSinglyLinkedList(ListNode*);

Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
ListNode* createNode(Student*);

void insertStudentToArrayBasedList(ListNode** vector, Student* stud, short* size) {
	ListNode* node = createNode(stud);
	//insertion in the list at the begining
	//element on size index is the head of the list
	if (*size == 0)
		vector[(*size)++] = node;
	else
	{
		node->next = vector[(*size)-1];
		//insertion in the array
		vector[(*size)++] = node;
	}
	
	
}

int main()
{
	ListNode* singlyLinkedList = NULL;

	ListNode* vector[100];
	memset(vector, 0, sizeof(vector));

	FILE* fp = fopen("Data.txt", "r");
	
	if (fp != NULL)
	{
		char line[LINE_BUFFER];
		char* delimiter = ",";
		//char delimiter[] = {',','\0'};
		unsigned int regNo;
		short int groupNo;
		char* token = NULL;
		char* context = NULL;
		short size = 0;
		while (fgets(line, LINE_BUFFER, fp))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);
			
			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);

			token = strtok_s(NULL, delimiter, &context);

			Student* stud = createStudent(regNo, groupNo, token);

			//insertStudentToEndList(&singlyLinkedList, stud);
			insertStudentToArrayBasedList(vector, stud,  &size);

			printSinglyLinkedList(vector[size-1]);
			printf("\n------------------------\n");
		}
	}
	//deleteStudent(stud);
}

ListNode* createNode(Student* stud)
{
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node != NULL)
	{
		node->data = stud;
		node->next = NULL;
	}
	return node;
}
void printSinglyLinkedList(ListNode* list)
{
	if (list != NULL)
	{
		while (list)
		{
			printStudent(list->data);
			list = list->next;
		}
	}
}

void insertStudentToEndList(ListNode** list, Student* stud)
{
	ListNode* node = createNode(stud);
	ListNode* tmp = *list;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
	else
		*list = node;
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
	if(pStud != NULL)
		printf("RegNo=%d, GroupNo=%d, Name=%s", 
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