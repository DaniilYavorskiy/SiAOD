#include <iostream>

using namespace std;

struct Vertex {
    int data;
    int balance = 0;
    Vertex* left = nullptr;
    Vertex* right = nullptr;
};

int size(Vertex* p) {
    if (!p)
        return 0;
    else {
        return 1 + size(p->left) + size(p->right);
    }
}

int height(Vertex* p) {
    if (!p)
        return 0;
    else {
        return 1 + max(height(p->right), height(p->left));
    }
}

int controlSum(Vertex* p) {
    if (!p)
        return 0;
    else {
        return p->data + controlSum(p->left) + controlSum(p->right);
    }
}

int SDP(Vertex* p, int L) {

    if (!p)
        return 0;
    else {
        return L + SDP(p->left, L + 1) + SDP(p->right, L + 1);
    }
}

float averageHeight(Vertex* p) { return float(SDP(p, 1)) / size(p); }

void printFromLeftToRight(Vertex* p) {
    if (p) {
        printFromLeftToRight(p->left);
        cout << p->data << " ";
        printFromLeftToRight(p->right);
    }
}

void printFromBottomToUp(Vertex* p) {
    if (p) {
        printFromBottomToUp(p->left);
        printFromBottomToUp(p->right);
        cout << p->data << " ";
    }
}

void printFromUpToBottom(Vertex* p) {
    if (p) {
        cout << p->data << " ";
        printFromUpToBottom(p->left);
        printFromUpToBottom(p->right);
    }
}

void deleteTree(Vertex* p) {
    if (!p)
        return;
    else {
        deleteTree(p->left);
        deleteTree(p->right);
        delete p;
    }
}

void LL(Vertex*& p) {
    Vertex* q = p->left;
    p->balance = q->balance = 0;
    p->left = q->right;
    q->right = p;
    p = q;
}

void RR(Vertex*& p) {
    Vertex* q = p->right;
    p->balance = q->balance = 0;
    p->right = q->left;
    q->left = p;
    p = q;
}

void LR(Vertex*& p) {
    Vertex* q = p->left;
    Vertex* r = q->right;
    if (r->balance < 0) {
        p->balance = 1;
    }
    else {
        p->balance = 0;
    }
    if (r->balance > 0) {
        q->balance = -1;
    }
    else {
        q->balance = 0;
    }
    r->balance = 0;
    q->right = r->left;
    p->left = r->right;
    r->left = q;
    r->right = p;
    p = r;
}

void RL(Vertex*& p) {
    Vertex* q = p->right;
    Vertex* r = q->left;
    if (r->balance > 0) {
        p->balance = -1;
    }
    else {
        p->balance = 0;
    }
    if (r->balance < 0) {
        q->balance = 1;
    }
    else {
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

void AVL(Vertex*& p, int D) {
    if (!p) {
        p = new Vertex;
        p->data = D;
        p->left = nullptr;
        p->right = nullptr;
        p->balance = 0;
        growth = true;
    }
    else if (p->data > D) {
        AVL(p->left, D);
        if (growth) {
            if (p->balance > 0) {
                p->balance = 0;
                growth = false;
            }
            else if (p->balance == 0) {
                p->balance = -1;
                growth = true;
            }
            else {
                if (p->left->balance < 0) {
                    LL(p);
                    growth = false;
                }
                else {
                    LR(p);
                    growth = false;
                }
            }
        }
    }
    else if (p->data < D) {
        AVL(p->right, D);
        if (growth) {
            if (p->balance < 0) {
                p->balance = 0;
                growth = false;
            }
            else if (p->balance == 0) {
                p->balance = 1;
                growth = true;
            }
            else {
                if (p->right->balance > 0) {
                    RR(p);
                    growth = false;
                }
                else {
                    RL(p);
                    growth = false;
                }
            }
        }
    }
}

bool decreasing = false;

int VR, HR;

void B2Insert(int D, Vertex*& p) {
    if (!p) {
        p = new Vertex;
        p->data = D;
        p->left = p->right = NULL;
        p->balance = 0;
        VR = 1;
    }
    else if (p->data > D) {
        B2Insert(D, p->left);
        if (VR == 1) {
            if (p->balance == 0) {
                Vertex* q = p->left;
                p->left = q->right;
                q->right = p;
                p = q;
                p->balance = 1;
                VR = 0;
                HR = 1;
            }
            else {
                p->balance = 0;
                VR = 1;
                HR = 0;
            }
        }
        else
            HR = 0;
    }
    else if (p->data < D) {
        B2Insert(D, p->right);
        if (VR == 1) {
            p->balance = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR == 1) {
            if (p->balance == 1) {
                Vertex* q = p->right;
                p->right = q->left;
                p->balance = 0;
                q->balance = 0;
                q->left = p;
                p = q;
                VR = 1;
                HR = 0;
            }
            else
                HR = 0;
        }
    }
}

int main() {

    srand(time(NULL));
    Vertex* AVLtree = nullptr;
    Vertex* btree = nullptr;
    for (int i = 0; i < 101; i++) {
        int value = rand() % 10000;
        AVL(AVLtree, value);
        B2Insert(value, btree);
    }

    printFromLeftToRight(btree);

    std::cout << "\n\n\n\n\n\n\n";
    printf("		Size    Summ   Height  Average Height \n");
    printf(" AVL  %7d %8d %5d %13.2f\n", size(AVLtree), controlSum(AVLtree),
        height(AVLtree), averageHeight(AVLtree));
    printf(" DBD  %7d %8d %5d %13.2f\n", size(btree), controlSum(btree),
        height(btree), averageHeight(btree));

}