//
// TODO: free(Node);
//
#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
    int item;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
    ListNode *head;
    int size;
} LinkedList;

void printList2(LinkedList llist);
ListNode *findNode2(LinkedList llist, int index);
int insertNode2(LinkedList *llist, int index, int item);
void deleteList2(LinkedList *ptrHead);
int removeNode2(LinkedList *llist, int index);

int main() {
    LinkedList llist;
    llist.head = NULL;
    llist.size = 0;
    int item;
    int index;
    
    printf("Enter a list of numbers, terminated by any non-digit character: \n");
    while (scanf("%d", &item)) {
        if (!insertNode2(&llist, llist.size, item)) {
            break;
        }
    }
    scanf("%*s");
    printList2(llist);
    
    while (1) {
        printf("Enter the index of the node to be removed: ");
        scanf("%d", &index);
        
        if (!removeNode2(&llist, index)) {
            printf("The node cannot be removed.\n");
            break;
        }
        
        printf("After the removal operation, \n");
        printList2(llist);
    }
    printList2(llist);
    
    deleteList2(&llist);
}

void printList2(LinkedList llist) {
    ListNode *cur = llist.head;
    printf("Current List has %d elements: ", llist.size);
    
    while (cur != NULL) {
        printf("%d ", cur->item);
        cur = cur->next;
    }
    printf("\n");
}

ListNode *findNode2(LinkedList llist, int index) {
    ListNode *cur = llist.head;
    if (cur == NULL || index < 0 || index > llist.size) {
        return NULL;
    }
    
    while (index > 0) {
        cur = cur->next;
        if (cur == NULL) {
            return NULL;
        }
        index--; // ie index = 3, will loop 3 times to reach the index
    }
    return cur;
}

int insertNode2(LinkedList *llist, int index, int item) {
    ListNode *previousNode, *newNode;
    
    // If empty list or inserting first node, update head pointer
    if (index == 0) {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = llist->head;
        
        llist->head = newNode;
        llist->size++;
        return 1;
    }
    // Find the nodes before and at the target position
    // Create a new node and reconnect the links
    else if ((previousNode = findNode2(*llist, index-1)) != NULL) {
        newNode = malloc(sizeof(ListNode));
        newNode->item = item;
        newNode->next = previousNode->next;
        previousNode->next = newNode;
        llist->size++;
        return 1;
    }
    else {
        return 0;
    }
}

void deleteList2(LinkedList *llist) {
    while(removeNode2(llist, 0));
}

int removeNode2(LinkedList *llist, int index) {
    ListNode *tempNode, *previousNode;
    
    // If remove node at the front
    if (index == 0) {
        tempNode = llist->head;
        llist->head = tempNode->next;
        llist->size--;
        return 1;
    }
    // If remove node at the middle or end
    else if (findNode2(*llist, index) != NULL) {
        previousNode = findNode2(*llist, index-1);
        tempNode = previousNode->next;
        tempNode = tempNode->next;
        
        if (tempNode == NULL) {
            previousNode->next = NULL;
        }
        else {
            previousNode->next = tempNode;
        }
        llist->size--;
        return 1;
    }
    
    else {
        return 0;
    }
}
