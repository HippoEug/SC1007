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
    
    //printf("\nAFTER USER INPUT: \n"); // FOR DEBUG
    //printList(head); // FOR DEBUG
    
    if (K != 0) {
        reverseKNodes(&head, K, itemCount);
    }
    
    //printf("\nAFTER REVERSING: \n"); // FOR DEBUG
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
    ListNode *tempNode, *secondNode;
    ListNode *firstNode;

    int itemIndex = 0;
    int outerLoopCount = 0;
    
    tempNode = *head;
    
    for (itemIndex = 0; itemIndex < itemCount; itemIndex++) {
        
        if (outerLoopCount >= (int)(floor(itemCount/K))) {
            //printf("outerLoopCount: %d, floor(itemCount/K): %d\n", outerLoopCount, (int)(floor(itemCount/K)));
            break;
        }
        
        if (itemIndex % K == 0) {
            //printf("\nouterLoopCount: %d\n", outerLoopCount);
            //printf("itemIndex: %d\n", itemIndex);
            
            // STEP 1
            previousNode = tempNode;
            //printf("tempNode S1: %d\n", tempNode->item);
            
            if (outerLoopCount == 0) {
                firstNode = tempNode;
                //printf("firstNode->item: %d\n", firstNode->item);
            }
            else {
                secondNode = tempNode;
                //printf("secondNode->item: %d\n", secondNode->item);
            }
            
            currentNode = tempNode;
            
            // STEP 2
            tempNode = tempNode->next;
            currentNode = tempNode;
            //printf("tempNode S2: %d\n", tempNode->item);
            
            for (int innerLoopCount = 0; innerLoopCount < (K - 1); innerLoopCount++) {
                // STEP 3
                tempNode = tempNode->next;
                currentNode->next = previousNode;
                //printf("tempNode S3: %d\n", tempNode->item);
                
                // STEP 4
                previousNode = currentNode;
                currentNode = tempNode;
                //printf("tempNode S4: %d\n", tempNode->item);
            }
            
            if (outerLoopCount == 0) {
                //printf("CHANGING HEAD\n");
                *head = previousNode;
            }
            
            if (outerLoopCount != 0) {
                //printf("PERFORMING firstNode->next = previousNode\n");
                //printf("DEBUG firstNode: %d\n", firstNode->item);
                //printf("DEBUG previousNode: %d\n", previousNode->item);
                firstNode->next = previousNode;
                
                firstNode = secondNode;
            }
            
            outerLoopCount++;
            
        }
    }
    
    firstNode->next = tempNode;
    //printf("\nFUNCTION ENDED\n");
}
