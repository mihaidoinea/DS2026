#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
//#pragma pack(1)

typedef struct Student
{
	unsigned int regNo;
	unsigned short group;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;
//typedef struct Student* PStudent;
typedef struct StackNode
{
	Student* data;
	struct StackNode* next;
}Stack, StackNode;

#define LINE_SIZE 256
PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*);

bool isEmpty(Stack* head) {
	return head == NULL;
}
StackNode* createNode(Student* s) {
	StackNode* s1 = (StackNode*)malloc(sizeof(StackNode));
	s1->data = s;
	s1->next = NULL;
	return s1;
}
Stack* push(Stack* head, Student* s) {
	StackNode* node = createNode(s);
	if (!isEmpty(head)) {
		node->next = head;
	}
	return node;
}

Student* pop(Stack** head) {
	if (isEmpty(*head)) {
		return NULL;
	}
	else {
		Student* s = (*head)->data;
		StackNode* tmp = *head;
		*head = (*head)->next;
		free(tmp);
		return s;
	}
}
Student* peek(Stack* head) {
	if (isEmpty(head)) {
		return NULL;
	}
	return head->data;
}
void delete(Stack** head) {
	while (!isEmpty(*head)) {
		Student* s = pop(head);
		printStudent(s);
		deleteStudent(s);
	}
}

int main()
{
	Stack* head = NULL;

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
			head = push(head, pStud);
			pStud = peek(head);
			printStudent(pStud);
		}
		delete(&head);
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