//
// Q3: Reverse Every K Nodes
//
// Given a linked list with input K
// Every K nodes form a segment
// Reverse the order of each K segment
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _listNode {
    int item;
    struct _listNode *next;
} ListNode;

void printList(ListNode *head);
void deleteList(ListNode **ptrHead);
void reverseKNodes(ListNode **head, int K, int itemCount);

int main() {
    ListNode *head = NULL, *temp = NULL;
    int i = 0;
    int K = 0;
    int itemCount = 0;
    
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
        
        itemCount++;
    }
    temp->next = NULL;
    
    printf("\nAFTER USER INPUT: \n"); // FOR DEBUG
    printList(head); // FOR DEBUG
    
    reverseKNodes(&head, K, itemCount);
    
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

void reverseKNodes(ListNode **head, int K, int itemCount) {
    ListNode *previousNode, *currentNode;
    ListNode *tempNode;
    ListNode *firstNode;

    int itemIndex = 0;
    
    tempNode = *head;
    
    for (int outerLoopCount = 0; outerLoopCount < ((int)(floor(itemCount/K))); outerLoopCount++) {
        printf("\nOUTER LOOP COUNT %d\n", outerLoopCount);
        if (itemIndex % K == 0) {
            printf("ITEM INDEX %d\n", itemIndex);
            // STEP 1
            previousNode = tempNode;
            //printf("%d", previousNode->item);
            
            if (outerLoopCount == 0) {
                firstNode = tempNode;
                printf("FIRST NODE ITEM: %d\n", firstNode->item);
            }
            else {
                //printf("%d\n", iterationCount);
                firstNode = firstNode->next;
                printf("FIRST NODE ITEM: %d\n", firstNode->item);
            }
            currentNode = tempNode;
            
            // STEP 2
            tempNode = tempNode->next;
            currentNode = tempNode;
            
            for (int innerLoopCount = 0; innerLoopCount < (K - 1); innerLoopCount++) {
                // STEP 3
                //printf("K - 1: %d, LoopCount: %d\n", K - 1, loopCount);
                //printf("%d\n", tempNode->item);
                
                tempNode = tempNode->next;
                currentNode->next = previousNode;
                
                // STEP 4
                previousNode = currentNode;
                currentNode = tempNode;
            }
            
            if (outerLoopCount == 0) {
                *head = previousNode;
            }
            
            //printf("%d", outerLoopCount);
            if (outerLoopCount != 0) {
                //printf("%d", tempNode->item);
                tempNode->next = firstNode; // BUGGY AF
            }
            firstNode->next = tempNode;
            
            
        }
        itemIndex++;
    }
    printf("\nFUNCTION ENDED\n");
}
