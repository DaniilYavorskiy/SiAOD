#include <iostream>

using namespace std;

struct node
{
 int data;
 struct node *left;
 struct node *right;
} Node;

struct node *newNode(int data) {
  struct node *node = (struct node *)malloc(sizeof(struct node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return (node);
}

void traversePreOrder(struct node *temp) {
  if (temp != NULL) {
    cout << " " << temp->data;
    traversePreOrder(temp->left);
    traversePreOrder(temp->right);
  }
}

void traverseInOrder(struct node *temp) {
  if (temp != NULL) {
    traverseInOrder(temp->left);
    cout << " " << temp->data;
    traverseInOrder(temp->right);
  }
}

void traversePostOrder(struct node *temp) {
  if (temp != NULL) {
    traversePostOrder(temp->left);
    traversePostOrder(temp->right);
    cout << " " << temp->data;
  }
}

int height(struct node *p) {
  if (!p)
    return 0;
  else {
    return 1 + max(height(p->right), height(p->left));
  }
}

int NodeCount(struct node * temp){
    if (temp->left == NULL && temp->right == NULL)
        return 1;
    int left, right;
    if (temp->left != NULL)
        left = NodeCount(temp->left);
    else
        left = 0;
    if (temp->right != NULL)
        right = NodeCount(temp->right); 
    else 
        right = 0;

    return left+right+1;
}

int Sum(struct node * temp) {
  if (temp == NULL)
    return 0;
  else
    return (temp -> data + Sum(temp->left) + Sum(temp->right));
}

//подсчёт кол-ва вершин на каждом уровне
int countOnLevel(struct node * temp, int N)
{
    if (temp == 0)
        return 0;
    if (N == 0)
        return 1;
    return countOnLevel(temp->left, N - 1) + countOnLevel(temp->right, N - 1);
}

int main() {
  node *root = newNode(1);
  root->right = newNode(3);
  root->right->left = newNode(2);
  root->right->right = newNode(6);
  root->right->right->left = newNode(5);
  root->right->right->left->left = newNode(4);
  
  cout <<"\nFrom top to bottom: ";
  traversePreOrder(root);
  cout << "\nFrom left to right: ";
  traverseInOrder(root);
  cout << "\nFrom bottom to top: ";
  traversePostOrder(root);
  cout<<"\nTree size: "<< NodeCount(root);
  cout<<"\nChecksum: "<< Sum(root);
  cout<<"\nTree height: "<< height(root);
  
  //кол-во вершин на каждом уровне
  int level = height(root);
  int sum = 0;
  for(int i = 0; i <= level; i++){
    int temp = countOnLevel(root,i);   
    sum += (i + 1) * temp;   
  }
  cout<<"\nAverage height of the tree: "<< sum / NodeCount(root);
  return 0;
}