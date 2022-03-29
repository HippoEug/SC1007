//
// Graph: Degree of a Vertex
//
// Degree of vertex v in a graph is the number of edges incident on v
// Write function calDegreeV() to compute number of degrees using adjacency matrix
//
// Sample Input:
// 7
// 1 2
// 1 3
// 2 3
// 2 4
// 4 1
// 4 3
// 4 6
// 5 3
// 5 7
// a
//
// Sample Output:
//
//

#include <stdio.h>
#include <stdlib.h>

// Types of Graph Representation
enum GraphType {ADJ_MATRIX, ADJ_LIST};

typedef struct _listnode {
    int vertex;
    struct _listnode *next;
} ListNode;

struct GraphForm {
    int **matrix;
    ListNode **list;
};

typedef struct _graph {
    int V; // vertices
    int E; // edges
    enum GraphType type;
    struct GraphForm adj;
} Graph;

void printGraphMatrix(Graph );
void adjMatrixToAdjList(Graph *);
void calDegreeV(Graph, int *);
void printDegreeV(int *, int );

int main() {
    Graph g;
    int i, j;

    int *degreeV;

    printf("Enter the number of vertices:\n");
    scanf("%d", &g.V);

    // Space allocation of adjacency matrix
    g.E = 0;
    g.adj.matrix = (int **)malloc(g.V*sizeof(int *));
    for (i = 0; i < g.V; i++) {
        g.adj.matrix[i] = (int *)malloc(g.V*sizeof(int));
    }

    // Initializing adjacency matrix
    for (i=0; i<g.V; i++) {
        for(j=0; j < g.V; j++) {
            g.adj.matrix[i][j] = 0;
        }
    }
    g.type = ADJ_MATRIX;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for (i=0; i < g.V; i++) {
        degreeV[i]=0;
    }

    // Filling in the adjacency matrix
    int V1, V2;
    printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    while (scanf("%d %d", &V1, &V2) == 2) {
        if ((V1 > 0) && (V1 <= g.V) && (V2 > 0) && (V2 <= g.V)) {
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
        }
        else {
            break;
        }
        printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    }


    printGraphMatrix(g);
    //adjMatrixToAdjList(&g);
    calDegreeV(g, degreeV);
    printDegreeV(degreeV, g.V);

    return 0;
}

void printGraphMatrix(Graph g) {
    int i, j;
    printf("Print graph matrix \n");
    if (g.type == ADJ_LIST) {
        printf("Error");
        return;
    }
    
    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++) {
            printf("%d\t", g.adj.matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void adjMatrixToAdjList(Graph *g) {
    int i,j;
    ListNode **list;
    ListNode *temp;

    if (g->type == ADJ_LIST) {
        printf("Error");
        return;
    }
    if (g->V <= 0) {
        printf("Empty graph!");
        return;
    }

    list = (ListNode **) malloc(g->V*sizeof(ListNode *));
    for (i = 0; i < g->V; i++) {
        list[i] = NULL;
    }

    for (i = 0; i < g->V; i++) {
        for(j = 0; j < g->V; j++) {
            if (g->adj.matrix[i][j] == 1) {
                if (list[i] == NULL) {
                    list[i] = (ListNode *)malloc(sizeof(ListNode));
                    list[i]->vertex = j+1;
                    list[i]->next = NULL;
                    temp = list[i];
                }
                else {
                    temp->next = (ListNode *)malloc(sizeof(ListNode));
                    temp->next->vertex = j+1;
                    temp->next->next = NULL;
                    temp = temp->next;
                }
            }
        }
    }
    
    g->type = ADJ_LIST; //change representation form

    //free adjMatrix
    for(i = 0; i < g->V; i++) {
        free(g->adj.matrix[i]);
    }
    free(g->adj.matrix);

    g->adj.list = list;
}

void calDegreeV(Graph g, int *degreeV) {
    /*
    // Using Adjacency List to calculate Degrees
    int i;
    ListNode *temp = NULL;

    // iterate through each vertices one by one
    for (i = 0; i < g.V; i++) {
        degreeV[i] = 0;
     
        // iterate through each vertex linked list to count
        ListNode *temp = g.adj.list[i];
        while (temp != NULL) {
            degreeV[i]++;
            temp = temp->next;
        }
    }
    */
    
    // Using Adjacency Matrix to calculate Degrees
    int i,j;
    ListNode *temp = NULL;
    degreeV[i] = 0;

    // iterate through each vertices one by one
    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++) {
            ListNode *temp = g.adj.matrix[i][j];
            if (temp != NULL) {
                degreeV[i]++;
            }
            temp = temp->next;
        }
    }
}

void printDegreeV(int *degreeV, int V) {
    int i;
    printf("Print vertex's degree \n");
    for(i = 0; i < V; i++) {
        printf("%d: %d degree\n",i+1,degreeV[i]);
    }
}
