//
// Correction of Binary Search Tree
//
// Find and correct a binary search tree with two error nodes which are swapped.
// If the input is -1, it is a NULL node.
// Input is a level-by-level traversal string.
//
// ie Input 1
// 4 2 6 1 -1 -1 7 -1 0 a
//
// ie Output 1
// Enter a list of numbers for a Binary Tree, terminated by any non-digit character:
// The input binary tree:
// 4
// |---2
// |        |---1
// |        |       |___0
// |___6
// |        |___7
//
// The corrected binary search tree:
// 4
// |---2
// |        |---0
// |        |       |___1
// |___6
// |        |___7
//
// Credits: https://www.geeksforgeeks.org/fix-two-swapped-nodes-of-bst/
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode {
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queueNode {
    BTNode *data;
    struct _queueNode *next;
} QueueNode;

typedef struct _queue {
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

typedef struct _stackNode {
    BTNode *data;
    struct _stackNode *next;
} StackNode;

typedef struct _stack {
    int size;
    StackNode *top;
} Stack;

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode *data);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode *createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

//Prototypes of Interface functions for Stack structure
void push(Stack *sPtr, BTNode *data);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

void BSTCorrection(BTNode *root);

void correctBST(struct node *root);

int main() {
    BTNode *root = NULL;
    BTNode *temp = NULL;
    
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag=1;
    
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while (scanf("%d", &item)) {
        if (root == NULL) {
            if (item != -1) {
                root = createNode(item);
                enqueue(&q, root);
            }
        }
        else {
            while (!isEmptyQueue(q)) {
                temp = getFront(q);
                if (flag) {
                    if (item != -1) {
                        temp->left = createNode(item);
                        enqueue(&q, temp->left);
                    }
                    flag = 0;
                    break;
                }
                else if (temp->right == NULL) {
                    if (item != -1) {
                        temp->right = createNode(item);
                        enqueue(&q, temp->right);
                    }
                    dequeue(&q);
                    flag=1;
                    break;
                }
                else {
                    dequeue(&q);
                }
            }
        }
    }
    scanf("%*s");

    printf("The input binary search tree:\n");
    printBTNode(root,0,0);
    printf("\n");
    
    printf("The corrected binary search tree:\n");
    BSTCorrection(root);
    //correctBST(root);

    printBTNode(root,0,0);
    deleteTree(&root);
}

BTNode *createNode(int item) {
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    node->item = item;
    node->left = node->right = NULL;
    return node;
}

void printBTNode(BTNode *root,int space,int left) {
    if (root != NULL) {
        int i;
        for (i = 0; i < space-1; i++) {
            printf("|\t");
        }

        if (i < space) {
            if (left == 1) {
                printf("|---");
            }
            else {
                printf("|___");
            }
        }

        printf("%d\n", root->item);

        space++;
        printBTNode(root->left, space, 1);
        printBTNode(root->right, space, 0);
    }
}

void deleteTree(BTNode **root) {
    if (*root != NULL) {
        deleteTree(&((*root)->left));
        deleteTree(&((*root)->right));
        free(*root);
        *root = NULL;
    }
}

void enqueue(Queue *qPtr, BTNode *data) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;

    if (isEmptyQueue(*qPtr)) {
        qPtr->head = newNode;
    }
    else {
        qPtr->tail->next = newNode;
    }

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if (qPtr == NULL || qPtr->head == NULL) { //Queue is empty or NULL pointer
        return 0;
    }
    else{
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        
        if (qPtr->head == NULL) {//Queue is emptied
           qPtr->tail = NULL;
        }

        free(temp);
        qPtr->size--;
        return 1;
    }
}

BTNode* getFront(Queue q) {
    return q.head->data;
}

