#include <iostream>

using namespace std;

struct Vertex {
  int data;
  int balance = 0;
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

int height(Vertex *p) {
  if (p == NULL) return 0;
  else {
    return 1 + max(height(p->right), height(p->left));
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

float heightsr(Vertex *p) {
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


void delete_From_SDP(int X, Vertex *&root) {
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

void LL(Vertex *&p) {
  Vertex *q = p->left;
  p->balance = q->balance = 0;
  p->left = q->right;
  q->right = p;
  p = q;
}

void RR(Vertex *&p) {
  Vertex *q = p->right;
  p->balance = q->balance = 0;
  p->right = q->left;
  q->left = p;
  p = q;
}

void LR(Vertex *&p) {
  Vertex *q = p->left;
  Vertex *r = q->right;
  if (r->balance < 0) {
    p->balance = 1;
  } else {
    p->balance = 0;
  }
  if (r->balance > 0) {
    q->balance = -1;
  } else {
    q->balance = 0;
  }
  r->balance = 0;
  q->right = r->left;
  p->left = r->right;
  r->left = q;
  r->right = p;
  p = r;
}

void RL(Vertex *&p) {
  Vertex *q = p->right;
  Vertex *r = q->left;
  if (r->balance > 0) {
    p->balance = -1;
  } else {
    p->balance = 0;
  }
  if (r->balance < 0) {
    q->balance = 1;
  } else {
    q->balance = 0;
  }
  r->balance = 0;
  q->left = r->right;
  p->right = r->left;
  r->right = q;
  r->left = p;
  p = r;
}

bool growth;

void AVL(int D, Vertex *&p) {
  if (!p) {
    p = new Vertex;
    p->data = D;
    p->left = nullptr;
    p->right = nullptr;
    p->balance = 0;
    growth = true;
  } else if (p->data > D) {
    AVL(D, p->left);
    if (growth) {
      if (p->balance > 0) {
        p->balance = 0;
        growth = false;
      } else if (p->balance == 0) {
        p->balance = -1;
        growth = true;
      } else {
        if (p->left->balance < 0) {
          LL(p);
          growth = false;
        } else {
          LR(p);
          growth = false;
        }
      }
    }
  } else if (p->data < D) {
    AVL(D, p->right);
    if (growth) {
      if (p->balance < 0) {
        p->balance = 0;
        growth = false;
      } else if (p->balance == 0) {
        p->balance = 1;
        growth = true;
      } else {
        if (p->right->balance > 0) {
          RR(p);
          growth = false;
        } else {
          RL(p);
          growth = false;
        }
      }
    }
  }
}

bool decreasing = false;
void LL1(Vertex*& p) {
	Vertex* q = p->left;
	if (q->balance == 0) {
		q->balance = 1;
		p->balance = -1;
		decreasing = false;
	}
	else {
		q->balance = 0;
		p->balance = 0;
	}
	p->left = q->right;
	q->right = p;
	p = q;
}

void RR1(Vertex*& p) {
	Vertex* q = p->right;
	if (q->balance == 0) {
		q->balance = -1;
		p->balance = 1;
		decreasing = false;
	}
	else {
		q->balance = 0;
		p->balance = 0;
	}
	p->right = q->left;
	q->left = p;
	p = q;
}

void BL(Vertex*& p) { 
	if (p->balance == -1) {
		p->balance = 0;
	}
	else if (p->balance == 0) {
		p->balance = 1;
		decreasing = false;
	}
	else if (p->balance == 1) {
		if (p->right->balance >= 0) {
			RR1(p);
		}
		else {
			RL(p);
		}
	}
}

void BR(Vertex*& p) { 
	if (p->balance == 1) {
		p->balance = 0;
	}
	else if (p->balance == 0) {
		p->balance = -1;
		decreasing = false;
	}
	else if (p->balance == -1) {
		if (p->left->balance <= 0) {
			LL1(p);
		}
		else {
			LR(p);
		}
	}
}



void del(Vertex*& r, Vertex*& q) {
	if (r->right != nullptr) {
		del(r->right, q);
		if (decreasing) BR(r);
	}
	else {
		q->data = r->data;
		q = r;
		r = r->left;
		decreasing = true;
	}
}

void delete_From_AVL(Vertex*& p, int key) {
	if (p == nullptr);
	else if (p->data > key) {
		delete_From_AVL(p->left, key);
		if (decreasing) BL(p);
	}
	else if (p->data < key) {
		delete_From_AVL(p->right, key);
		if (decreasing) BR(p);
	}
	else {
		Vertex* q = p;
		if (q->right == nullptr) {
			p = q->left;
			decreasing = true;
		}
		else if (q->left == nullptr) {
			p = q->right;
			decreasing = true;
		}
		else {
			del(q->left, q);
			if (decreasing) BL(p);
		}
		delete q;
	}
}


int main() {
	Vertex *treeAVL = nullptr;
	int n = 10;
    int mas[n];
    for (int i = 0; i < n; i++) {
    	mas[i] = rand() % 100;
    	AVL(mas[i], treeAVL);
    }
    left(treeAVL);
	for(int i = 0; i < 10; i++){
	  cout << "\n";
	  int key;
	  cin >> key;
	  delete_From_AVL(treeAVL, key);
	  left(treeAVL);
	}
  return 0;
}
