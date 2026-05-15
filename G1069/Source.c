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

typedef struct BST
{
	Student* data;
	struct BST* left;
	struct BST* right;
} BinarySearchTree;

//typedef struct Student Student;
//typedef struct Student* PStudent;
#define LINE_SIZE 256

void printStudent(Student*);
PStudent createStudent(unsigned int, unsigned short, const char*);
void deleteStudent(Student*);
void insert(BinarySearchTree**, Student*);
void printTree(BinarySearchTree*);
void deleteTree(BinarySearchTree**);
BinarySearchTree* deleteByKey(BinarySearchTree*, unsigned int);

int main()
{
	BinarySearchTree* root = NULL;
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

			insert(&root, stud);
		}
		printTree(root);

		root = deleteByKey(root, 12450);

		deleteTree(&root);
		printTree(root);
	}
	return 0;
}

BinarySearchTree* deleteByKey(BinarySearchTree* root, unsigned int key)
{
	if (root != NULL)
	{
		if (root->data->regNo > key)
			root->left = deleteByKey(root->left, key);
		else if (root->data->regNo < key)
			root->right = deleteByKey(root->right, key);
		else
		{
			//the leaf usecase
			if (root->left == NULL && root->right == NULL)
			{
				deleteStudent(root->data);
				free(root);
				root = NULL;
			}
			else if (root->left == NULL || root->right == NULL)
			{
				BinarySearchTree* desc = root->left ? root->left : root->right;
				deleteStudent(root->data);
				free(root);
				root = desc;
			}
			else
			{

			}
		}
	}
}

void deleteTree(BinarySearchTree** root)
{
	if (*root != NULL)
	{
		deleteTree(&(*root)->left);
		deleteTree(&(*root)->right);
		deleteStudent((*root)->data);
		free(*root);
		*root = NULL;
	}
}
BinarySearchTree* createNode(Student* stud) {
	BinarySearchTree* node = (BinarySearchTree*)malloc(sizeof(BinarySearchTree));
	if (node != NULL) {
		node->data = stud;
		node->left = NULL;
		node->right = NULL;
	}
	return node;
}

void printTree(BinarySearchTree* root) {
	if (root != NULL) {
		printTree(root->left);
		printStudent(root->data);
		printTree(root->right);
	}
}

void insert(BinarySearchTree** root, Student* stud)
{
	if ((*root) == NULL) {
		(*root) = createNode(stud);
	}

	else {
		if (stud->regNo > (*root)->data->regNo)
		{
			insert(&(*root)->right, stud);
		}
		else if (stud->regNo < (*root)->data->regNo) {
			insert(&(*root)->left, stud);
		}
		else {
			deleteStudent((*root)->data);
			(*root)->data = stud;
		}
	}
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