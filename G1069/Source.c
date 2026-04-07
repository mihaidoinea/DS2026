#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#pragma pack(1)
typedef struct Student
{
	unsigned int regNo;
	unsigned short groupNo;
	char* name;
} Student, * PStudent;

typedef struct DoubleLinkedList
{
	Student* info;
	struct DoubleLinkedList* next;
	struct DoubleLinkedList* prev;
} DoubleLinkedList;

typedef struct HashTable
{
	DoubleLinkedList** items;
	unsigned int size;
} HashTable;


//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256
#define HTINITIAL_SIZE 3

void printStudent(Student*);
PStudent createStudent(unsigned int, unsigned short, const char*);
void deleteStudent(Student*);
void putStudent(HashTable*, Student*);
void displayHashTable(HashTable);

int main()
{
	HashTable table = { .items = NULL, .size = 0 };


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

			putStudent(&table, stud);
		}

		displayHashTable(table);

		//deleteStudentByKey(table, 1070);
		//deleteStudentByKeyAndName(table, 1070, "Popescu Ion");
	}
	return 0;
}

void displayHashTable(HashTable hashTable)
{
	for (unsigned int i = 0; i < hashTable.size; i++)
	{
		printf("---------------Bucket %d---------------\n", i);
		DoubleLinkedList* iterator = hashTable.items[i];
		do
		{
			printStudent(iterator->info);
			iterator = iterator->next;
		} while (iterator != hashTable.items[i]);
	}
}

void insertDCLL(DoubleLinkedList** bucket, Student* stud) {
	DoubleLinkedList* newNode = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
	newNode->info = stud;
	newNode->next = NULL;
	newNode->prev = NULL;
	if (*bucket == NULL) {
		newNode->next = newNode->prev = newNode;
		*bucket = newNode;
	}
	else {
		newNode->prev = (*bucket)->prev;
		newNode->next = *bucket;
		(*bucket)->prev = newNode;
		newNode->prev->next = newNode;
	}
}
unsigned int fhash(unsigned int key, unsigned int size)
{
	return key % size;
}

void putStudent(HashTable* table, Student* stud)
{
	if (table->size == 0 || table->items == NULL) {
		table->items = (DoubleLinkedList**)malloc(HTINITIAL_SIZE * sizeof(DoubleLinkedList*));
		table->size = HTINITIAL_SIZE;
		memset(table->items, 0, HTINITIAL_SIZE * sizeof(DoubleLinkedList*));
	}
	int index = fhash(stud->groupNo, table->size);
	insertDCLL(&table->items[index], stud);
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
			pStud->name, pStud->regNo, pStud->groupNo);
	}
}