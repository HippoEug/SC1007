//
// CONSTRUCT A BINARY TREE
//
// Given valid preorder & postorder traversal strings,
// write a function to reconstruct the binary tree.
// The id of each node is a unique character.
// If any node has only one child, the child node must be on the left.
//
// ie Input 1
// 124567389 (preorder traversal string)
// 564729831 (postorder traversal string)
//
// ie Output 1
// 124567389
// 564729831
// 546271983
//
// ie Input 2
// 124567389ABC
// 56472BCA9831
//
// ie Output 2
// 124567389ABC
// 56472BCA9831
// 546271BAC983
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_N 120

typedef struct _btnode {
    char id;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

BTNode *insertBTNode(int item);
void buildTree(BTNode **node, char *preO, char *postO);
BTNode *build(char *preO, char *postO, int *preIndex, int l, int h, int size);

void inOrder(BTNode *cur);
void preOrder(BTNode *cur);
void postOrder(BTNode *cur);

int main() {
    char preO[MAX_N];
    char postO[MAX_N];
    scanf("%s", preO);
    scanf("%s", postO);
    
    BTNode *root = NULL;
    buildTree(&root, preO, postO);
    
    if (root == NULL) {
        printf("error\n");
    }
    
    preOrder(root);
    printf("\n");
    postOrder(root);
    printf("\n");
    inOrder(root);
    printf("\n");
}

void inOrder(BTNode *cur) {
    if (cur == NULL) {
        return;
    }
    
    inOrder(cur->left);
    printf("%c", cur->id);
    inOrder(cur->right);
}

void preOrder(BTNode *cur) {
    if (cur == NULL) {
        return;
    }
    
    printf("%c", cur->id);
    preOrder(cur->left);
    preOrder(cur->right);
}

void postOrder(BTNode *cur) {
    if (cur == NULL) {
        return;
    }
    
    postOrder(cur->left);
    postOrder(cur->right);
    printf("%c", cur->id);
}

BTNode *insertBTNode(int item) {
    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    node->id = item;
    node->left = node->right = NULL;
    return node;
}

BTNode *build(char *preO, char *postO, int *preIndex, int l, int h, int size) {
    if (*preIndex >= size || l > h) {
        return NULL;
    }
    
    BTNode* root = insertBTNode(preO[*preIndex]);
    ++*preIndex;
    
    if (l == h) {
        return root;
    }
    
    int i;
    for (i = l; i <= h; ++i) {
        if (preO[*preIndex] == postO[i]) {
            break;
        }
    }
    
    if (i <= h) {
        root->left = build(preO, postO, preIndex, l, i, size);
        root->right = build(preO, postO, preIndex, i + 1, h - 1, size);
    }
    
    return root;
}

void buildTree(BTNode **node, char *preO, char *postO) {
    // Get length of preO and postO strings
    int preOLength = 0;
    int postOLength = 0;
    while (preO[preOLength] != '\0') {
        preOLength++;
    }
    while (postO[postOLength] != '\0') {
        postOLength++;
    }
    if (preOLength != postOLength) {
        return;
    }
    //printf("Length of string is %d (preO), %d (postO)\n", preOLength, postOLength);
    
    int preIndex = 0;
    *node = build(preO, postO, &preIndex, 0, preOLength - 1, preOLength);
    
    //printf("\nRESULTS BELOW\n");
}
