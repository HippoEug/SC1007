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
    
    if( isdigit(splitString[0]) ) {             // external nodes (= leaves) are operands
        (*root)->item = atoi(splitString);
        (*root)->left = NULL;
        (*root)->right = NULL;
    }
    else {                                // internal nodes are binary operators
        (*root)->item = splitString[0];
        createExpTree(&(*root)->left, NULL);  // continue using the same string prefix
        createExpTree(&(*root)->right, NULL); // continue using the same string prefix
    }
    
    /*
    while (1) {
        char *q = "null";
        
        printf ("hello %s\n", pch);
        
        
        if (*root == NULL) {
            //printf("HELLO HERE\n");
            BTNode *newNode = (BTNode*)malloc(sizeof(BTNode));
            newNode->item = *pch;
            newNode->left = newNode->right = NULL;
            *root = newNode;
        }
        else {
            //printf("HELLO AGSAIN\n");
            // Checking for operand
            if (isdigit(*pch)) {
                printf("isDigit pch: %c \n", *pch);
                return pch;
            }
            //if (*pch >= '0' && *pch <= '9') {
            //    return pch;
            //}
            
            // Build left subtree
            printf("????\n");
            q = createExpTreeRecursive(&(*root)->left, pch + 1);
            printf("!!!!\n");
            // Build right subtree
            q = createExpTreeRecursive(&(*root)->right, q + 1);
            
            return q;
        }
        
        pch = strtok (NULL, " ");
    }
    
    //return 0;
     */
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

void convertToString(BTNode *node, char *str[]) {
    // Convert to postfix code using printpostfix code
    // Then evaluate function using Lab 2 Q3 solution
    
    char temp = "";
    
    if (node == NULL) {
        return;
    }
    
    convertToString(node->left, str);
    convertToString(node->right, str);
    // External node
    if ((node->left == NULL) && (node->right == NULL)) {
        //printf("%d ", node->item);
        sprintf(temp, "%d", node->item);
        strcat(str, temp);
    }
    // Internal node
    else {
        //printf("%c ", (char)node->item);
        //temp[2] = node->item;
        sprintf(temp, "%c", (char)node->item);
        strcat(str, temp);
    }
}

double computeTree(BTNode *node) {
    char str[1024] = "";
    
    convertToString(node, str);
    printf("hello %c", str);
    return 0;
}

/*
double exePostfix(char* postfix)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    int i=0;
    double op1, op2;
    char c;
    double result;
    while(postfix[i]!='\0')
    {
        c = postfix[i++];
        if(c=='*' || c=='/' || c=='+' || c=='-')
        {

            op1 = peek(s); pop(&s);
            op2 = peek(s); pop(&s);

            switch(c)
            {
            case '*':
                push(&s, op2*op1);
                break;
            case '/':
                push(&s, op2/op1);
                break;
            case '+':
                push(&s, op2+op1);
                break;
            case '-':
                push(&s, op2-op1);
            }
        }
        else
            push(&s, (c-'0')) ;

    }

   result = peek(s); pop(&s);
   return result;

}
 */
