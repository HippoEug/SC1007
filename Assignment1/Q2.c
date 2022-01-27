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

void printList(LinkedList llist);
void deleteList(LinkedList *llptr);
LinkedList rearrange (LinkedList llist);

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
    
    printf("\nAFTER USER INPUT: \n"); // FOR DEBUG
    printList(llist); // FOR DEBUG
    
    llist = rearrange(llist);
    
    printf("\nAFTER REARRANGE: \n"); // FOR DEBUG
    printList(llist);
    deleteList(&llist);
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

LinkedList rearrange(LinkedList llist) {
    return llist;
}
