//
// Q1: Reverse Nodes from A to B
//
// Given a linked list & a start and end index
// Index range from 0 to size of (linked list - 1)
// Reverse nodes of linked list from start to end index
//
#include <stdio.h>
#include <stdlib.h>

typedef struct _listNode {
    float item;
    struct _listNode *next;
} ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);
ListNode *reverseSegment(ListNode *head, int start, int end);

int main() {
    ListNode *head = NULL;
    ListNode *temp = NULL;
    
    float f = 0.0;
    int startIndex, endIndex;
    
    scanf("%d %d", &startIndex, &endIndex);
    while (scanf("%f", &f)) {
        if (head == NULL) {
            head = (ListNode*) malloc(sizeof(ListNode));
            temp = head;
        }
        else {
            temp->next = (ListNode*) malloc(sizeof(ListNode));
            temp = temp->next;
        }
        temp->item = f;
    }
    temp->next = NULL;
    
    /*
    printf("\nAFTER USER INPUT:\n"); // FOR DEBUG
    printList(head); // FOR DEBUG
    */
    
    head = reverseSegment(head, startIndex, endIndex);
    
    /*
    printf("\nAFTER REVERSE FUNCTION:\n"); // FOR DEBUG
    */
    
    printList(head);
    deleteList(&head);
}

void printList(ListNode *head) {
    while (head != NULL) {
        printf("%.2f ", head->item);
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

ListNode *reverseSegment(ListNode *head, int start, int end) {
    ListNode *beforeStartIndex, *originalStartIndex;
    ListNode *previousNode, *currentNode;
    ListNode *returningIndex;
    
    int originalStart = start;

    if (head == NULL || start < 0 || end < 0) {
        return head;
    }
    
    int diff = end - start;
    
    returningIndex = head;
    
    /*
    printf("\nreturningIndex->item: %f\n", returningIndex->item);
    printf("\nhead->item: %f\n", head->item); // debug
    */
    
    // Step 1: Moving head pointer to the (start index - 1)
    if (start > 1) {
        while (start > 1) {
            head = head->next;
            
            /*
            printf("\nhead->item: %f\n", head->item); // debug
            printf("\nHELLOreturningIndex->item: %f\n", returningIndex->item);
            */
            
            if (head == NULL) {
                return NULL;
            }
            start--;
        }
    }
    
    beforeStartIndex = head;
    
    /*
    printf("\nbeforeStartIndex->item: %f\n", beforeStartIndex->item); // debug
    */
    
    // Step 2
    head = head->next;
    originalStartIndex = head;
    previousNode = head;
    currentNode = head;
    
    // Step 3
    head = head->next;
    currentNode = head;
    
    while (diff > 0) {
        // Step 4
        head = head->next;
        currentNode->next = previousNode;
        
        // Step 5
        previousNode = currentNode;
        currentNode = head;
        
        diff--;
    }
    
    originalStartIndex->next = head;
    beforeStartIndex->next = previousNode;
    
    //return returningIndex;
    
    
    if (originalStart > 0) {
        return returningIndex;
    }
    
    else {
        return previousNode;
    }
     
}
