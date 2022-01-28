//
// Q4: Reverse Every K Nodes
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
void triPartition(ListNode **head, int pivot);

int main() {
    ListNode *head = NULL;
    ListNode *temp = NULL;
    
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
    
    triPartition(&head, pivot);
    printList(head);
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

void triPartition(ListNode **head, int pivot) {
    
}
