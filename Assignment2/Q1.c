//
// Q1: Arithmetic Expression Queue
//
// Function split the operands, operators and paranthesis into a queue
// Infix: Character String
// inExpQ: Output Queue
//
// Example Input:
// 1+11*111/(1111-88)
//
// Example Output:
// 1 + 11 * 111 / ( 111 - 88 )
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 1000
enum ExpType {OPT, OPERAND};

typedef struct _queueNode {
    int item;
    enum ExpType type;
    struct _queueNode *next;
} QueueNode;

typedef struct _queue {
    int size;
    QueueNode *head;
    QueueNode *tail;
} Queue;

void enqueue(Queue *qPtr, int item, enum ExpType type);
int dequeue(Queue *qPtr);
QueueNode *getFront(Queue q);
int isEmptyQueue(Queue q);

void expressionQ(char *inflix, Queue *qPtr);
void printExpQ(Queue *qPtr);

int main() {
    char infix[SIZE];
    scanf("%[^\n]%*c", infix);
    
    Queue inExpQ;
    inExpQ.head = NULL;
    inExpQ.tail = NULL;
    inExpQ.size = 0;
    
    expressionQ(infix, &inExpQ);
    printf("Output:\n");
    printExpQ(&inExpQ);
}

void enqueue(Queue *qPtr, int item, enum ExpType type) {
    QueueNode *newNode;
    newNode = (QueueNode*) malloc(sizeof(QueueNode));
    newNode->item = item;
    newNode->type = type;
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
    if (qPtr == NULL || qPtr->head == NULL) {
        return 0;
    }
    else {
        QueueNode *temp = qPtr->head;
        qPtr->head = qPtr->head->next;
        
        if (qPtr->head == NULL) {
            qPtr->tail = NULL;
        }
        
        free(temp);
        qPtr->size--;
        return 1;
    }
}

QueueNode *getFront(Queue q) {
    return q.head;
}

int isEmptyQueue(Queue q) {
    if (q.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void printExpQ(Queue *qPtr) {
    if (qPtr == NULL) {
        return;
    }
    
    QueueNode *temp = NULL;
    temp = getFront(*qPtr);
    
    while (temp != NULL) {
        // If Operand
        if (temp->type == OPERAND) {
            printf(" %d ", temp->item);
        }
        // If Operator
        else {
            printf(" %c ", (char)(temp->item));
        }
        
        dequeue(qPtr);
        temp = getFront(*qPtr);
    }
    printf("\n");
}

void expressionQ(char *infix, Queue *qPtr) {
    Queue temp;
    temp.head = NULL;
    temp.tail = NULL;
    temp.size = 0;
    
    int tempChr[SIZE];
    int count = 0;
    
    unsigned long len = strlen(infix);
    //printf("LENGTH OF LEN %d\n", len);
    
    for (int i = 0; i < len; i++) {
        printf("%c\n", infix[i]);
        
        if (isdigit(infix[i])) {
            //printf("ADDING TO TEMP %d, %d\n", ((int)infix[i] - 48), i);
            tempChr[i] = ((int)infix[i] - 48);
            count++;
            //enqueue(&temp, ((int)infix[i] - 48), OPERAND);
        }
        else {
            //printf("CALLING ELSE FUNCTION:\n");
            
            int total = 0;
            for (int x = 0; x < count; x++) {
                total = (total * 10) + tempChr[x];
            }
            //printf("Hello %d\n", total);
            
            enqueue(qPtr, total, OPERAND);
            enqueue(qPtr, infix[i], OPT);
            
            count = 0;
        }
         
         
        /*
        if (isdigit(infix[i])) {
            enqueue(qPtr, ((int)infix[i] - 48), OPERAND);
            //enqueue(qPtr, infix[i], OPERAND);
        }
        else {
            enqueue(qPtr, infix[i], OPT);
        }
         */
    }
}
