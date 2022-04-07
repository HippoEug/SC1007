//
// Graph Connection (Directed Graph)
//
// Based on DFS algorithm, determine if an directed graph is strongly connected or not
// Vertices range from 1 to |V|
// May assume the graph is always valid
//
// Sample Input:
// 5
// 1 2
// 1 4
// 2 3
// 3 4
// 4 1
// 4 5
// a
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
    int vertex;
    struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph {
    int V;
    int E;
    int *visited; //store the visited vertices
    int **matrix;
} Graph;

typedef struct _linkedlist {
    int size;
    ListNode *head;
} Stack;

// You should not change the prototypes of these functions
// Stack
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
// Graph
void printGraphMatrix(Graph );
// You should not change the prototypes of these functions

int Connected(Graph);

int main() {
    Graph g;
    int i, j;
    
    printf("Enter the number of vertices:\n");
    scanf("%d", &g.V);

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for (i = 0; i < g.V; i++) {
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));
    }

    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++) {
            g.matrix[i][j] = 0;
        }
    }
    
    g.visited = (int *) malloc(sizeof(int)*g.V);
    for (i = 0; i < g.V; i++) {
        g.visited[i] = 0;
    }
    
    int V1, V2;
    printf("Enter a directed edge: (press a to stop)\n");
    while (scanf("%d %d", &V1, &V2) == 2) {
        if ((V1 > 0) && (V1 <= g.V) && (V2 > 0) && (V2 <= g.V)) {
            g.matrix[V1-1][V2-1] = 1;
            g.E++;
        }
        else {
            break;
        }
        printf("Enter a directed edge: (press a to stop)\n");
    }
    scanf("%*c");
    
    int res = Connected(g);
    if (res == 1) {
        printf("The graph is strongly connected.\n");
    }
    else {
        printf("The graph is not strongly connected.\n");
    }
}

int Connected(Graph g) {
    int vertexVisitedCounter = 0;
    int vertex;
    
    Stack s;
    s.size = 0;
    s.head = NULL;

    // to check if it is strongly connected
    // go through every single vertex one by one and see if it can reach every other vertex using count method
    for (int loop = 1; loop <= g.V; loop++) {
        // init counter and visited array back to zero
        vertexVisitedCounter = 0;
        for (vertex = 0; vertex < g.V; vertex++) {
            g.visited[vertex] = 0;
        }
        
        int v = loop;
        push(&s, v);
        g.visited[v - 1] = 1;
        vertexVisitedCounter++;
        
        while (isEmptyStack(s) != 1) { // while stack is not empty
            int stopNode = 0; // no unvisited vertices flag
            int w = peek(s); // peek the top of the stack
            
            for (vertex = 1; vertex <= g.V; vertex++) { // iterate through all the vertices one by one
                // if adjacent based on adjacency matrix, and vertex yet visited
                if (g.matrix[w-1][vertex-1] == 1 && g.visited[vertex-1] == 0) {
                    push(&s, vertex); // push vertex to stack
                    g.visited[vertex-1] = 1; // indicate that vertex already visited
                    vertexVisitedCounter++;
                    stopNode = 1; // flag to indicate no need to pop, just push to stack
                    break;
                }
            }
            if (stopNode == 0) { // flag to indicate there is no new vertice to visit since DFS
                pop(&s); // pop the top of the stack
            }
        }
        
        if (vertexVisitedCounter != g.V) {
            return 0;
        }
    }
    // if all vertices can reach every other vertex
    return 1;
}


void printGraphMatrix(Graph g) {
    int i, j;

    for(i = 0; i < g.V; i++) {
        for(j = 0; j < g.V; j++) {
            printf("%d\t", g.matrix[i][j]);
        }
        printf("\n");
    }
}

void push(Stack *sPtr, int vertex) {
    StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
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

int isEmptyStack(Stack s) {
    if (s.size == 0) {
        return 1;
    }
    else {
        return 0;
    }
}

int peek(Stack s) {
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr) {
    while(pop(sPtr));
}
