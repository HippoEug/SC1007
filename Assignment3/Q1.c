//
// Expression Tree
//
// Write 4 Functions
//
// 1: createExpTree()
// Create expression tree using a prefix expression.
// Each element is sperated by white spaces.
// Insert each operator as an internal node.
// Insert each operand as a leaf node.
//
// 2: printTree()
// Print all tree nodes by infix expression.
//
// 3: printTreePostfix()
// Print all tree nodes by postfix expression.
//
// 4: computeTree()
// Calculate the given arithmetic expression.
//
// ie Input 1
// + 99 * - 88 77 + / 66 - 55 44 33
//
// ie Output 1
// 99 + 88 - 77 * 66 / 55 - 44 + 33
// 99 88 77 - 66 55 44 - / 33 + * +
// 528.00
//
// Credits: https://www.geeksforgeeks.org/building-expression-tree-from-prefix-expression/
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 // Number digit limitation

typedef struct _btnode {
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _node {
    BTNode *item;
    struct _node *next;
} StackNode;

typedef struct _stack {
    int size;
    StackNode *head;
} Stack;

void deleteTree(BTNode **root);
void createExpTree(BTNode **root, char *prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr, BTNode *item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main() {
    char prefix[SIZE];
    BTNode *root = NULL;
    
    //printf("Enter a prefix expression: \n");
    gets(prefix);
    
    createExpTree(&root, prefix);
    
    //printf("The Infix Expression: \n");
    printTree(root);
    printf("\n");
    
    //printf("The Postfix Expression: \n");
    printTreePostfix(root);
    printf("\n");
    
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
}

void push(Stack *sPtr, BTNode *item) {
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr) {
    if (sPtr == NULL || sPtr->head == NULL) {
        return 0;
    }
    else {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

BTNode *peek(Stack s) {
    return s.head->item;
}

int isEmptyStack(Stack s) {
    if (s.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void deleteTree(BTNode **root) {
    BTNode *temp;
    if (*root != NULL) {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}

void createExpTree(BTNode **root, char *prefix) {
    
}

void printTree(BTNode *node) {
    
}

void printTreePostfix(BTNode *node) {
    
}

double computeTree(BTNode *node) {
    
}
