#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#pragma pack(1)

typedef struct Student
{
	unsigned int regNo;
	unsigned short group;
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


PStudent createStudent(unsigned int, unsigned short,const char*);
void printStudent(Student*);
void deleteStudent(Student*);

void insertStudentIntoList(ListNode**, Student*);
void printSinglyLinkedList(ListNode*);

int main()
{

	ListNode* studentsList = NULL;

	Student stud = {12000, 17, "Popescu Ioan"};
	printf("sizeof(Student) = %d\n", sizeof(Student));
	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		char line[LINE_SIZE];
		//char* delimiter = ",";
		char delimiter[] = { ',','\n','\0'};
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
			insertStudentIntoList(&studentsList, pStud);
			printSinglyLinkedList(studentsList);

			printf("\n-------------------------------\n");

		}
	}	
	return 0;
}
ListNode* createNode(Student* stud)
{
	//memory allocation
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	if (node != NULL)
	{
		//initialization
		node->data = stud;
		node->next = NULL;
	}
	return node;
}
void printSinglyLinkedList(ListNode* list)
{
	while (list)
	{
		printStudent(list->data);
		list = list->next;
	}
}
void insertStudentIntoList(ListNode** list, Student* stud)
{
	ListNode* node = createNode(stud);
	ListNode* tmp = *list;
	if (tmp != NULL)
	{
		while (tmp->next) //while(list->next!= NULL)
			tmp = tmp->next;
		tmp->next = node;
	}
	else
	{
		*list = node;
	}
}

void deleteStudent(Student* pStud)
{
	if (pStud != NULL)
	{
		if (pStud->name)
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
		stud->name = (char*)malloc(strlen(name)+1);
		if (stud->name != NULL)
		{
			strcpy_s(stud->name, strlen(name)+1, name);
		}
		else
		{
			free(stud);
			stud = NULL;
		}
	}
	return stud;
}