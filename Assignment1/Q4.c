//
// Q4: Tri-Partition
//
// Given a linked list and a pivot
// Move numbers less than pivot to the front
// Move numbers same as pivot to the middle
// Move the rest of the numbers to the back
//
#include <stdio.h>
#include <stdlib.h>

typedef struct _listNode {
    int item;
    struct _listNode *next;
} ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);

ListNode *findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);

void triPartition(ListNode **head, ListNode **newHead, int pivot);

int main() {
    ListNode *head = NULL;
    ListNode *temp = NULL;
    
    ListNode **newHead = NULL;
    
    int i = 0;
    int pivot = 0;
    
    scanf("%d", &pivot);
    
    while (scanf("%d", &i)) {
        if (head == NULL) {
            head = (ListNode*) malloc(sizeof(ListNode));
            temp = head;
        }
        else {
            temp->next = (ListNode*) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = i;
    }
    temp->next = NULL;
    
    triPartition(&head, &newHead, pivot);
    printList(newHead);
    deleteList(&head);
}

void printList(ListNode *head) {
    while (head != NULL) {
        printf("%d ", head->item);
        head = head->next;
    }
    printf("\n");
}

void deleteList(ListNode **ptrHead) {
    ListNode *cur = *ptrHead;
    ListNode *temp;
    
    while (cur != NULL) {
        temp = cur->next;
        free(cur);
        cur = temp;
    }
    *ptrHead = NULL;
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

void triPartition(ListNode **head, ListNode **newHead, int pivot) {
    ListNode *lessThanPivot = NULL;
    ListNode *equalPivot = NULL;
    ListNode *moreThanPivot = NULL;
    ListNode *currNode = NULL;
    
    currNode = *head;
    
    int lessThanCount = 0;
    int equalCount = 0;
    int moreThanCount = 0;
    
    while (currNode != NULL) {
        // printf("%d\n", currNode->item); // FOR DEBUG
        if ((currNode->item) < pivot) {
            // rintf("Function Less Than %d %d\n", lessThanCount, currNode->item);
            
            insertNode(&lessThanPivot, lessThanCount, currNode->item);
            lessThanCount++;
        }
        else if ((currNode->item) == pivot) {
            // printf("Function Equal: %d %d\n", equalCount, currNode->item); // FOR DEBUG
            
            insertNode(&equalPivot, equalCount, currNode->item);
            equalCount++;
        }
        else if ((currNode->item) > pivot) {
            // printf("Function More Than: %d %d\n", moreThanCount, currNode->item); // FOR DEBUG
            
            insertNode(&moreThanPivot, moreThanCount, currNode->item);
            moreThanCount++;
        }
        
        currNode = currNode->next;
    }
    
    // printList(lessThanPivot);
    // printList(equalPivot);
    // printList(moreThanPivot);
    //printList(*head);
    
    int i = 0;
    int j = 0;
    int totalCount = lessThanCount + equalCount + moreThanCount;
    
    while (i < totalCount) {
        for (j = 0; j < lessThanCount; j++) {
            // printf("FINAL L1: %d\n", lessThanPivot->item);
            insertNode(newHead, i, lessThanPivot->item);
            lessThanPivot = lessThanPivot->next;
            i++;
        }
        for (j = 0; j < equalCount; j++) {
            // printf("FINAL L2: %d\n", equalPivot->item);
            insertNode(newHead, i, equalPivot->item);
            equalPivot = equalPivot->next;
            i++;
        }
        for (j = 0; j < moreThanCount; j++) {
            // printf("FINAL L3: %d\n", moreThanPivot->item);
            insertNode(newHead, i, moreThanPivot->item);
            moreThanPivot = moreThanPivot->next;
            i++;
        }
    }
    //printList(*newHead);
    //insertNode(head, totalCount, NULL);
}
