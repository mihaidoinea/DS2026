#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(4)
typedef struct Student
{
	unsigned int regNo;
	unsigned short groupNo;
	char* name;
} Student, * PStudent;
//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256

typedef struct BST
{
	Student* stud;
	struct BST* left;
	struct BST* right;
}BinarySearchTree;

PStudent createStudent(unsigned int reg, unsigned short group, const char* name);
void deleteStudent(Student* stud);
void printStudent(Student* stud);
BinarySearchTree* insert(BinarySearchTree*, Student*);
void printTree(BinarySearchTree*);
BinarySearchTree* deleteTree(BinarySearchTree*);
void deleteByKey(BinarySearchTree** root, unsigned int regNo);
int main()
{
	//Student stud = {.regNo=12300, .groupNo=1055, .name="Popescu Ioan"};
	//printf("sizeof(Student)=%d\n", sizeof(Student));
	BinarySearchTree* root = NULL;


	FILE* pFile = fopen("Data.txt", "r");
	if (pFile != NULL)
	{
		char line[LINE_SIZE];
		//char* delimiter = ",";
		char delimiter[] = { ',','\n','\0' };
		char* token = NULL, * context = NULL;
		unsigned int reg;
		unsigned short group;
		char buffer[LINE_SIZE];
		while (fgets(line, LINE_SIZE, pFile))
		{
			token = strtok_s(line, delimiter, &context);
			reg = atoi(token);
			//printf("Remaining string: %s\n", context);

			token = strtok_s(NULL, delimiter, &context);
			strcpy_s(buffer, strlen(token) + 1, token);

			token = strtok_s(NULL, delimiter, &context);
			group = atoi(token);
			//printf("Remaining string: %s\n", context);

			Student* stud = createStudent(reg, group, buffer);
			root = insert(root, stud);
		}
		printTree(root);
		deleteByKey(&root, 12340);
		//root = deleteTree(root);
		printf("\n---------------------------\n");
		printTree(root);
	}
	return 0;
}

void deleteByKey(BinarySearchTree** root, unsigned int regNo)
{
	if ((*root) != NULL)
	{
		if (regNo < (*root)->stud->regNo)
			deleteByKey(&(*root)->left, regNo);
		else if (regNo > (*root)->stud->regNo)
			deleteByKey(&(*root)->right, regNo);
		else
		{
			if ((*root)->left == NULL && (*root)->right == NULL)
			{
				deleteStudent((*root)->stud);
				free((*root));
				(*root) = NULL;

			}
			else if ((*root)->left == NULL || (*root)->right == NULL)
			{
				BinarySearchTree* desc = (*root)->left ? (*root)->left : (*root)->right;
				deleteStudent((*root)->stud);
				free((*root));
				(*root) = desc;
			}
			else
			{

			}

		}

	}
}

BinarySearchTree* deleteTree(BinarySearchTree* root) {
	if (root != NULL) {
		root->left = deleteTree(root->left);
		root->right = deleteTree(root->right);
		deleteStudent(root->stud);
		free(root);
		root = NULL;
	}
	return root;
}

void printTree(BinarySearchTree* root) {
	if (root != NULL) {
		printTree(root->left);
		printStudent(root->stud);
		printTree(root->right);
	}
}

BinarySearchTree* createNode(Student* stud)
{
	BinarySearchTree* rezultat = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	if (rezultat != NULL)
	{
		rezultat->stud = stud;
		rezultat->left = NULL;
		rezultat->right = NULL;
	}
	return rezultat;

}

BinarySearchTree* insert(BinarySearchTree* root, Student* stud)
{
	if (root == NULL)
	{
		root = createNode(stud);
	}
	else
	{
		if (root->stud->regNo < stud->regNo) {
			root->right = insert(root->right, stud);
		}
		else if (root->stud->regNo > stud->regNo) {
			root->left = insert(root->left, stud);
		}
		else {
			Student* tmp = root->stud;
			root->stud = stud;
			deleteStudent(tmp);
		}
	}
	return root;
}
PStudent createStudent(unsigned int reg, unsigned short group, const char* name)
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
			free(stud->name);
		free(stud);
	}
}
void printStudent(Student* stud)
{
	if (stud != NULL && stud->name != NULL)
	{
		printf("RegNo:%d, Name:%s, group:%d\n",
			stud->regNo, stud->name, stud->groupNo);
	}
}