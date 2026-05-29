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

PStudent createStudent(unsigned int, unsigned short, const char*);
void deleteStudent(Student*);
void printStudent(Student*);
BinarySearchTree* insert(BinarySearchTree*, Student*);
void printTree(BinarySearchTree*);
BinarySearchTree* deleteTree(BinarySearchTree*);
void deleteByKey(BinarySearchTree**, unsigned int);

int main()
{
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

		//1.1 Calculati numarul de studenti cu regno mai mare decat o valoare transmisa ca parametru 
		//1.2 Determinati nivelul nodului ce stocheaza studentul "Popescu Maria"

		//2.1 Stergeti vecinul stang al unui student al carui nume este transmis ca parametru
		//2.2 Determinati numarul de studenti de pe un anumit nivel din arbore

		//deleteByKey(&root, 13000);
		//root = deleteTree(root);
		//printf("\n---------------------------\n");
		//printTree(root);
	}
	return 0;
}
BinarySearchTree* findMin(BinarySearchTree* root) {
	while (root != NULL && root->left != NULL) {
		root = root->right;
	}
	return root;
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
				//search for the min node in the right subtree
				BinarySearchTree* minDesc = findMin((*root)->right);
				Student* aux = (*root)->stud;
				(*root)->stud = minDesc->stud;
				minDesc->stud = aux;
				deleteByKey(&(*root)->right, minDesc->stud->regNo);
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
		printStudent(root->stud);
		printTree(root->left);
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