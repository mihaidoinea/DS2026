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

//Generic Trees
typedef struct TreeNode {
    Student* data;                 // Data stored in the node
    struct TreeNode* parent;
    struct TreeNode** children; // Array of pointers to child nodes
    int noDescendants;          // Number of children of this node
} TreeNode;
#define LINE_SIZE 256

PStudent createStudent(unsigned int, unsigned short, const char*);
void printStudent(Student*);
void deleteStudent(Student*);
TreeNode* createNode(Student*);
void insertChild(TreeNode*, int, Student*);
void printTree(TreeNode*, int);

int main()
{
    FILE* pFile = fopen("Data.txt", "r");
    TreeNode* root = NULL;

    if (pFile != NULL)
    {
        char line[LINE_SIZE];
        //char* delimiter = ",";
        char delimiter[] = { ',','\n','\0' };
        char* token = NULL;
        char* context = NULL;
        unsigned int regNo;
        unsigned short groupNo;
        unsigned short parent;

        while (fgets(line, LINE_SIZE, pFile))
        {
            token = strtok_s(line, delimiter, &context);
            parent = atoi(token);
            //printf("Remaining line: %s\n", context);

            token = strtok_s(NULL, delimiter, &context);
            regNo = atoi(token);

            token = strtok_s(NULL, delimiter, &context);
            groupNo = atoi(token);
            //printf("Remaining line: %s\n", context);

            token = strtok_s(NULL, delimiter, &context);
            //printf("Remaining line: %s\n", context);
            Student* pStud = createStudent(regNo, groupNo, token);
            
            if(root == NULL)
                root = createNode(pStud);
            else
                insertChild(root, parent, pStud);
        }

        printTree(root, 0);
    }

    return 0;
}
// Function to create a new node
TreeNode* createNode(Student* stud) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    if (newNode != NULL)
    {
        newNode->data = stud;
        newNode->parent = NULL;
        newNode->children = NULL;
        newNode->noDescendants = 0;
    }
    return newNode;
}

void insertChild(TreeNode* root, int parentKey, Student* data) {
    // If the root is NULL, return
    if (root == NULL) return;

    // If the current node matches the parentKey, insert the child
    if (root->data->regNo == parentKey) {
        TreeNode** oldItems = NULL;
        // Allocate space for one more child
        root->children = (TreeNode**)realloc(oldItems = root->children, (root->noDescendants + 1) * sizeof(TreeNode*));

        if (root->children != NULL)
        {
            // Create a new child node
            TreeNode* newChild = createNode(data);
            newChild->parent = root;

            // Add the new child node to the parent's children list
            root->children[root->noDescendants] = newChild;
            root->noDescendants++;
            return;
        }
    }

    // Otherwise, recursively search through the children of the current node
    for (int i = 0; i < root->noDescendants; i++) {
        insertChild(root->children[i], parentKey, data);
    }
}

// Function to print the tree (for debugging purposes)
void printTree(TreeNode* root, int level) {
    if (root == NULL) return;

    // Print the current node's data
    for (int i = 0; i < level; i++) {
        printf("\t");
    }
    printStudent(root->data);

    // Recursively print each child
    for (int i = 0; i < root->noDescendants; i++) {
        printTree(root->children[i], level + 1);
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