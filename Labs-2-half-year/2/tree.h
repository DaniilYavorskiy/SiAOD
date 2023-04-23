#pragma once

#include <iostream>
#include <cmath>
#include <functional>

struct Vertex {
    const int data;
    Vertex *left, *right;
    int balance;

    explicit Vertex(int data, Vertex *left = nullptr, Vertex *right = nullptr, int balance = 0) :
            data(data), left(left), right(right), balance(balance) {}
};

class Tree {
protected:
    Vertex *root = nullptr;

public:

    ~Tree() {
        std::function<void(Vertex *)> del = [&del](Vertex *root) {
            if (root) {
                del(root->right);
                del(root->left);
                delete root;
            }
        };
        del(root);
    }

    Vertex *getRoot() const {
        return root;
    }

    int size() const {
        std::function<int(Vertex *)> size = [&size](Vertex *root) {
            return root ? 1 + size(root->left) + size(root->right) : 0;
        };
        return size(root);
    }

    int height() const {
        std::function<int(Vertex *)> height = [&height](Vertex *root) {
            return root ? 1 + std::max(height(root->left), height(root->right)) : 0;
        };
        return height(root);
    }

    int checkSum() const {
        std::function<int(Vertex *)> checkSum = [&checkSum](Vertex *root) {
            return root ? root->data + checkSum(root->left) + checkSum(root->right) : 0;
        };
        return checkSum(root);
    }

private:
    int lenSum(Vertex *root, int depth) const {
        return root ? depth + lenSum(root->left, depth + 1) + lenSum(root->right, depth + 1) : 0;
    }

public:
    double mediumHeight() const {
        return (double) lenSum(root, 1) / size();
    }

    void printLNR() const {
        std::function<void(Vertex *)> printLNR = [&printLNR](Vertex *root) {
            if (root) {
                printLNR(root->left);
                std::cout << root->data << ' ';
                printLNR(root->right);
            }
        };
        return printLNR(root);
    }
};

class IsdpTree : public Tree {
public:
    IsdpTree(int arr[], int n) {
        std::function<Vertex *(int[], int, int)> IsdpTree = [&IsdpTree](int arr[], int l, int r) -> Vertex * {
            if (l > r) {
                return nullptr;
            } else {
                const int m = (int) ceil((double) (l + r) / 2);
                return new Vertex(arr[m], IsdpTree(arr, l, m - 1), IsdpTree(arr, m + 1, r));
            }
        };
        root = IsdpTree(arr, 0, n - 1);
    }
};

class SdpTree : public Tree {
public:
    void addRec(int data) {
        std::function<void(Vertex *&)> addRec = [&addRec, &data](Vertex *&root) {
            if (!root) {
                root = new Vertex(data);
            } else if (data < root->data) {
                addRec(root->left);
            } else if (data > root->data) {
                addRec(root->right);
            } else {
                std::cout << "Data already exist\n";
            }
        };
        return addRec(root);
    }

    void addDouble(int data) {//pointer vertex add
        auto p = &root;//короче сохраняется корень, и на глубине показывает себя лучше чем рекурсия
        while (*p) {//
            if (data < (*p)->data) {
                p = &((*p)->left);
            } else if (data > (*p)->data) {
                p = &((*p)->right);
            } else {
                std::cout << "Data already exist\n";
                break;
            }
        }//
        if (!*p) {
            (*p) = new Vertex(data);
        }
    }
};
