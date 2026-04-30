#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#pragma pack(1)

typedef unsigned int (*HashFunction) (unsigned int, int);

unsigned int hash1(unsigned int key, int size)
{
	return key % size;
}
unsigned int hash2(unsigned int key, int size)
{
	return (key / size + 1) % size;
}
unsigned int hash3(unsigned int key, int size)
{
	return (key * 13 + 1) % size;
}

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

HashFunction hashFunctions[] = { hash1, hash2, hash3 };

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
		
			hashTable = putStudent(hashTable, pStud);

		}
		printf("\n----------------Hash Table Items--------------------\n");
	
	}

	return 0;
}
HashTable putStudent(HashTable hashTable, Student* pStud)
{
	if (hashTable.items == NULL && hashTable.size == 0)
	{
		//initial allocation
		hashTable.items = (Student**)malloc(sizeof(Student*) * HT_INITIAL_SIZE);
		hashTable.size = HT_INITIAL_SIZE;
		memset(hashTable.items, 0, sizeof(Student*) * HT_INITIAL_SIZE);
	}
	/*int index = hash1(pStud->regNo, hashTable.size);
	if(hashTable.items[index] == NULL)
		hashTable.items[index] = pStud;
	else if (hashTable.items[hash2(pStud->regNo, hashTable.size)] == NULL)
	{
		hashTable.items[hash2(pStud->regNo, hashTable.size)] = pStud;
	}
	else if (hashTable.items[hash3(pStud->regNo, hashTable.size)])
	{
		hashTable.items[hash3(pStud->regNo, hashTable.size)] = pStud;
	}
	else
	{
		resizeHT(&hashTable);
	}*/
	int noEl = sizeof(hashFunctions) / sizeof(HashFunction);
	for (int i = 0; i < noEl; i++)
	{
		int index = hashFunctions[i](pStud->regNo, hashTable.size);
		if (hashTable.items[index] == NULL)
		{
			hashTable.items[index] = pStud;
			return hashTable;
		}
	}
	resizeHT(&hashTable);
	hashTable = putStudent(hashTable, pStud);
	return hashTable;
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