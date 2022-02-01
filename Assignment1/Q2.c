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
    ListNode *aTemp;
    
    ListNode *tempLeft = NULL;
    ListNode *tempRight = NULL;
    
    while (splitLeftCounter < halfSize && temp != NULL) {
        //insertNode(&splitLeftOne, splitLeftCounter, temp->item);
        if (splitLeftOne == NULL) {
            splitLeftOne = (ListNode*) malloc(sizeof(ListNode));
            aTemp = splitLeftOne;
        }
        else {
            aTemp->next = (ListNode*) malloc(sizeof(ListNode));
            aTemp = aTemp->next;
        }
        aTemp->item = temp->item;
        
        splitLeftCounter++;
        temp = temp->next;
    }
    
    while (splitRightCounter < (listSize - halfSize) && temp != NULL) {
        //insertNode(&splitRightOne, splitRightCounter, temp->item);
        if (splitRightOne == NULL) {
            splitRightOne = (ListNode*) malloc(sizeof(ListNode));
            aTemp = splitRightOne;
        }
        else {
            aTemp->next = (ListNode*) malloc(sizeof(ListNode));
            aTemp = aTemp->next;
        }
        aTemp->item = temp->item;
        
        splitRightCounter++;
        temp = temp->next;
    }
    
    //printListX(splitLeftOne);
    //printListX(splitRightOne);
    
    tempLeft = splitLeftOne;
    tempRight = splitRightOne;
    
    while (finalCounter < listSize) {
        //insertNode(&splitOne, finalCounter, tempRight->item);
        if (splitOne == NULL) {
            splitOne = (ListNode*) malloc(sizeof(ListNode));
            aTemp = splitOne;
        }
        else {
            aTemp->next = (ListNode*) malloc(sizeof(ListNode));
            aTemp = aTemp->next;
        }
        aTemp->item = tempRight->item;
        
        
        tempRight = tempRight->next;
        finalCounter++;
        
        if (tempLeft != NULL) {
            //insertNode(&splitOne, finalCounter, tempLeft->item);
            if (splitOne == NULL) {
                splitOne = (ListNode*) malloc(sizeof(ListNode));
                aTemp = splitOne;
            }
            else {
                aTemp->next = (ListNode*) malloc(sizeof(ListNode));
                aTemp = aTemp->next;
            }
            aTemp->item = tempLeft->item;
            
            
            
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
        //insertNode(&splitLeftTwo, splitLeftCounter, temp->item);
        if (splitLeftTwo == NULL) {
            splitLeftTwo = (ListNode*) malloc(sizeof(ListNode));
            aTemp = splitLeftTwo;
        }
        else {
            aTemp->next = (ListNode*) malloc(sizeof(ListNode));
            aTemp = aTemp->next;
        }
        aTemp->item = temp->item;
        
        splitLeftCounter++;
        temp = temp->next;
    }
    
    while (splitRightCounter < (listSize - halfSize) && temp != NULL) {
        //insertNode(&splitRightTwo, splitRightCounter, temp->item);
        if (splitRightTwo == NULL) {
            splitRightTwo = (ListNode*) malloc(sizeof(ListNode));
            aTemp = splitRightTwo;
        }
        else {
            aTemp->next = (ListNode*) malloc(sizeof(ListNode));
            aTemp = aTemp->next;
        }
        aTemp->item = temp->item;
        
        splitRightCounter++;
        temp = temp->next;
    }
    
    //printListX(splitLeftTwo);
    //printListX(splitRightTwo);
    
    tempLeft = splitLeftTwo;
    tempRight = splitRightTwo;
    
    while (finalCounter < listSize) {
        if (tempLeft != NULL) {
            //insertNode(&splitTwo, finalCounter, tempLeft->item);
            if (splitTwo == NULL) {
                splitTwo = (ListNode*) malloc(sizeof(ListNode));
                aTemp = splitTwo;
            }
            else {
                aTemp->next = (ListNode*) malloc(sizeof(ListNode));
                aTemp = aTemp->next;
            }
            aTemp->item = tempLeft->item;
            
            
            
            
            tempLeft = tempLeft->next;
            finalCounter++;
        }
        
        //insertNode(&splitTwo, finalCounter, tempRight->item);
        if (splitTwo == NULL) {
            splitTwo = (ListNode*) malloc(sizeof(ListNode));
            aTemp = splitTwo;
        }
        else {
            aTemp->next = (ListNode*) malloc(sizeof(ListNode));
            aTemp = aTemp->next;
        }
        aTemp->item = tempRight->item;
        
        tempRight = tempRight->next;
        finalCounter++;
    }
    
    printListX(splitTwo);
    
    deleteList(&llist);
    //return llist;
}
