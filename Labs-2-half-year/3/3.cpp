#include <iostream>

using namespace std;

struct Vertex {
  int data;
  struct Vertex *left;
  struct Vertex *right;
};

Vertex *newVertex(int data) {
  Vertex *p = new Vertex;
  p->data = data;
  p->left = NULL;
  p->right = NULL;
  return(p);
}

int size(Vertex *p) {
  if (p == NULL) return 0;
  else {
    return 1 + size(p->left) + size(p->right);
  }
}

int hight(Vertex *p) {
  if (p == NULL) return 0;
  else {
    return 1 + max(hight(p->right), hight(p->left));
  }
}

int controlSum(Vertex *p) {
  if (p == NULL) return 0;
  else {
    return p->data + controlSum(p->left) + controlSum(p->right);
  }
}

int SDP(Vertex *p, int L) {  
  if (p == NULL)
    return 0;
  else {
    return L + SDP(p->left, L + 1) + SDP(p->right, L + 1);
  }
}

float hightsr(Vertex *p) {
  return float(SDP(p, 1)) / size(p); 
}

void top(Vertex *p) {
  if (p != NULL) {
    cout << " " << p->data;
    top(p->left);
    top(p->right);
  }
}

void left(Vertex *p) {
  if (p != NULL) {
    left(p->left);
    cout << " " << p->data;
    left(p->right);
  }
}

void bottom(Vertex *p) {
  if (p != NULL) {
    bottom(p->left);
    bottom(p->right);
    cout << " " << p->data;
  }
}

Vertex *ISDP(int L, int R, int mas[]) {
  if (L > R) return nullptr;
  else {
    int m = (L + R) / 2;
    Vertex *p = new Vertex;
    p->data = mas[m];
    p->left = ISDP(L, m - 1, mas);
    p->right = ISDP(m + 1, R, mas);
    return p;
  } 
}

void add_SDP(int D, Vertex *&root) {
    Vertex **p = &root;
    while(*p) {
        if(D < (*p)->data) p = &((*p)->left);
        else if(D >= (*p)->data) p = &((*p)->right);
        else break;
    }
    if(!*p) {
        *p = new Vertex;
        (*p)->data = D;
        (*p)->right = nullptr;
        (*p)->left = nullptr;
    }
}

void add_SDP_rec(int D, Vertex *&p){
    if(!p){
        p = new Vertex;
        p->data = D;
        p->left = nullptr;
        p->right = nullptr;
    } else if (D < p->data) {
        add_SDP_rec(D, p->left);
    } else if (D >= p->data) {
        add_SDP_rec(D, p->right);
    } else {
        return;
    }
}


void deleteFromSDP(int X, Vertex *&root) {
    Vertex **p = &root;
    while(*p){
        if((*p)->data < X) p = &((*p)->right);
        else if ((*p)->data > X) p = &((*p)->left);
        else break;
    }
    if(*p){
        Vertex *q = *p;
        if(!q->left) *p = q->right;
        else if (!q->right) *p=q->left;
        else {
            Vertex *r = q->left;
            Vertex *s = q;
            while(r->right){
                s = r;
                r = r->right;
            }
            s->right = r->left;
            r->left = q->left;
            r->right = q->right;
            *p = r;
        }
        delete q;
    }
}


int main() {
	Vertex *treeSDP = nullptr;
	int n = 20;
	int mas[n];
	for (int i = 0; i < n; i++) {
    	mas[i] = rand() % 100;
  	}
  	for(int i = 0; i < n; i++){
      add_SDP_rec(mas[i], treeSDP);
  	}
  	left(treeSDP);
	for(int i  = 0; i < 10; i++){
        int a;
        cout << endl << "Enter the key: "<<endl;
        cin >> a;
        deleteFromSDP(a, treeSDP);
        cout<<endl;
    	left(treeSDP);
    }
  return 0;
}
