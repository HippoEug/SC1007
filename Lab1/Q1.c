//
// TODO: free(Node);
//
//
// TODO: free(Node);
//
#include <stdio.h>
#include <stdlib.h>

// Node that contains the actual item and the address of the next node
typedef struct _listnode {
    int item;
    struct _listnode *next;
} ListNode;

void printList(ListNode *cur);
ListNode *findNode(ListNode *cur, int index);
int insertNode(ListNode **ptrHead, int index, int item);
void deleteList(ListNode **ptrHead);
int removeNode(ListNode **ptrHead, int index);

int main() {
    ListNode *head = NULL;
    int size = 0;
    int item;
    int index;
    
    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while (scanf("%d", &item)) {
        if (insertNode(&head, size, item)) {
            size++;
        }
    }
    scanf("%*s");
    
    printList(head);
    
    while(1) {
        printf("Enter the index of the node to be removed: ");
        scanf("%d", &index);
        
        if (removeNode(&head, index)) {
            size--;
        }
        else {
            printf("The node cannot be removed. \n");
            break;
        }
        
        printf("After the removal operation, \n");
        printList(head);
    }
    
    printList(head);
    deleteList(&head);
}

void printList(ListNode *cur) {
    printf("Current List: ");
    while (cur != NULL) {
        printf("%d ", cur->item); // Current pointer points to actual data
        cur = cur->next; // Current pointer points to address of next node
    }
    printf("\n");
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

void deleteList(ListNode **ptrHead) {
    while(removeNode(ptrHead, 0));
}

int removeNode(ListNode **ptrHead, int index) {
    ListNode *tempNode, *previousNode;
    
    // If remove node at the front
    if (index == 0) {
        // tempNode->next for iterating to next node
        tempNode = *ptrHead;
        *ptrHead = tempNode->next;
        return 1;
    }
    // If remove node at middle or end
    else if (findNode(*ptrHead, index) != NULL) {
        previousNode = findNode(*ptrHead, index-1);
        // tempnode->next for iterating to next node
        tempNode = previousNode->next;
        tempNode = tempNode->next;
        
        if (tempNode == NULL) { // If remove node is the last node
            previousNode->next = NULL;
        }
        else {
            previousNode->next = tempNode;
        }
        
        return 1;
    }
    else {
        return 0;
    }
}
