//
// Q3: Reverse Every K Nodes
//
// Given a linked list with input K
// Every K nodes form a segment
// Reverse the order of each K segment
//
#include <stdio.h>
#include <stdlib.h>

typedef struct _listNode {
    int item;
    struct _listNode *next;
} ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);
void reverseKNodes(ListNode **head, int K);

int main() {
    ListNode *head = NULL, *temp = NULL;
    int i = 0;
    int K = 0;
    
    scanf("%d", &K);
    
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
    
    printf("\nAFTER USER INPUT: \n"); // FOR DEBUG
    printList(head); // FOR DEBUG
    
    reverseKNodes(&head, K);
    
    printf("\nAFTER REVERSING: \n"); // FOR DEBUG
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

void reverseKNodes(ListNode **head, int K) {
    printf("Hello World");
}
