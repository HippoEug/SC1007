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

void in2PreLL(char* infix, LinkedList *inExpLL) {
    // Operands
    char temp;
    int opr = 0;
    int oprWeight = 1;
    
    // Operators
    Stack opt;
    opt.head = NULL;
    opt.size=0;
    
    // Operand Weight Management
    int currentOpr;
    int previousOpr;
    
    // Count string length
    int stringLength = 0;
    char tempChar = infix[0];
    while (tempChar != '\0') {
        stringLength++;
        tempChar = infix[stringLength];
    }
    
    // Reversed from the back
    for (int i = (stringLength - 1); i >= 0; i--) {
        temp = infix[i];
        //printf("temp %c\n", temp);

        // If Operand Opr
        if ('0' <= temp && temp <= '9') {
            //printf("HELLO %c\n", temp);
            
            // Concetanate digits
            //printf("opr %d, temp %d, oprCount %d\n", opr, temp - '0', oprCount);
            opr = opr + ((temp - '0') * oprWeight);
            oprWeight = oprWeight*10;
        }
        // Else if Operator Opt
        else {
            //printf("BYE %c\n", temp);

            // Prevent 0 from being appended
            if (opr > 0){
                // Push operand into queue
                insertNode(inExpLL, opr, OPERAND);
                
                oprWeight = 1;
                opr = 0;
            }
        
            // Sort Operator Stack
            if (temp == '+' || temp == '-') {
                if (!isEmptyStack(opt)) {
                    
                    // Get currentOpr
                    if (temp == '+' || temp == '-') {
                        currentOpr = 1;
                    }
                    else if (temp == '/' || temp == '*') {
                        currentOpr = 2;
                    }
                    else {
                        currentOpr = -1;
                    }
                    
                    // Get previousOpr from Stack
                    if (peek(opt) == '+' || peek(opt) == '-') {
                        previousOpr = 1;
                    }
                    else if (peek(opt) == '/' || peek(opt) == '*') {
                        previousOpr = 2;
                    }
                    else {
                        previousOpr = -1;
                    }
                    
                    // Compare both operators
                    while (currentOpr < previousOpr){
                        insertNode(inExpLL,peek(opt), OPT);
                        pop(&opt);
                        
                        if (isEmptyStack(opt)) {
                            break;
                        }
                        else {
                            // Get previousOpr from Stack
                            if (peek(opt) == '+' || peek(opt) == '-') {
                                previousOpr = 1;
                            }
                            else if (peek(opt) == '/' || peek(opt) == '*') {
                                previousOpr = 2;
                            }
                            else {
                                previousOpr = -1;
                            }
                        }
                    }
                }
                push(&opt, temp);
            }
            else if (temp == '(') {
                while (peek(opt) != ')') {
                    insertNode(inExpLL, peek(opt), OPT);
                    pop(&opt);
                }
                pop(&opt);
            }
            else {
                push(&opt, temp);
            }
        }

        // printExpLL(*inExpLL);
    }

    // Clear remaining operands at the "front"
    if (opr > 0){
        insertNode(inExpLL, opr, OPERAND);
        
        oprWeight = 1;
        opr = 0;
    }
    
    // Clear remaining operators at the "front"
    while (!isEmptyStack(opt)) {
        insertNode(inExpLL, peek(opt), OPT);
        pop(&opt);
    }
}

