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

int getLevel(BTNode *root, int node, int level);
BTNode *getCost(BTNode *root, int nodeV1, int nodeV2, int *distOfV1FromRoot, int *distOfV2FromRoot, int *distOfV1V2, int level);
int twoNodesCost(BTNode *node, int nodeV1, int nodeV2);

void inOrder(BTNode *root);
void preOrder(BTNode *root);
void postOrder(BTNode *root);

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
    
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
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

void inOrder(BTNode *root) {
    if (root == NULL) {
        return;
    }
    
    inOrder(root->left);
    printf("%d", root->nodeV);
    inOrder(root->right);
}

void preOrder(BTNode *root) {
    if (root == NULL) {
        return;
    }
    
    printf("%d", root->nodeV);
    preOrder(root->left);
    preOrder(root->right);
}

void postOrder(BTNode *root) {
    if (root == NULL) {
        return;
    }
    
    postOrder(root->left);
    postOrder(root->right);
    printf("%d", root->nodeV);
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

int getLevel(BTNode *root, int node, int level) {
    if (root == NULL) {
        return -1;
    }
    
    if (root->nodeV == node) {
        return level;
    }
    
    int l = getLevel(root->left, node, level+1);
    
    if (l != -1) {
        return l;
    }
    else {
        getLevel(root->right, node, level+1);
    }
    
    return -1;
}

BTNode *getCost(BTNode *root, int nodeV1, int nodeV2, int *distOfV1FromRoot, int *distOfV2FromRoot, int *distOfV1V2, int level) {
    if (root == NULL) {
        return NULL;
    }
    
    if (root->nodeV == nodeV1) {
        *distOfV1FromRoot = level;
        return root;
    }
    if (root->nodeV == nodeV2) {
        *distOfV2FromRoot = level;
        return root;
    }
    
    BTNode *leftAncestor = getCost(root->left, nodeV1, nodeV2, distOfV1FromRoot, distOfV2FromRoot, distOfV1V2, (level+1));
    BTNode *rightAncestor = getCost(root->right, nodeV1, nodeV2, distOfV1FromRoot, distOfV2FromRoot, distOfV1V2, (level+1));
    
    if (leftAncestor && rightAncestor) {
        *distOfV1V2 = *distOfV1FromRoot + *distOfV2FromRoot - (2*level);
        return root;
    }
    
    if (leftAncestor != NULL) {
        return leftAncestor;
    }
    else {
        return rightAncestor;
    }
}

int twoNodesCost(BTNode *node, int nodeV1, int nodeV2) {
    int distOfV1FromRoot = -1;
    int distOfV2FromRoot = -1;
    int distOfV1V2 = 0;
    
    BTNode *lowestCommonAncestor = getCost(node, nodeV1, nodeV2, &distOfV1FromRoot, &distOfV2FromRoot, &distOfV1V2, 1);
    printf("distOfV1FromRoot: %d\n", distOfV1FromRoot);
    printf("distOfV2FromRoot: %d\n", distOfV2FromRoot);
    printf("distOfV1V2: %d\n", distOfV1V2);
    
    if ((distOfV1FromRoot != -1) && (distOfV2FromRoot != -1)) {
        return distOfV1V2;
    }
    
    if (distOfV1FromRoot != -1) {
        distOfV1V2 = getLevel(lowestCommonAncestor, nodeV2, 0);
        return distOfV1V2;
    }
    
    if (distOfV2FromRoot != -1) {
        distOfV1V2 = getLevel(lowestCommonAncestor, nodeV1, 0);
        return distOfV1V2;
    }
 
    // return -1 if neither nodeV1 or nodeV2 is not in tree
    return -1;
}
