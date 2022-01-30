//
// Q2: Rearrange Nodes
//
// Given a linked list of length N
// 1: Split into two halves, L (left) & R (right)
// 2: Rearrange as R L R L ..
// 3: Split into two halves again, L (left) & R (right)
// 4: Rearrange as L R L R ..
//
// If N is odd, keep it as last node
//
#include <stdio.h>
#include <stdlib.h>

typedef struct _listNode {
    int item;
    struct _listNode *next;
} ListNode;

typedef struct _linkedList {
    ListNode *head;
    int size;
} LinkedList;

void printListX(ListNode *head);
void printList(LinkedList llist);
void deleteList(LinkedList *llptr);

ListNode *findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);

void rearrange (LinkedList llist);

int main() {
    LinkedList llist;

    llist.head = NULL;
    llist.size = 0;
    
    ListNode *temp;
    temp = NULL; // Not in given code
    
    int i = 0;
    
    while (scanf("%d", &i)) {
        if (llist.head == NULL) {
            llist.head = (ListNode*) malloc(sizeof(ListNode));
            temp = llist.head;
        }
        else {
            temp->next = (ListNode*) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
        llist.size++;
    }
    temp->next = NULL;

    //llist = rearrange(llist);
    //printList(llist);
    
    rearrange(llist);
    //deleteList(&llist);
}

void printListX(ListNode *head) {
    while (head != NULL) {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

void printList(LinkedList llist) {
    ListNode *temp = llist.head;
    
    while (temp != NULL) {
        printf("%d ", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

void deleteList(LinkedList* llptr) {
    ListNode *cur = llptr->head;
    ListNode *temp;
    
    while (cur != NULL) {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    
    llptr->head = NULL;
    llptr->size = 0;
}

ListNode *findNode(ListNode *cur, int index) {
    if (cur == NULL || index < 0) {
        return NULL;
    }
    while (index > 0) {
        cur = cur->next;
        if (cur == NULL) {
            return NULL;
        }
        index--;
    }
    return cur;
}

int insertNode(ListNode **ptrHead, int index, int item) {
    ListNode *previousNode, *newNode;
    
    // If empty list or inserting first node, update head pointer
    if (index == 0) {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = *ptrHead;
        *ptrHead = newNode;
        return 1;
    }
    // Find the nodes before and at target position
    // Create a new node and reconnect the links
    else if ((previousNode = findNode(*ptrHead, index-1)) != NULL) {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = previousNode->next;
        previousNode->next = newNode;
        return 1;
    }
    else {
        return 0;
    }
}

void rearrange(LinkedList llist) {
    int listSize = llist.size;
    //printf("ListSize: %d\n", listSize);
    
    int halfSize = listSize/2;
    
    int splitLeftCounter = 0;
    int splitRightCounter = 0;
    int finalCounter = 0;
    
    ListNode *splitLeftOne = NULL;
    ListNode *splitRightOne = NULL;
    ListNode *splitOne = NULL;
    
    ListNode *splitLeftTwo = NULL;
    ListNode *splitRightTwo = NULL;
    ListNode *splitTwo = NULL;
    
    ListNode *temp = llist.head;
    
    ListNode *tempLeft = NULL;
    ListNode *tempRight = NULL;
    
    while (splitLeftCounter < halfSize && temp != NULL) {
        insertNode(&splitLeftOne, splitLeftCounter, temp->item);
        splitLeftCounter++;
        temp = temp->next;
    }
    
    while (splitRightCounter < (listSize - halfSize) && temp != NULL) {
        insertNode(&splitRightOne, splitRightCounter, temp->item);
        splitRightCounter++;
        temp = temp->next;
    }
    
    //printListX(splitLeftOne);
    //printListX(splitRightOne);
    
    tempLeft = splitLeftOne;
    tempRight = splitRightOne;
    
    while (finalCounter < listSize) {
        insertNode(&splitOne, finalCounter, tempRight->item);
        tempRight = tempRight->next;
        finalCounter++;
        
        if (tempLeft != NULL) {
            insertNode(&splitOne, finalCounter, tempLeft->item);
            tempLeft = tempLeft->next;
            finalCounter++;
        }
    }
    
    //printf("SPLIT ONE\n");
    //printListX(splitOne);
    //printf("\n");
    
    
    // SECOND SPLIT
    
    splitLeftCounter = 0;
    splitRightCounter = 0;
    finalCounter = 0;
    
    temp = splitOne;
    
    while (splitLeftCounter < halfSize && temp != NULL) {
        insertNode(&splitLeftTwo, splitLeftCounter, temp->item);
        splitLeftCounter++;
        temp = temp->next;
    }
    
    while (splitRightCounter < (listSize - halfSize) && temp != NULL) {
        insertNode(&splitRightTwo, splitRightCounter, temp->item);
        splitRightCounter++;
        temp = temp->next;
    }
    
    //printListX(splitLeftTwo);
    //printListX(splitRightTwo);
    
    tempLeft = splitLeftTwo;
    tempRight = splitRightTwo;
    
    while (finalCounter < listSize) {
        if (tempLeft != NULL) {
            insertNode(&splitTwo, finalCounter, tempLeft->item);
            tempLeft = tempLeft->next;
            finalCounter++;
        }
        
        insertNode(&splitTwo, finalCounter, tempRight->item);
        tempRight = tempRight->next;
        finalCounter++;
    }
    
    printListX(splitTwo);
    
    
    //return llist;
}
