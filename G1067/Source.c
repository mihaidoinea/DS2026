//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#pragma pack(1)
typedef struct Student {
	unsigned int regNo;
	short int groupNo;
	char* name;
} Student, * PStudent;

typedef struct StackNode
{
	Student* data;
	struct StackNode* next;
}StackNode, * PStackNode;

typedef struct DoubleStack
{
	StackNode* head1;
	StackNode* head2;
}DoubleStack;

//typedef struct Student Student;
#define LINE_BUFFER 256

Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
bool isEmpty(StackNode*);
StackNode* push(StackNode*, Student*);
Student* pop(StackNode**);
Student* peek(StackNode*);

bool isEmpty(StackNode* head)
{
	if (head != NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}

StackNode* push(StackNode* head, Student* stud)
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	newNode->data = stud;
	newNode->next = NULL;
	if (isEmpty(head) == false)
	{
		newNode->next = head;
	}
	return newNode;
}

Student* pop(StackNode** head) {
	if (isEmpty(*head) == true)
		return NULL;
	else
	{
		// 1. return the useful info
		// 2. delete the node
		// 3. change the head

		Student* stud = (*head)->data;
		StackNode* tmp = *head;
		(*head) = (*head)->next;
		free(tmp);
		return stud;
	}
}

Student* peek(StackNode* head) {
	if (isEmpty(head) == true)
	{
		return NULL;
	}
	else
	{
		return head->data;
	}
}

void deleteStack(StackNode** stack);

int main()
{
	PStackNode stack = NULL;
	DoubleStack doubleStack = { .head1 = NULL, .head2 = NULL };

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
			stack = push(stack, stud);
			stud = peek(stack);
			printStudent(stud);

		}
		deleteStack(&stack);
	}
}

void deleteStack(StackNode** stack) {
	while (isEmpty(*stack) == false)
	{
		Student* stud = pop(stack);
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