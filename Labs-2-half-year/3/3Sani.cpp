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

void roundLeft(Vertex *p) {
    if (p != NULL) {
        roundLeft(p->left);
        cout << " " << p->data;
        roundLeft(p->right);
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

void add_SDP_rec(int nodeData, Vertex *&p){
    if(!p){
        p = new Vertex;
        p->data = nodeData;
        p->left = nullptr;
        p->right = nullptr;
    } else if (nodeData < p->data) {
        add_SDP_rec(nodeData, p->left);
    } else if (nodeData >= p->data) {
        add_SDP_rec(nodeData, p->right);
    } else {
        return;
    }
}


void deleteFromSDP(int X, Vertex *&root) {
    Vertex **p = &root;

    while(*p){
        if((*p)->data < X) {
            p = &((*p)->right);
        }
        else if ((*p)->data > X) {
            p = &((*p)->left);
        } else break;
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
    int numOfElem = 20;
    int arr[numOfElem];
    for (int i = 0; i < numOfElem; i++) {
        arr[i] = rand() % 100;
    }
    for(int i = 0; i < numOfElem; i++){
        add_SDP_rec(arr[i], treeSDP);
    }
    roundLeft(treeSDP);
    for(int i  = 0; i < 10; i++){
        int findNum;
        cout << endl << "Enter the key: "<<endl;
        cin >> findNum;
        deleteFromSDP(findNum, treeSDP);
        cout<<endl;
        roundLeft(treeSDP);
    }
    return 0;
}
