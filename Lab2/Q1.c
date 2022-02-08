//
// NOT COMPLETED
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _listnode {
    char item;
    struct _listnode *next;
} ListNode;

typedef ListNode StackNode;
typedef ListNode QueueNode;

typedef struct _linkedList {
    int size;
    ListNode *head;
} Stack;

typedef struct _queue {
    int size;
    ListNode *head;
    ListNode *tail;
} Queue;

// Stack Interfacing Functions
void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);
void deleteStack(Stack *sPtr);

// Queue Interfacing Functions
void enqueue(Queue *qPtr, char item);
int dequeue(Queue *qPtr);
char getFront(Queue q);
char getBack(Queue q);
int isEmptyQueue(Queue q);
void deleteQueue(Queue *qPtr);

int palindrome(Queue *wordPtr);

int main() {
    char item;
    Queue word;
    word.head = NULL;
    word.tail = NULL;
    word.size = 0;
    
    printf("Enter a string of characters, terminated by a newline:\n");
    while (1) {
        scanf("%c", &item);
        if (item == '\n') {
            break;
        }
        enqueue(&word, item);
    }
    
    printf("The string is ");
    printf("%s", palindrome(&word)? "" : "not ");
    printf("a palindrome.\n");
}

void push(Stack *sPtr, char item) {
    StackNode *newNode;
    newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr) {
    if (sPtr == NULL || sPtr->head == NULL) {
        return 0;
    }
    else {
        StackNode *temp = sPtr->head;
        sPtr->head = sPtr->head->next;
        free(temp);
        sPtr->size--;
        return 1;
    }
}

char peek(Stack s) {
    return s.head->item;
}

int isEmptyStack(Stack s) {
    if (s.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void deleteStack(Stack *sPtr) {
    while(pop(sPtr));
}

void enqueue(Queue *qPtr, char item) {
    QueueNode *newNode;
    newNode = (QueueNode *) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->next = NULL;
    
    if (isEmptyQueue(*qPtr)) {
        qPtr->head = newNode;
    }
    else {
        qPtr->tail->next = newNode;
    }
    
    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    // If queue is empty or NULL pointer
    if (qPtr == NULL || qPtr->head == NULL) {
        return 0;
    }
    else {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        
        // If queue is empteied
        if (qPtr->head == NULL) {
            qPtr->tail = NULL;
        }
        
        free(temp);
        qPtr->size--;
        return 1;
    }
}

char getFront(Queue q) {
    return q.head->item;
}

char getBack(Queue q) {
    return q.tail->item;
}

int isEmptyQueue(Queue q) {
    if (q.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void deleteQueue(Queue *qPtr) {
    while(dequeue(qPtr));
}

int palindrome(Queue *wordPtr) {
    // LOOP 1, GO THROUGH STRING AND REMOVE SPACES
    // LOOP 2, SPLIT STRING INTO TWO HALVES
    // REVERSE SECOND HALF
    // COMPARE
    
    printf("Size of Queue is: %d\n", wordPtr->size);
    
    while (wordPtr != NULL) {
        char frontChar = getFront(*wordPtr);
        // char backChar = getBack(*wordPtr);
        
        printf("%c\n", frontChar);
        //printf("%c\n", backChar);
        
        dequeue(wordPtr);
    }
    
    return 1;
}
