// Lab 5 Q1
//
// Sample Input:
// 1 3 2 1 2 2 2 3 2 4 2 5 2 6 2 7 2 8 2 9 3 9 3 10 4 5
//
// Sample Output: (At the end)
// Enter selection: Enter a key to be deleted:
// 11 is not existing.
// Enter selection:
// 0:  9 -> 6 -> 3 ->
// 1:  7 -> 4 -> 1 ->
// 2:  8 -> 5 -> 2 ->
//

#include <stdio.h>
#include <stdlib.h>

typedef struct _listnode {
    int key;
    struct _listnode *next;
} ListNode;

typedef struct _linkedlist {
    int size;
    ListNode *head;
} HashTableNode;

typedef struct _hashTable {
    int hSize; //size of hash table
    int nSize; //number of inserted keys
    HashTableNode *Table;
} HashTable;

int Hash(int,int);

ListNode *HashSearch(HashTable Q3Hash, int key);
int HashInsert(HashTable *Q3HashPtr, int key);

//In Practice, we will not do it
void HashPrint(HashTable);

int main() {
    int opt;

    int i;
    int key;

    //Create a HashTable
    HashTable Q3Hash;
    Q3Hash.hSize = 0;
    Q3Hash.nSize = 0;
    Q3Hash.Table = NULL;

    printf("============= Hash Table ============\n");
    printf("|1. Create a hash table             |\n");
    printf("|2. Insert a key to the hash table  |\n");
    printf("|3. Search a key in the hash table  |\n");
    printf("|4. Print the hash table            |\n");
    printf("|5. Quit                            |\n");
    printf("=====================================\n");

    printf("Enter selection: ");
    scanf("%d",&opt);
    while ((opt >= 1) && (opt <= 4)) {
        switch (opt) {
            case 1: {
                printf("Enter the size of hash table:\n");
                scanf("%d", &Q3Hash.hSize);

                Q3Hash.nSize = 0;

                Q3Hash.Table = (HashTableNode *) malloc(sizeof(HashTableNode)*(Q3Hash.hSize));

                for (i = 0; i < Q3Hash.hSize; i++) {
                   Q3Hash.Table[i].head = NULL;
                   Q3Hash.Table[i].size = 0;
                }
                printf("HashTable is created.\n");
                break;
            }
            case 2: { //Insertion
                printf("Enter a key to be inserted:\n");
                scanf("%d", &key);

                if (HashInsert(&Q3Hash, key))
                    printf("%d is inserted.\n", key);
                else {
                    printf("%d is a duplicate. No key is inserted.\n", key);
                }
                break;
            }
            case 3: { //Search
                printf("Enter a key for searching in the HashTable:\n");
                scanf("%d", &key);
                ListNode *node = HashSearch(Q3Hash, key);

                if (node != NULL) {
                    printf("%d is found.\n", key);
                }
                else {
                    printf("%d is not found.\n", key);
                }
                break;
            }
            case 4: {
                HashPrint(Q3Hash);
                break;
            }
        }

        printf("Enter selection: ");
        scanf("%d", &opt);
    }

    for (i = 0; i < Q3Hash.hSize; i++) {
        while (Q3Hash.Table[i].head) {
            ListNode *temp;
            temp = Q3Hash.Table[i].head;
            Q3Hash.Table[i].head = Q3Hash.Table[i].head->next;
            free(temp);
        }
    }
    free(Q3Hash.Table);
}

int Hash(int key, int hSize) {
    return key%hSize;
}

ListNode *HashSearch(HashTable Q3Hash, int key) {
    int hashIndex = Hash(key, Q3Hash.hSize);
    ListNode *getNode = Q3Hash.Table[hashIndex].head;

    while (getNode) {
        if (getNode->key == key) {
            return getNode;
        }
        getNode = getNode->next;
    }

    return NULL; // if cannot find key
}

int HashInsert(HashTable *Q3HashPtr, int key) {
    // If key not exist
    if (HashSearch(*Q3HashPtr, key) == NULL) {
        int hashIndex = Hash(key, Q3HashPtr->hSize);
        
        ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
        newNode->key = key;
        newNode->next = Q3HashPtr->Table[hashIndex].head; // append to the front of LL
        
        Q3HashPtr->Table[hashIndex].head = newNode; // new node is new head
        Q3HashPtr->Table[hashIndex].size++; // increase table size
        Q3HashPtr->nSize++; // increase number of keys size
        
        return 1;
    }
    // If key already exists
    else {
        return 0;
    }
}

void HashPrint(HashTable Q3Hash) {
    int i;
    ListNode *temp;
    
    for(i = 0; i < Q3Hash.hSize; i++) {
        temp = Q3Hash.Table[i].head;
        printf("%d:  ", i);
        
        while(temp != NULL) {
            printf("%d -> ", temp->key);
            temp = temp->next;
        }
        printf("\n");
    }
}

