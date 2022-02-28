//
// Finding Largest Binary Search Subtree
//
// Find the largest binary search subtree (largest number of nodes) in a given binary tree.
// Select the leftmost subtree if there are multiple largest subtrees.
// Input is a level-by-level traversal string.
//
// ie Input 1
// 70 35 79 15 50 -1 99 18 -1 40 60 a
//
// ie Output 1
// Enter a list of numbers for a Binary Tree, terminated by any non-digit character:
// The input binary tree:
// 70
// |---35
// |        |---15
// |        |       |---18
// |        |___50
// |        |       |---40
// |        |       |___60
// |___79
//
// The largest binary search subtree:
// 50
// |---40
// |___60
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

//Prototypes of Interface functions for Queue structure
void enqueue(Queue *qPtr, BTNode *data);
int dequeue(Queue *qPtr);
BTNode *getFront(Queue q);
int isEmptyQueue(Queue q);

BTNode *createNode(int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

int getTreeSize(BTNode* root);
int ifBST(BTNode *root, BTNode *left, BTNode *right);
BTNode *findLargestBST(BTNode *root);

int main() {
    BTNode *root = NULL;
    BTNode *temp = NULL;
    Queue q;
    q.head = NULL;
    q.tail = NULL;
    q.size = 0;

    int item;
    int flag = 1;
    
    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while (scanf("%d",&item)) {
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
                    flag = 1;
                    break;
                }
                else {
                    dequeue(&q);
                }
            }
        }
    }
    scanf("%*s");
    printf("The input binary tree:\n");
    printBTNode(root, 0, 0);
    printf("\n");
    
    BTNode* BSTnode = findLargestBST(root);
    printf("The largest binary search subtree:\n");
    
    if (BSTnode) {
        printBTNode(BSTnode, 0, 0);
    }
    else {
        printf("No BST\n");
    }
    deleteTree(&root);
}

BTNode *createNode(int item) {
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    node->item = item;
    node->left = node->right = NULL;
    return node;
}

void printBTNode(BTNode *root, int space, int left) {
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
    //Queue is empty or NULL pointer
    if (qPtr == NULL || qPtr->head == NULL) {
        return 0;
    }
    else {
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
        //Queue is emptied
        if (qPtr->head == NULL) {
           qPtr->tail = NULL;
        }

        free(temp);
        qPtr->size--;
        return 1;
    }
}

BTNode *getFront(Queue q) {
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

int getTreeSize(BTNode* root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return (getTreeSize(root->left) + getTreeSize(root->right) + 1);
    }
}

int ifBST(BTNode *root, BTNode *left, BTNode *right) {
    if (root == NULL) {
        return 1;
    }

    // Check if Binary Search Tree is Invalid
    // ie 18 on the left of 15, but 18 > 15
    if ((left != NULL) && (left->item >= root->item)) {
        return 0;
    }
    if ((right != NULL) && (right->item <= root->item)) {
        return 0;
    }

    //recursively checks all children
    return (ifBST(root->left, left, root) && ifBST(root->right, root, right));
}

BTNode *findLargestBST(BTNode *root) {
    int leftTreeSize = 0;
    int rightTreeSize = 0;
    
    if (root == NULL) {
        return NULL;
    }

    BTNode *leftTraversal;
    BTNode *rightTraversal;

    // Post-order traversal
    leftTraversal = findLargestBST(root->left);
    rightTraversal = findLargestBST(root->right);

    leftTreeSize = getTreeSize(leftTraversal);
    rightTreeSize = getTreeSize(rightTraversal);
    
    // If node is Binary Search Tree
    if (ifBST(root, NULL, NULL)) {
        return root;
    }
    // Else return root of biggest subtree
    else if (leftTreeSize >= rightTreeSize) {
        return leftTraversal;
    }
    else {
        return rightTraversal;
    }
}
