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
typedef struct Neighbour
{
	struct Vertex* reference;
	struct Neighbour* next;
}Neighbour;
typedef struct Vertex
{
	int position;
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

void printStudent(Student*);
PStudent createStudent(unsigned int, unsigned short, const char*);
void deleteStudent(Student*);
void printListOfLists(Vertex*);
void breadthFirst(Vertex*);

int main()
{
	Vertex* graph = NULL;
	int noVertices = 0;
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
			graph = addVertex(graph, stud);
			noVertices++;
		}

		addEdges(graph, 8700, 4500);
		addEdges(graph, 8700, 17000);
		addEdges(graph, 3000, 17000);
		addEdges(graph, 3000, 15000);
		addEdges(graph, 3000, 13000);
		addEdges(graph, 4500, 15000);
		addEdges(graph, 17000, 13000);

		printListOfLists(graph);

		//1.1 Delete a node from the graph for a given student "Popescu Ioan"
		
		//1.2 Return the list of connections for a given student "Popescu Ioan"

		//2.1 Delete all neighbours from group N for a given student "Popescu Ioan"
		
		//2.2 Return a list with all students from group 1070
		
	}
	return 0;
}

void breadthFirst(Vertex* graph)
{
	int* visited = (int*)malloc(sizeof(int) * graph->position + 1);
	int* queue = (int*)malloc(sizeof(int) * graph->position + 1);
}

void printListOfLists(Vertex* listOfVertices)
{
	while (listOfVertices != NULL) {
		printStudent(listOfVertices->info);

		printf("Neighbours: \n");
		while (listOfVertices->neighbours != NULL) {
			printStudent(listOfVertices->neighbours->reference->info);
			listOfVertices->neighbours = listOfVertices->neighbours->next;
		}
		printf("-------\n");

		listOfVertices = listOfVertices->next;
	}
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
void addEdges(Vertex* listOfVertices, unsigned int src, unsigned int dst)
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
		node->position = 0;
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
		if (listOfVertices)
			vertex->position = listOfVertices->position++;
		vertex->next = listOfVertices;
		listOfVertices = vertex;
	}
	return listOfVertices;
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