//
// Graph Representation: Adjacency List to Adjacency Matrix
//
// Convert an adjacency list to an adjacency matrix for an undirected graph
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
void adjL2adjM(Graph *);
void printGraphList(Graph );
void calDegreeV(Graph, int *);
void printDegreeV(int *, int );

int main() {
    Graph g;
    int i,j;

    int *degreeV;
    ListNode *temp;

    printf("Enter the number of vertices:\n");
    scanf("%d", &g.V);

    g.E = 0;
    g.adj.list = (ListNode **) malloc(g.V*sizeof(ListNode *));
    for (i = 0; i < g.V; i++) {
        g.adj.list[i] = NULL;
    }
    g.type = ADJ_LIST;

    degreeV = (int *) malloc(g.V*sizeof(int));
    for (i=0; i<g.V; i++) {
        degreeV[i]=0;
    }
    
    /*
    // ADDING CHEAT CODE TO TAKE INPUT AS MATRIX
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
    // END OF CHEAT CODE
    */

    int V1, V2;
    printf("Enter two vertices which are adjacent to each other (enter a to stop):\n");
    while (scanf("%d %d", &V1, &V2) == 2) {
        if ((V1 > 0) && (V1 <= g.V) && (V2 > 0) && (V2 <= g.V)) {
            /*
            // START OF CHEAT CODE TO TAKE INPUT AS MATRIX
            g.adj.matrix[V1-1][V2-1] = 1;
            g.adj.matrix[V2-1][V1-1] = 1;
            g.E++;
            // END OF CHEAT CODE
            */
            
            i = V1-1;
            j = V2-1;
            if (g.adj.list[i] == NULL) {
                    g.adj.list[i] = (ListNode *)malloc(sizeof(ListNode));
                    g.adj.list[i]->vertex = j+1;
                    g.adj.list[i]->next = NULL;
            }
            else {
                temp = (ListNode *)malloc(sizeof(ListNode));
                temp->vertex = j+1;
                temp->next =g.adj.list[i];
                g.adj.list[i] = temp;
            }
            if (g.adj.list[j] == NULL) {
                    g.adj.list[j] = (ListNode *)malloc(sizeof(ListNode));
                    g.adj.list[j]->vertex = i+1;
                    g.adj.list[j]->next = NULL;
            }
            else {
                temp = (ListNode *)malloc(sizeof(ListNode));
                temp->vertex = i+1;
                temp->next =g.adj.list[j];
                g.adj.list[j] = temp;
            }
            g.E++;
        }
        else {
            break;
        }
        printf("Enter two vertices which are adjacent to each other: (enter a to stop)\n");
    }

    adjL2adjM(&g);
    printGraphMatrix(g);
}

void printGraphMatrix(Graph g) {
    int i, j;
    if (g.type == ADJ_LIST) {
        printf("Error");
        return;
    }
    printf("Adjacency matrix:\n");
    for (i = 0; i < g.V; i++) {
        for (j = 0; j < g.V; j++) {
            printf("%d\t", g.adj.matrix[i][j]);
        }
        printf("\n");
    }
}

void adjL2adjM(Graph *g) {
    int i, j;
    int **matrix;
    ListNode *tempList = NULL;

    // if type of graph is already matrix
    if (g->type == ADJ_MATRIX) {
        printf("Error");
        return;
    }

    // if number of vertices less than or equals zero
    if (g->V <= 0) {
        printf("Empty graph!");
        return;
    }

    // Refering to Lab5 to init adjMatrix
    matrix = (int **)malloc(g->V*sizeof(ListNode*));
    for (i = 0; i < g->V; i++) {
        matrix[i] = (int *)malloc(g->V*sizeof(int));
    }
    for (i = 0; i < g->V; i++) {
        for (j = 0; j < g->V ;j++) {
            matrix[i][j] = 0;
        }
    }
    
    // iterate through each vertex's linked list
    for (i = 0; i < g->V; i++) {
        // iterate through each vertex linked list (temp) to check
        tempList = g->adj.list[i];
        while (tempList != NULL) { // go through linked list for each vertex until end of linked list
            //printf("tempList->vertex: %d, i+1: %d\n", tempList->vertex, i+1);
            matrix[(tempList->vertex)-1][i] = 1;
            matrix[i][(tempList->vertex)-1] = 1;
            tempList = tempList->next;
        }
    }

    g->adj.matrix = matrix;
    g->type = ADJ_MATRIX; // change representation form
}


void printGraphList(Graph g) {
    int i;
    ListNode* temp;

    if (g.type == ADJ_MATRIX) {
        printf("Error");
        return;
    }
    printf("Adjacency list:\n");
    for (i = 0; i < g.V; i++) {
        printf("%d:\t", i+1);
        temp = g.adj.list[i];
        while (temp != NULL) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}
