#include <iostream>
#include <ctime>

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

int VR, HR;

void B2Insert(int D, Vertex *&p) {
  if (!p) {
    p = new Vertex;
    p->data = D;
    p->left = p->right = NULL;
    p->balance = 0;
    VR = 1;
  } else if (p->data > D) {
    B2Insert(D, p->left);
    if (VR == 1) {
      if (p->balance == 0) {
        Vertex *q = p->left;
        p->left = q->right;
        q->right = p;
        p = q;
        p->balance = 1;
        VR = 0;
        HR = 1;
      } else {
        p->balance = 0;
        VR = 1;
        HR = 0;
      }
    } else
      HR = 0;
  } else if (p->data < D) {
    B2Insert(D, p->right);
    if (VR == 1) {
      p->balance = 1;
      HR = 1;
      VR = 0;
    } else if (HR == 1) {
      if (p->balance == 1) {
        Vertex *q = p->right;
        p->right = q->left;
        p->balance = 0;
        q->balance = 0;
        q->left = p;
        p = q;
        VR = 1;
        HR = 0;
      } else
        HR = 0;
    }
  }
}

const int n = 100;
int AW[n][n];
int AP[n][n];
int AR[n][n];
int W[n];
int V[n];

void calculate_AW() {

  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      AW[i][j] = AW[i][j - 1] + W[j];
}

void calculate_AP_AR() {
  int i, j, m, min, k, h;
  for (i = 0; i < n - 1; i++) {
    j = i + 1;
    AP[i][j] = AW[i][j];
    AR[i][j] = j;
  }
  for (h = 2; h < n; h++) {
    for (i = 0; i < n - h; i++) {
      j = i + h;
      m = AR[i][j - 1];
      min = AP[i][m - 1] + AP[m][j];
      for (k = m + 1; k < AR[i + 1][j]; k++) {
        int x = AP[i][k - 1] + AP[k][j];
        if (x < min) {
          m = k;
          min = x;
        }
      }
      AP[i][j] = min + AW[i][j];
      AR[i][j] = m;
    }
  }
}

void A1(Vertex *&root, int *V1, int *W1, int n) {
  for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (W1[j] > W1[j + 1]) {
        swap(W1[j], W1[j + 1]);
        swap(V1[j], V1[j + 1]);
      }
  for (int i = 0; i < n; i++) {
    add_SDP_rec(V1[i], root);
  }
}

void A2(Vertex *&root, int *V2, int *W2, int L, int R) {
	for (int i = 0; i < n - 1; i++)
    for (int j = 0; j < n - i - 1; j++)
      if (V2[j] > V2[j + 1]) {
        swap(W2[j], W2[j + 1]);
        swap(V2[j], V2[j + 1]);
      }
  int wes = 0;
  int sum = 0;
  int i;
  if (L <= R) {
    for (i = L; i < R; i++) {
      wes += W2[i];
    }
    for (i = L; i < R; i++) {
      if ((sum < wes / 2) && (sum + W2[i] > wes / 2))
        break;
      sum += W2[i];
    }
    add_SDP_rec(V2[i], root);
    A2(root, V2, W2, L, i - 1);
    A2(root, V2, W2, i + 1, R);
  }
}

int main() {
	srand(time(NULL));
	int V2[n], W2[n], V3[n], W3[n];
    Vertex *A1tree = nullptr;
    Vertex *A2tree = nullptr;
	for (int i = 0; i < n; i++) {
	    V3[i] = V2[i]  = rand() % (n * 100);
        W3[i] = W2[i]  =  W[i] = rand() % (n / 4);
  }

 A1(A1tree, V2, W2, n);
 A2(A2tree, V3, W3, 0, n-1);
 left(A1tree);
 cout << "\n\n\n";	
 left(A2tree);
 cout << "\n\n\n";	
 cout << "            size  controlSum   height     averageHeight\n";
 printf(" A1tree  %7d %8d     %5d  %13.3f\n", size(A1tree), controlSum(A1tree), height(A1tree), heightsr(A1tree));
 printf(" A2tree  %7d %8d     %5d  %13.3f\n", size(A2tree), controlSum(A2tree), height(A2tree), heightsr(A2tree));
  return 0;
}
