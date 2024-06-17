#include <stdio.h>

#include <stdlib.h>

struct node

{ 

struct node *left; 

int element; 

struct node *right; 

}; 

typedef struct node Node; 

Node *Insert(Node *Tree, int e); 

void Display(Node *Tree); 

Node *Delete(Node *Tree, int e); 

Node *FindMin(Node *Tree); 

int main() 

{ 

Node *Tree = NULL; 

int n, i, e; 

printf("Enter number of nodes in the tree : "); 

scanf("%d", &n); 

printf("Enter the elements :\n"); 

for (i = 1; i <= n; i++) 

 { 

 scanf("%d", &e); 

 Tree = Insert(Tree, e); 

 } 

printf("Tree elements in inorder :\n"); 

 Display(Tree); 

printf("\nEnter the element to delete : \n"); 

scanf("%d", &e); 

 Tree = Delete(Tree, e); 

printf("Tree elements in inorder after deletion :\n"); 

 Display(Tree); 

return 0; 

}
Node *Insert(Node *Tree, int e) 

{ 

Node *NewNode = malloc(sizeof(Node)); 

if (Tree == NULL) 

 { 

 NewNode->element = e; 

 NewNode->left = NULL; 

 NewNode->right = NULL; 

 Tree = NewNode; 

 } 

else if (e < Tree->element) 

 Tree->left = Insert(Tree->left, e); 

else if (e > Tree->element) 

 Tree->right = Insert(Tree->right, e); 

return Tree; 

} 

void Display(Node *Tree) 

{ 

if (Tree != NULL) 

 { 

 Display(Tree->left); 

 printf("%d\t", Tree->element); 

 Display(Tree->right); 

 } 

} 

Node *Delete(Node *Tree, int e) 

{ 

Node *TempNode = malloc(sizeof(Node)); 

if (e < Tree->element) 

 { 

 Tree->left = Delete(Tree->left, e); 

 } 

else if (e > Tree->element) 

 { 

 Tree->right = Delete(Tree->right, e); 

 } 

else if (Tree->left && Tree->right) 

 { 

 TempNode = FindMin(Tree->right); 

 Tree->element = TempNode->element; 

 Tree->right = Delete(Tree->right, Tree->element); 

 } 

else

 { 

 TempNode = Tree; 

 if(Tree->left == NULL) 

 Tree = Tree->right; 

 else if (Tree->right == NULL) 

 Tree = Tree->left;
 free(TempNode); 

 } 

return Tree; 

} 

Node *FindMin(Node *Tree) 

{ 

if (Tree != NULL) 

 { 

 if (Tree->left == NULL) 

 return Tree; 

 else

 FindMin(Tree->left); 

 } 

}
