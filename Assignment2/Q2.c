//
// Q2: Infix String to Prefix Expression Linked List
//
// Function converts an infix expression into a prefix expression linked list
//
// Example Input:
// 99+(88-77)*(66/(55-44)+33)
//
// Example Output:
// + 99 * - 88 77 + / 66 - 55 44 33
//

#include <stdio.h>
#include <stdlib.h>

#define SIZE 1000

enum ExpType {OPT, OPERAND};

typedef struct _stackNode {
    char item;
    struct _stackNode *next;
} StackNode;

typedef struct _stack {
    int size;
    StackNode *head;
} Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listNode {
    int item;
    enum ExpType type;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
    int size;
    ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item, enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList(LinkedList ll);

void in2PreLL(char *infix, LinkedList *inExpLL);
void printExpLL(LinkedList inExp);

int main() {
    char infix[SIZE];
    
    //printf("Enter an infix expression:\n");
    scanf("%[^\n]%*c", infix);
    
    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;
    
    in2PreLL(infix, &inExpLL);
    printExpLL(inExpLL);
    removeAllNodes(&inExpLL);
}

void printExpLL(LinkedList inExpLL) {
    ListNode *temp = NULL;
    temp = inExpLL.head;
    
    while (temp != NULL) {
        if (temp->type == OPERAND) {
            printf(" %d ", temp->item);
        }
        else {
            printf(" %c ", (char)(temp->item));
        }
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    
    if (newNode == NULL) {
        exit(0);
    }
    
    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head = newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if (LLPtr == NULL || LLPtr->size == 0) {
        return 0;
    }
    else {
        ListNode *temp = LLPtr->head;
        LLPtr->head = LLPtr->head->next;
        
        free(temp);
        LLPtr->size--;
        return 1;
    }
}

int isEmptyLinkedList(LinkedList ll) {
    if (ll.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

void removeAllNodes(LinkedList *LLPtr) {
    while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item) {
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
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

#include <strings.h>
#include <ctype.h>

int Gerald(char symbol) {
    switch(symbol) {
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 4;
        default:
            return 7;
    }
}

int Farquer(char symbol) {
    switch(symbol) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 3;
        default:
            return 8;
    }
}

void in2PreLL(char *infix, LinkedList *inExpLL) {
    int tempChr[SIZE];
    int count = 0;
    int total = 0;
    int j = 0;
    
    int prevIsOperandFlag = 0;
    
    unsigned long len = strlen(infix);
    //printf("LENGTH OF LEN %lu\n", len);
    
    for (j = 0; j < len; j++) {
        //printf("\n%c", infix[i]);
        
        if (isdigit(infix[j])) {
            //printf("ADDING TO TEMP %d, %d\n", ((int)infix[i] - 48), i);
            //printf("\nFIRST IF INDEX %d\n", i);
            tempChr[count] = ((int)infix[j] - 48);
            count++;
            
            prevIsOperandFlag = 1;
            //enqueue(&temp, ((int)infix[i] - 48), OPERAND);
        }
        else {
            //printf("FIRST ELSE INDEX %d\n", i);
            //printf("CALLING ELSE FUNCTION:\n");
            
            total = 0;
            for (int x = 0; x < count; x++) {
                total = (total * 10) + tempChr[x];
            }
            //printf("Count %d\n", count);
            
            if (prevIsOperandFlag == 1) {
                //printf("TOTAL: %d\n", total);
                insertNode(inExpLL, total, OPERAND);
                prevIsOperandFlag = 0;
            }
            insertNode(inExpLL, infix[j], OPT);
            
            count = 0; // This may be the bug
        }
    }
    if (prevIsOperandFlag == 1) {
        //printf("\nSECOND IF INDEX %d\n", i);
        
        total = 0;
        for (int x = 0; x < count; x++) {
            total = (total * 10) + tempChr[x];
        }
        
        //printf("Count %d\n", count);
        //printf("TOTAL 2: %d\n", total);
        insertNode(inExpLL, total, OPERAND);
        prevIsOperandFlag = 0;
    }
    
    
    // START OF INTERNET CODE
    int position = 0;
    int top; // top of stack pointer
    unsigned long length; // length of expression
    char symbol; // scanned character
    char temp; // when item popped from stack, keep in temp
    
    char arrayS[50]; // stack of type character
    char infixWeb[50], prefixWeb[50];
    
    int i, t1;
    top = -1;
    
    length = len;
    length = length - 1;
    position = length;
    t1 = length;
    
    char item;
    
    while (length >= 0) {
        symbol = infix[length];
        
        switch(symbol) {
            case ')':
                top = top + 1;
                arrayS[top] = symbol;
                break;
            case '(':
                item = arrayS[top];
                top = top - 1;
                temp = item;
                //temp = pop();
                
                while (temp != ')') {
                    prefixWeb[position] = temp;
                    position--;
                    item = arrayS[top];
                    top = top - 1;
                    temp = item;
                    //temp = pop();
                }
                if (temp != ')') {
                    item = arrayS[top];
                    top = top - 1;
                    temp = item;
                    //temp = pop();
                    prefixWeb[position--] = temp;
                }
                break;
            case '+':
            case '-':
            case '*':
            case '/':
                while (Farquer(arrayS[top]) >= Gerald(symbol)) {
                    item = arrayS[top];
                    top = top - 1;
                    temp = item;
                    //temp = pop();
                    prefixWeb[position] = temp;
                    position--;
                }
                
                top = top + 1;
                arrayS[top] = symbol;
                //push(symbol);
                break;
            default:
                prefixWeb[position--] = symbol;
                break;
        }
        length--;
    }
    
    while (arrayS[49] != '#') {
        item = arrayS[top];
        top = top - 1;
        temp = item;
        //temp = pop();
        prefixWeb[position--] = temp;
    }
    
    for (i = 0; i < t1; i++) {
        prefixWeb[i] = prefixWeb[i + position + 1];
    }
    
    printf("%s\n", prefixWeb);
}
