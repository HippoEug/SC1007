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
// 546271983 (might be wrong)
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

BTNode *insertBTNode(BTNode *cur, int item, int leftFlag);
void buildTree(BTNode **node, char *preO, char *postO);
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

BTNode *insertBTNode(BTNode *cur, int item, int leftFlag) {
    if (cur == NULL){
        BTNode* node = (BTNode*) malloc(sizeof(BTNode));
        node->id = item;
        node->left = node->right = NULL;
        return node;
    }
    
    if (leftFlag == 1) {
        cur->left  = insertBTNode (cur->left, item, leftFlag);
    }
    else {
        cur->right = insertBTNode (cur->right, item, leftFlag);
    }
    
    return cur;
}

void findRightMost(char curChar, char *preO, char *postO) {
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
    
    
}

void buildTree(BTNode **node, char *preO, char *postO) {
    BTNode *cur = NULL;
    
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
    printf("Length of string is %d (preO), %d (postO)\n", preOLength, postOLength);
    
    // Initialize root node
    *node = insertBTNode(*node, preO[0], 0);
    
    // Initialize 1st left node
    *node = insertBTNode(*node, preO[1], 1);
    
    
    for (int i = 2; i < preOLength; i++) {
        //printf("%c", preO[i]);
        
        findRightMost(preO[i], preO, postO);
    }
    
    
    
    printf("\npreO:\n");
    for (int i = 0; i < preOLength; i++) {
        printf("%c", preO[i]);
    }
    printf("\n");
    
    printf("postO:\n");
    for (int i = 0; i < postOLength; i++) {
        printf("%c", postO[i]);
    }
    printf("\n");
    
    printf("\nRESULTS BELOW\n");

    // 3. recursive function - yes you need to call this function again and again

    // 4. find your left subtree nodes
    // HINT: how do you determine the root node for the left subtree
    // HINT: how do you determine the number of nodes for left subtree

    // 5. create new preO and postO for the left subtree and do the recursive for left subtree
    // HINT: when you don't have strcpy() from string.h, then how do you get substrings?
    // HINT: create your own helper function to create substring? maybe?

    // 6. repeat steps 4 and 5 for the right subtree
    // HINT: what if right subtree doesn't exist? e.g. preO = '5 6' postO = '6 5'
}
