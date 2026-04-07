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


typedef struct HTable
{
	Student** items;
	int size;
}HashTable;


#define LINE_SIZE 256
#define HT_INITIAL_SIZE 3
//#define HT_INITIAL_SIZE 7

PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*); 
void resizeHT(HashTable*);
void putHashTable(HashTable*, Student*);
void displayStudents(HashTable);

int main()
{
	FILE* pFile = fopen("Data.txt", "r");
	HashTable hashTable = { .items = NULL, .size = 0 };

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
			putHashTable(&hashTable, pStud);
		}
		printf("\n----------------Hash Table Items--------------------\n");
		displayStudents(hashTable);
	}

	return 0;
}

void displayStudents(HashTable hashTable)
{
	for (int i = 0; i < hashTable.size; i++)
	{
		printf("Bucket %d:\n", i);
		printStudent(hashTable.items[i]);
	}
}

int fhash(unsigned char key, int size)
{
	return key % size;
}


int linearProbing(HashTable* hTabel, char key, int index)
{
	while (hTabel->items[index] != NULL)
	{
		index++;
		if (hTabel->size == index)
		{
			printf("\n----------------Hash Table Items before Resize-------------------\n");
			displayStudents(*hTabel);
			resizeHT(hTabel);
			index = fhash(key, hTabel->size);
		}
	}
	return index;
}

void putHashTable(HashTable* hTable, Student* stud)
{
	if (hTable->size == 0)
	{
		hTable->items = (Student**)malloc(sizeof(Student*) * HT_INITIAL_SIZE);
		hTable->size = HT_INITIAL_SIZE;
		memset(hTable->items, 0, sizeof(Student*) * HT_INITIAL_SIZE);
	}
	int index = fhash(stud->regNo, hTable->size);
	if (hTable->items[index] != NULL)
	{
		char key = stud->regNo;
		index = linearProbing(hTable, key, index);
	}
	hTable->items[index] = stud;
}

void resizeHT(HashTable* hTable)
{
	Student** aux = hTable->items;
	hTable->size *= 3;
	hTable->items = (Student**)malloc(sizeof(Student*) * hTable->size);
	memset(hTable->items, 0, sizeof(Student*) * hTable->size);
	for (int index = 0; index < hTable->size / 3; index++)
	{
		Student* stud = aux[index];
		if (stud != NULL)
		{
			putHashTable(hTable, stud);
		}
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