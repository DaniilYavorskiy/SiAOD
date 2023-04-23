#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <clocale>

using namespace std;

int const N = 10;

struct Vertex {
  	int Data;
  	int bal;
  	Vertex *Left;
  	Vertex *Right;
};

Vertex *Root;
Vertex *RandomVertex()

{
  	Vertex *box = new struct Vertex;
  	box->Data = rand() % 112;
  	cout << " " << box->Data;
  	box->Left = NULL;
  	box->Right = NULL;
  	return box;
};


void PrintMas(int *arr, int size) //Вывод массива
{
  	for (int i = 0; i < size; i++)
    	cout << arr[i] << " ";
  	cout << endl;
}

void FillRand (int* A, int n)
{
    bool chislo;

    for (int i = 0; i < n;)
    {
        chislo = false;
        int random = rand() % (N+10) + 1;

        for (int j = 0; j < i; j++)
        {
            if (A[j] == random)
            {
                chislo = true;
                break;
            }
        }

        if (!chislo)
        {
            A[i] = random;
            i++;
        }
    }
}

void BubbleSort(int Z[], int N) {
  	int temp;
  	for (int i = 0; i < N - 1; i++) {
    	for (int j = (N - 1); j > i; j--) {
      		if (Z[j - 1] > Z[j]) {
        		temp = Z[j - 1];
        		Z[j - 1] = Z[j];
        		Z[j] = temp;
      		}
    	}
  	}
}
float max(int x, int y) {
  	if (x > y)
    	return x;
  	else
    	return y;
}
void Obh1(Vertex *p) {
  	if (p != NULL) {

    Obh1(p->Left);
    cout << p->Data << " ";
    Obh1(p->Right);
  }
}

int Razm(Vertex *p) {
  	if (p == NULL)
    	return 0;
  	else
    	return (1 + Razm(p->Left) + Razm(p->Right));
}

float Sum(Vertex *p) {
  	if (p == NULL)
    	return 0;
  	else
    	return (p->Data + Sum(p->Left) + Sum(p->Right));
}

float SumDP(Vertex *p, int L) {
  	if (p == NULL)
    	return 0;
  	else
    	return (L + SumDP(p->Left, L + 1) + SumDP(p->Right, L + 1));
}

float Vis(Vertex *p) {
  	if (p == NULL)
    	return 0;
  	else
    	return (SumDP(Root, 1) / Razm(Root));
}

Vertex *ISDP(int L, int R, int *arr) {
  	int m;
  	if (L > R)
    	return NULL;
  	else
    	m = (L + R) / 2;

  	Vertex *p = new Vertex;
  	p->Data = arr[m];
  	p->Left = ISDP(L, m - 1, arr);
  	p->Right = ISDP(m + 1, R, arr);
  	return p;
}

void Info(Vertex *Root) {
  	cout << "Traversing tree from left to right: " << endl;
  	Obh1(Root);
  	cout << endl << endl;
  	cout << "Tree size: ";
  	cout << Razm(Root);
  	cout << endl << endl;
  	cout << "Tree sum: ";
  	cout << Sum(Root) << endl << endl;
  	cout << "Sum of tree path lengths: ";
  	cout << SumDP(Root, 1) << endl << endl;
  	cout << "Tree height: ";
  	cout << Vis(Root) << endl;
}

int main() {
	setlocale (LC_ALL,"");
    int size = 100;
    int* A = new int[size];
    for (int i = 100; i >= 0; i--) {
        A[size-i] = i;
    }
    PrintMas(A, size);
    cout << endl;
    BubbleSort(A, size);
    cout << endl;
    PrintMas(A, size);
    cout << endl;
    Root = ISDP(0, size - 1, A);
    cout << endl;
    Info(Root);
    return 0;
}