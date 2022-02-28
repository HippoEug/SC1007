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
// Credits: https://www.geeksforgeeks.org/full-and-complete-binary-tree-from-given-preorder-and-postorder-traversals/
// Credits: https://www.youtube.com/watch?v=5lWJpTEnyow
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
BTNode *build(char *preO, char *postO, int *preOIndex, int postOLowIndex, int postOHighIndex, int preOLength);

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

BTNode *build(char *preO, char *postO, int *preOIndex, int postOLowIndex, int postOHighIndex, int preOLength) {
    if ((postOLowIndex > postOHighIndex) || (*preOIndex >= preOLength)) {
        return NULL;
    }
    
    // Make first index of preO root
    BTNode* root = insertBTNode(preO[*preOIndex]);
    ++*preOIndex;
    
    // If only 1 element
    if (postOLowIndex == postOHighIndex) {
        return root;
    }
    
    // Find next element of preO in postO
    int nextElement;
    for (nextElement = postOLowIndex; nextElement <= postOHighIndex; nextElement++) {
        if (preO[*preOIndex] == postO[nextElement]) {
            break;
        }
    }
    
    // Divide postO into left and right subtree
    if (nextElement <= postOHighIndex) {
        root->left = build(preO, postO, preOIndex, postOLowIndex, nextElement, preOLength);
        root->right = build(preO, postO, preOIndex, (nextElement + 1), (postOHighIndex - 1), preOLength);
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
    
    // preOIndex for keeping track of index in preO
    int preOIndex = 0;
    // Calls recursive function to construct tree
    int postOLowIndex = 0;
    int postOHighIndex = preOLength - 1;
    *node = build(preO, postO, &preOIndex, postOLowIndex, postOHighIndex, preOLength);
    
    //printf("\nRESULTS BELOW\n");
}
