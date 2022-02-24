//
// MOVING COST FROM A TO B IN A BINARY TREE
//
// In a given binary tree, each node represents a toll gate.
// nodeV of each node indicates the toll fee (unique & non-negative).
// Find the minimum cost to move from one node to another, including first and last node.
//
// n nodes of binary tree will be read in level-by-level order.
// a - indicates an edge
// @ - indicates no edge
// After tree is constructed, query with two nodes will be given to test
//
// ie Input 1
// 1 a a
// 2 a a
// 3 a @
// 4 a a
// 7 @ @
// 8 a @
// 5 @ @
// 6 @ @
// 9 @ @
// 5 7
//
// ie Output 1
// 1
// |---2
// |        |---4
// |        |       |---5
// |        |       |___6
// |        |___7
// |___3
// |        |--8
// |        |       |---9
// Distance is 18

#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode {
    int nodeV;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

typedef struct _queuenode {
    BTNode *node;
    struct _queuenode *next;
} QueueNode;

typedef struct _queue {
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

void printBTNode(BTNode *root, int space, int left);
// Queue Prototypes
void enqueue(Queue *qPtr, BTNode *node);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);
int twoNodesCost(BTNode *node, int nodeV1, int nodeV2);

int main() {
    BTNode *root = (BTNode*) malloc(sizeof(BTNode));
    
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;
    
    BTNode *node;
    enqueue(&q, root);
    
    int nodeV;
    char opL, opR;
    
    while (!isEmptyQueue(q)) {
        scanf("%d %c %c", &nodeV, &opL, &opR);
        node = getFront(q);
        dequeue(&q);
        node->nodeV = nodeV;
        
        if (opL != '@') {
            node->left = (BTNode*) malloc(sizeof(BTNode));
            enqueue(&q, node->left);
        }
        else {
            node->left = NULL;
        }
        
        if (opR != '@') {
            node->right = (BTNode*) malloc(sizeof(BTNode));
            enqueue(&q, node->right);
        }
        else {
            node->right = NULL;
        }
    }
    
    int v1, v2;
    scanf("%d %d", &v1, &v2);
    int cost = twoNodesCost(root, v1, v2);
    
    printBTNode(root, 0, 0);
    
    printf("Distance is %d\n", cost);
}

void enqueue(Queue *qPtr, BTNode *node) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    newNode->node = node;
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
    // If queue is empty or NULL
    if (qPtr == NULL || qPtr->head == NULL) {
        return 0;
    }
    else {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        if (qPtr->head == NULL) {
            qPtr->tail = NULL;
        }
        
        free(temp);
        qPtr->size--;
        return 1;
    }
}

BTNode *getFront(Queue q) {
    return q.head->node;
}

int isEmptyQueue(Queue q) {
    if (q.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void printBTNode(BTNode *root, int space, int left) {
    if (root != NULL) {
        int i;
        for (i = 0; i < (space - 1); i++) {
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
        
        printf("%d\n", root->nodeV);
        
        space++;
        printBTNode(root->left, space, 1);
        printBTNode(root->right, space, 0);
    }
}

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2) {
    
}
