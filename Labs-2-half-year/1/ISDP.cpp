#include <algorithm>
#include <iostream>

using namespace std;

struct Vertex {
  int data;
  Vertex *left = nullptr;
  Vertex *right = nullptr;
};

int size(Vertex *p) {
  if (!p)
    return 0;
  else {
    return 1 + size(p->left) + size(p->right);
  }
}

int height(Vertex *p) {
  if (!p)
    return 0;
  else {
    return 1 + max(height(p->right)+1, height(p->left));
  }
}

int controlSum(Vertex *p) {
  if (!p)
    return 0;
  else {
    return p->data + controlSum(p->left) + controlSum(p->right);
  }
}

int SDP(Vertex *p, int L) {
    
  if (!p)
    return 0;
  else {
    return L + SDP(p->left, L + 1) + SDP(p->right, L + 1);
  }
}

float averageHeight(Vertex *p) { return float(SDP(p, 1)) / size(p); }

void printFromLeftToRight(Vertex *p) {
  if (p) {
    printFromLeftToRight(p->left);
    cout << p->data << " ";
    printFromLeftToRight(p->right);
  }
}

void printFromBottomToUp(Vertex *p) {
  if (p) {
    printFromBottomToUp(p->left);
    printFromBottomToUp(p->right);
    
    cout << p->data << " ";
    
  }
}

void deleteTree(Vertex* p){
    if(!p) return; else {
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
    }
}

/* void findVertex(Vertex *&root, int x){
    Vertex *p = root;
    while(p){
        if(x < p->data) p = p -> left;
        else if (x > p->data) p = p -> right;
        else break;
    }
    if(p) cout << x << " is found\n";
    else 
    cout << x << " is not found\n";
} */

int main() {
  int counter = 1;
  Vertex *root = new Vertex{counter++};
  root->right = new Vertex{counter++};
  root->left = new Vertex{counter++};
  root->left->left = new Vertex{counter++};
  root->left->left->left = new Vertex{counter++};
  root->left->left->right = new Vertex{counter++};

  printFromBottomToUp(root);
    std::cout << "\n";
  printFromLeftToRight(root);
  cout << endl;
  cout << "size of tree = " << size(root) << endl;
  cout << "control sum = " << controlSum(root) << endl;
  cout << "height of tree = " << height(root) << endl;
  cout << "average height of tree = " << averageHeight(root) << endl;
  deleteTree(root);
}