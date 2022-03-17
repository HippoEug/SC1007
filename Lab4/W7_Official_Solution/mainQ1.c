#include <stdio.h>
#include <stdlib.h>

typedef struct _btnode{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode;

void insertBSTNode(BTNode** cur, int item);
void printBTNode(BTNode *root, int space, int left);
void deleteTree(BTNode **root);

int main()
{
    BTNode* root = NULL;
    int item;

    printf("Enter a list of numbers for a Binary Tree, terminated by any non-digit character: \n");
    while(scanf("%d",&item))
        insertBSTNode(&root, item);
    scanf("%*s");

    printf("The Binary Search Tree:\n");
    printBTNode(root,0,0);

    deleteTree(&root);
    root=NULL;
    return 0;
}

void printBTNode(BTNode *root,int space,int left){
      if (root != NULL)
      {

          int i;
          for (i = 0; i < space-1; i++)
                 printf("|\t");


          if(i<space){
            if(left==1)
              printf("|---");
            else
              printf("|___");
          }

          printf("%d\n", root->item);

          space++;
          printBTNode(root->left, space,1);
          printBTNode(root->right, space,0);
      }
}

void deleteTree(BTNode **root){
    if (*root != NULL)
	{
		deleteTree(&((*root)->left));
		deleteTree(&((*root)->right));
		free(*root);
		*root = NULL;
	}
}

void insertBSTNode(BTNode** cur, int item){
    BTNode* temp = *cur;
    while(temp!=NULL){
        if(item < temp->item)
            if(temp->left==NULL)
               break;
            else
               temp = temp->left;
        else if(item > temp->item)
            if(temp->right==NULL)
               break;
            else
               temp = temp->right;
        else{
           printf("Duplicated Item: %d\n",item);
           return;
        }
    }

    BTNode* node = (BTNode*) malloc(sizeof(BTNode));
    node->item = item;
    node->left = node->right = NULL;

    if(*cur==NULL) //first node at the root
        *cur = node;
    else if(item < temp->item)
        temp->left = node;
    else
        temp->right = node;

    return;
}
