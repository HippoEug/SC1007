//
// Q3: Number of Visible Pairs
//
// Given a doubly circular linked list
// Each integer represents height of a mountain
// Two mountains A and B can be mutually visible, but need to:
// - A and B not to be the same mountain
// - When A and B are adjacent, they can see each other
// - When A and B are not adjacent, hmin is denoted as the minimum height
// - A and B are mutually visible if the height of any mountain between A and B in either
//      in either clockwise or anti-clockwise is not higher than hmin
//
// Example Input:
// 3
// 1 2 3 4 5 a
// 5 2 2 4 3 a
// 5 4 4 4 3 2 1 5 1 a
//
// Example Output:
// Current List: 5 4 3 2 1
// 7 Pairs.
// Current List: 3 4 2 2 5
// 8 Pairs.
// Current List: 1 5 1 2 3 4 4 4 5
// 18 Pairs.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _dbllistnode {
    int item;
    struct _dbllistnode *next;
    struct _dbllistnode *pre;
} CDblListNode;

typedef struct _dbllinkedlist {
    int size;
    CDblListNode *head;
} CDblLinkedList;

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value);
void deleteList(CDblLinkedList *ptrCDLL);
void printList(CDblLinkedList CDLL);
int numMountainPairs(CDblLinkedList CDLL);

int main() {
    CDblLinkedList himalayas;
    himalayas.head = NULL;
    himalayas.size = 0;
    
    int item;
    int i, cases;
    int numP;
    
    scanf("%d", &cases);
    for (i = 0; i < cases; i++) {
        while (scanf("%d", &item)) {
            insertNode_AtFront(&himalayas, item);
        }
        scanf("%*s");
        
        numP = numMountainPairs(himalayas);
        printList(himalayas);
        printf("%d Pairs.\n", numP);
        
        deleteList(&himalayas);
    }
}

void insertNode_AtFront(CDblLinkedList *ptrCDLL, int value) {
    // Create a new node
    CDblListNode* newNode;
    newNode = (CDblListNode *) malloc(sizeof(CDblListNode));
    newNode->item = value;
    
    // First node
    if (ptrCDLL->size == 0) {
        newNode->next = newNode;
        newNode->pre = newNode;
        ptrCDLL->head = newNode;
    }
    else {
        newNode->next = ptrCDLL->head;
        newNode->pre = ptrCDLL->head->pre;
        
        // Update last node next link
        newNode->pre->next = newNode;
        ptrCDLL->head->pre = newNode;
        
        ptrCDLL->head = newNode;
    }
    ptrCDLL->size++;
}

void printList(CDblLinkedList CDLL) {
    if (CDLL.head == NULL) {
        return;
    }
    
    CDblListNode *temp = CDLL.head;
    printf("Current List: ");
    
    while (temp->next != CDLL.head) {
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("%d\n", temp->item);
}

void deleteList(CDblLinkedList *ptrCDLL) {
    if (ptrCDLL->head == NULL) {
        return;
    }
    CDblListNode *cur = ptrCDLL->head;
    CDblListNode *temp;
    
    while (cur->next != ptrCDLL->head) {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    
    free(cur);
    ptrCDLL->head = NULL;
    ptrCDLL->size = 0;
}

int numMountainPairs(CDblLinkedList CDLL) {
    int hmin = 0;
    int pair = 0;
    int totalPairs = 0;
    int outerLoop, innerLoop;
    int checkedFlag = 0;
    
    CDblListNode* curr = CDLL.head;
    CDblListNode* next = CDLL.head;
    CDblListNode* nextPlus = CDLL.head;
    CDblListNode* temp = CDLL.head;
    
    // Linked list count, where pairs = len + k
    int len = CDLL.size;
    
    if (len < 2) {
        return 0;
    }
    else if (len == 2) {
        return 1;
    }
    
    next = curr->next;
    
    for (outerLoop = 0; outerLoop < len; outerLoop++) {
        nextPlus = next->next;
        
        for (innerLoop = 0; innerLoop < (len - 3); innerLoop++) {
            checkedFlag = 0;
            temp = nextPlus;
            
            if (curr->item >= temp->item) {
                hmin = temp->item;
            }
            else {
                hmin = curr->item;
            }
            
            // Anti-clockwise
            while (temp != curr) {
                temp = temp->pre;
                
                if (hmin < temp->item) {
                    break;
                }
                if (temp->pre == curr) {
                    checkedFlag = 1;
                    break;
                }
            }
            
            temp = nextPlus;
            
            // Clockwise
            while (temp != curr) {
                temp = temp->next;
                
                if (hmin < temp->item) {
                    break;
                }
                if (temp->next == curr) {
                    checkedFlag = 1;
                    break;
                }
            }
            
            if (checkedFlag == 1) {
                pair += 1;
            }
            nextPlus = nextPlus->next;
        }
        
        curr = curr->next;
        next = curr->next;
    }
    
    // Divide by 2 since checking both directions
    totalPairs = len + (pair / 2);
    return totalPairs;
}

