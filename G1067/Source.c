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
typedef struct DoubleLinkedList {
	Student* info;
	struct DoubleLinkedList* next;
	struct DoubleLinkedList* prev;
}DoubleLinkedList;
typedef struct HT
{
	DoubleLinkedList** items;
	int size;
}HashTable;

//typedef struct Student Student;
#define LINE_BUFFER 256
#define HT_INITIAL_SIZE 3

Student* createStudent(unsigned int, short int, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
void putStudent(HashTable*, Student*);
void printHashTable(HashTable);

int main()
{
	FILE* fp = fopen("Data.txt", "r");
	HashTable hashtable = { .items = NULL,.size = 0 };
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
			putStudent(&hashtable, stud);
		}
		printHashTable(hashtable);

		//deleteStudent(hashtable, 1070, "Popescu Ion");
		//deleteStudent(hashtable, 1070);
	}
}

void printHashTable(HashTable hashTable)
{
	for (int i = 0; i < hashTable.size; i++)
	{
		printf("Bucket: %d\n", i);
		DoubleLinkedList* iterator = hashTable.items[i];
		do
		{
			printStudent(iterator->info);
			iterator = iterator->next;
		} while (iterator != hashTable.items[i]);
	}
}

int fhash(int key, int size)
{
	return key % size;
}

DoubleLinkedList* insertCdll(DoubleLinkedList* list, Student* stud)
{
	DoubleLinkedList* node = (DoubleLinkedList*)malloc(sizeof(DoubleLinkedList));
	node->info = stud;
	node->next = node->prev = NULL;
	if (list == NULL) {
		node->next = node->prev = node;
		list = node;
	}
	else
	{
		// connect node-> struct, connect struct -> node
		node->next = list;
		node->prev = list->prev;

		list->prev = node;
		node->prev->next = node;
	}
	return list;
}

void putStudent(HashTable* ht, Student* stud)
{
	if ((*ht).items == NULL || ht->size == 0)
	{
		ht->items = (DoubleLinkedList**)malloc(HT_INITIAL_SIZE * sizeof(DoubleLinkedList*));
		ht->size = HT_INITIAL_SIZE;
		memset(ht->items, 0, HT_INITIAL_SIZE * sizeof(DoubleLinkedList*));
	}
	int index = fhash(stud->groupNo, ht->size);
	ht->items[index] = insertCdll(ht->items[index], stud);
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