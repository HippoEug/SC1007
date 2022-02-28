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
// Credits: https://stackoverflow.com/questions/66828074/creating-a-recursive-function-that-creates-a-expression-tree-from-a-prefix-expre
// Credits: https://www.youtube.com/watch?v=XLORXuZyaaI
// Credits: https://www.geeksforgeeks.org/evaluation-of-expression-tree/
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

// Build expression tree
void createExpTree(BTNode **root, char *prefix) {
    char *splitString;
    splitString = strtok (prefix, " ");
    
    *root = (BTNode*)malloc(sizeof(BTNode));
    
    // Operands, external nodes
    if(isdigit(splitString[0])) {
        (*root)->item = atoi(splitString);
        (*root)->left = (*root)->right = NULL;
    }
    // Operators, internal nodes
    else {
        (*root)->item = splitString[0];
        createExpTree(&(*root)->left, NULL);
        createExpTree(&(*root)->right, NULL);
    }
}

// print Infix
void printTree(BTNode *node) {
    if (node == NULL) {
        return;
    }
    
    // External node
    if ((node->left == NULL) && (node->right == NULL)) {
        printf("%d", node->item);
    }
    // Internal node
    else {
        printTree(node->left);
        printf(" %c ", (char)node->item);
        printTree(node->right);
    }
}

// print Postfix
void printTreePostfix(BTNode *node) {
    if (node == NULL) {
        return;
    }
    
    printTreePostfix(node->left);
    printTreePostfix(node->right);
    // External node
    if ((node->left == NULL) && (node->right == NULL)) {
        printf("%d ", node->item);
    }
    // Internal node
    else {
        printf("%c ", (char)node->item);
    }
}

double computeTree(BTNode *node) {
    if (node == NULL) {
        return 0;
    }

    // Check for operands
    if ((node->left == NULL) && (node->right == NULL)) {
        return (node->item);
    }

    double leftSubTreeSol = computeTree(node->left);
    double rightSubTreeSol = computeTree(node->right);

    if (node->item == '+') {
        return (leftSubTreeSol + rightSubTreeSol);
    }
    if (node->item == '-') {
        return (leftSubTreeSol - rightSubTreeSol);
    }
    if (node->item == '*') {
        return (leftSubTreeSol * rightSubTreeSol);
    }
    return (leftSubTreeSol / rightSubTreeSol);
}
