#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#pragma pack(1)
typedef struct Student
{
	unsigned int regNo;
	unsigned short groupNo;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256
typedef struct StackNode
{
	Student* data;
	struct StackNode* next;
}StackNode, Stack;

void printStudent(Student*);
PStudent createStudent(unsigned int, unsigned short, const char*);
void deleteStudent(Student*);
bool isEmpty(Stack*);
Stack* push(Stack*, Student*);
Student* pop(Stack**);
Student* peek(Stack*);
void deleteStack(Stack**);

int main()
{
	Stack* stackHead = NULL;

	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		//char* delimiter = ",";
		char delimiter[] = { ',','\n','\0' };
		char line[LINE_SIZE];
		char* token = NULL, * context = NULL;
		unsigned int regNo;
		unsigned short groupNo;
		while (fgets(line, LINE_SIZE, pFile))
		{
			token = strtok_s(line, delimiter, &context);
			regNo = atoi(token);
			//printf("Remaining string: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			groupNo = atoi(token);
			//printf("Remaining string: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			Student* stud = createStudent(regNo, groupNo, token);
			stackHead = push(stackHead, stud);
		}
		deleteStack(&stackHead);
	}
	return 0;
}

bool isEmpty(Stack* stack) {
	if (stack == NULL) return true;
	else return false;
}

StackNode* createNode(Student* stud) {
	StackNode* node = (StackNode*)malloc(sizeof(StackNode));
	node->data = stud;
	node->next = NULL;
	return node;
}

Stack* push(Stack* stackHead, Student* stud) {
	StackNode* stackNode = createNode(stud);
	if (isEmpty(stackHead) != true)
	{
		stackNode->next = stackHead;

	}
	return stackNode;
}

Student* pop(Stack** stackHead)
{
	if (isEmpty(*stackHead))
	{
		return NULL;
	}
	else
	{
		Student* stud = (*(*stackHead)).data;
		StackNode* temp = *stackHead;
		(*stackHead) = (*stackHead)->next;
		free(temp);
		return stud;
	}
}

void deleteStack(Stack** stackHead)
{
	Student* stud = NULL;
	while ((stud = pop(stackHead)) != NULL)
	{
		printStudent(stud);
		deleteStudent(stud);
	}
}

Student* peek(Stack* stackHead)
{
	if (!isEmpty(stackHead))
	{
		return stackHead->data;
	}
	return NULL;
}





PStudent createStudent(unsigned int reg, unsigned short group,
	const char* name)
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
		{
			free(stud->name);
		}
		free(stud);
	}
}
void printStudent(PStudent pStud)
{
	if (pStud != NULL)
	{
		printf("Student: %s, regNo: %d, groupNo: %d\n",
			pStud->name, pStud->groupNo, pStud->regNo);
	}
}