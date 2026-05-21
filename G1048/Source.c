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
typedef struct Neighbour
{
	struct Vertex* reference;
	struct Neighbour* next;
}Neighbour;
typedef struct Vertex
{
	Student* info;
	struct Vertex* next;
	Neighbour* neighbours;
}Vertex;
Vertex* createVertex(Student*);
Vertex* addVertex(Vertex*, Student*);
void addEdges(Vertex*, unsigned int, unsigned int);
//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256

PStudent createStudent(unsigned int, unsigned short,const char*);
void printStudent(Student*);
void deleteStudent(Student*);

int main()
{
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
			
			graph = addVertex(graph, pStud);
			noVertices++;
		}

		addEdges(graph, 8700, 4500);
		addEdges(graph, 8700, 17000);
		addEdges(graph, 3000, 17000);
		addEdges(graph, 3000, 15000);
		addEdges(graph, 3000, 13000);
		addEdges(graph, 4500, 15000);
		addEdges(graph, 17000, 13000);
	}
	
	return 0;
}

Vertex* findVertex(Vertex* list, unsigned int key)
{
	while (list && list->info->regNo != key)
	{
		list = list->next;
	}
	return list;
}
Neighbour* insertNeighbour(Neighbour* neighbours, Vertex* vertex)
{
	Neighbour* node = (Neighbour*)malloc(sizeof(Neighbour));
	if (node != NULL)
	{
		node->reference = vertex;
		node->next = neighbours;
	}
	return node;
}
void addEdges(Vertex* listOfVertices,
	unsigned int src, unsigned int dst)
{
	Vertex* srcVertex = findVertex(listOfVertices, src);;
	Vertex* dstVertex = findVertex(listOfVertices, dst);;

	if (srcVertex != NULL && dstVertex != NULL)
	{
		srcVertex->neighbours = insertNeighbour(srcVertex->neighbours, dstVertex);
		dstVertex->neighbours = insertNeighbour(dstVertex->neighbours, srcVertex);
	}
}

Vertex* createVertex(Student* stud)
{
	Vertex* node = (Vertex*)malloc(sizeof(Vertex));
	if (node != NULL)
	{
		node->info = stud;
		node->neighbours = NULL;
		node->next = NULL;
	}
	return node;
}

Vertex* addVertex(Vertex* listOfVertices, Student* stud)
{
	Vertex* vertex = createVertex(stud);
	if (vertex != NULL)
	{
		vertex->next = listOfVertices;
		listOfVertices = vertex;
	}
	return listOfVertices;
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