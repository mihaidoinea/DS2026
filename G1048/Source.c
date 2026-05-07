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
#define LINE_SIZE 256

PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*);

//arbori binari de cautare
typedef struct BST {
	Student* student;
	struct BST* left;
	struct BST* right;
}BinarySearchTree;

BinarySearchTree* createNode(Student* s) {
	BinarySearchTree* bts = malloc(sizeof(BinarySearchTree));
	if (bts != NULL) {
		bts->left = NULL;
		bts->right = NULL;
		bts->student = s;

	}
	return bts;
}

BinarySearchTree* insert(BinarySearchTree*, PStudent);
void print_tree(BinarySearchTree*);
void deleteNodeByKey(unsigned int, BinarySearchTree**);

int main()
{
	FILE* pFile = fopen("Data.txt", "r");
	BinarySearchTree* root = NULL;

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

			root = insert(root, pStud);

		}

		print_tree(root);
		deleteNodeByKey(4500, &root);
		print_tree(root);

	}

	return 0;
}

void deleteNodeByKey(unsigned int key, BinarySearchTree** root) {
	if (*root != NULL)
	{
		if (key < (*root)->student->regNo)
			deleteNodeByKey(key, &(*root)->left);
		else if (key > (*root)->student->regNo)
			deleteNodeByKey(key, &(*root)->right);
		else {
			//cazul 1 - leaf
			if ((*root)->left == NULL && (*root)->right == NULL) {
				deleteStudent((*root)->student);
				free(*root);
				(*root) = NULL;
			}
			//cazul 2 - 1 descendent
			else if ((*root)->left == NULL || (*root)->right == NULL) {

			}
			//cazul 3 - 2 descendenti
		}

	}
}


BinarySearchTree* insert(BinarySearchTree* root, PStudent stud)
{
	if (root == NULL)

	{
		BinarySearchTree* node = createNode(stud);
		return node;
	}

	if (root->student->regNo < stud->regNo)
	{
		root->right = insert(root->right, stud);

	}
	else if (root->student->regNo > stud->regNo)
	{
		root->left = insert(root->left, stud);
	}
	else
	{
		PStudent tmp = root->student;
		root->student = stud;
		deleteStudent(tmp);
	}

	return root;
}

void print_tree(BinarySearchTree* root)
{
	if (root != NULL)
	{
		print_tree(root->right);
		printStudent(root->student);
		print_tree(root->left);
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