int isEmptyQueue(Queue q) {
    if (q.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void push(Stack *sPtr, BTNode *data) {
    StackNode *newNode;
    newNode= (StackNode*) malloc(sizeof(StackNode));
    newNode->data = data;
    newNode->next = sPtr->top;
    sPtr->top = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr) {
    if (sPtr == NULL || sPtr->top == NULL) {
        return 0;
    }
    else {
       StackNode *temp = sPtr->top;
       sPtr->top = sPtr->top->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s) {
    return s.top->data;
}

int isEmptyStack (Stack s) {
    if (s.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}


/*
void BSTCorrection(BTNode *root) {
    static BTNode *originalRoot = NULL;

    static BTNode *prev = NULL;
    int tempVal = 0;
    
    static BTNode *firstError = NULL;
    static BTNode *secondError = NULL;
    static BTNode *parentOfError = NULL;
    
    static int leftVal = -1;
    static int rightVal = -1;
    int left = leftVal;
    int right = rightVal;
    
    if (root == NULL) {
        return;
    }
    
    if (originalRoot == NULL) {
        originalRoot = root;
    }
    
    // Check if Binary Search Tree is Invalid or follows Binary Search Tree Convention
    // ie 18 on the left of 15, but 18 > 15
    if ((left >= 0 && left >= root->item) || (right >= 0 && right <= root->item)) {
        if (firstError == NULL) {
            firstError = root;
            parentOfError = prev;
        }
        else {
            secondError = root;
        }
        
        return;
    }
    
    // Pre-order traversal
    rightVal = root->item;
    prev = root;
    BSTCorrection(root->left);
    leftVal = root->item;
    prev = root;
    rightVal = right;
    BSTCorrection(root->right);
    
    // Fixing the error
    if ((firstError != NULL) && (root == originalRoot)) {
        // Only 1 error found, adjacent error nodes
        if (secondError == NULL) {
            tempVal = parentOfError->item;
            parentOfError->item = firstError->item;
            firstError->item = tempVal;
        }
        // Both errors found, adjacent error nodes
        else if ((firstError->left == secondError) || (firstError->right == secondError)) {
            tempVal = parentOfError->item;
            parentOfError->item = firstError->item;
            firstError->item = tempVal;
        }
        // Error nodes not adjacent
        else {
            tempVal = secondError->item;
            secondError->item = firstError->item;
            firstError->item = tempVal;
            
        }
        
        firstError = secondError = NULL;
        leftVal = rightVal = -1;
        //return BSTCorrection(originalRoot);
    }
}
*/

// In-order Traversal
void BSTCorrectionRecursive(BTNode *root, BTNode **previousNode, BTNode **firstNode, BTNode **middleNode, BTNode **lastNode) {
    if (root) {
        // Recursion for left subtree
        BSTCorrectionRecursive(root->left, previousNode, firstNode, middleNode, lastNode);

        // Check if Binary Search Tree is Invalid or follows Binary Search Tree Convention
        // ie 18 on the left of 15, but 18 > 15
        // If swapped nodes are adjacent, then first and middle contain the resultant nodes
        // Else, first and last contain the resultant nodes
        if ((*previousNode) && ((root->item) < (*previousNode)->item)) {
            // If first violation, mark these two nodes as first and middle
            if (*firstNode == NULL) {
                *firstNode = *previousNode;
                *middleNode = root;
            }
            // If second violation, mark this node as last
            else {
                *lastNode = root;
            }
        }
        *previousNode = root;
        
        // Recursion for right subtree
        BSTCorrectionRecursive(root->right, previousNode, firstNode, middleNode, lastNode);
    }
}

void BSTCorrection(BTNode *root) {
    static BTNode *previousNode = NULL;
    static BTNode *firstNode = NULL;
    static BTNode *middleNode = NULL;
    static BTNode *lastNode = NULL;
  
    // Find the wrong nodes
    BSTCorrectionRecursive(root, &previousNode, &firstNode, &middleNode, &lastNode);
    
    // Fixing/Swapping the two errors on tree
    if (firstNode && middleNode) {
        int temp = firstNode->item;
        firstNode->item = middleNode->item;
        middleNode->item = temp;
        
    }
    else if (firstNode && lastNode) {
        int temp = firstNode->item;
        firstNode->item = lastNode->item;
        lastNode->item = temp;
    }
}
