#pragma once
#include "StudentUtil.h"
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
Vertex* addVertex(Vertex* , Student*);
void addEdges(Vertex*, unsigned int, unsigned int);