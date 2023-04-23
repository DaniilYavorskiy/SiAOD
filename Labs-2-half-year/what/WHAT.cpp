#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
bool rost = 1; // За физ увеличение дерева по высоте
bool umen  = 1;
const int N = 10;
int kolpov = 0;
bool decrease = 1;
bool VR = 0;
bool HR = 1;
struct Vertex {
  int Data;
  int bal;
  Vertex *Left;
  Vertex *Right;
};
Vertex *Root;
Vertex* RootDBD;

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
int max(int x, int y) {
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
void Obh2(Vertex* p) {
    if (p != NULL) {

        cout << p->Data << " ";
        Obh2(p->Left);
        Obh2(p->Right);
    }
}
void Obh3(Vertex* p) {
    if (p != NULL) {
        Obh3(p->Left);
        Obh3(p->Right);
        cout << p->Data << " ";
    }
}

int Razm(Vertex *p) {
  if (p == NULL)
    return 0;
  else
    return (1 + Razm(p->Left) + Razm(p->Right));
}

int Sum(Vertex *p) {
  if (p == NULL)
    return 0;
  else
    return (p->Data + Sum(p->Left) + Sum(p->Right));
}

int Vis(Vertex *p) {
  if (p == NULL)
    return 0;
  else
    return (1 + max(Vis(p->Left), Vis(p->Right)));
}

int SumDP(Vertex *p, int L) {
  if (p == NULL)
    return 0;
  else
    return (L + SumDP(p->Left, L + 1) + SumDP(p->Right, L + 1));
}

Vertex *TreeSearch(Vertex *Root, int X) {
  struct Vertex *box = Root;
  while (box != NULL) {
    if (box->Data > X)
      box = box->Left;
    else if (box->Data < X)
      box = box->Right;
    else
      break;
  }
  if (box != NULL) {
    cout << "Вершина найдена" << endl;
    return box;
  } else {
    cout << "Вершина не найдена" << endl;
    return 0;
  }
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

void AddVertexDouble(int x, Vertex *&Root) {
  struct Vertex **box;
  box = &Root;
  while (*box != NULL) {
    if (x < (*box)->Data)
      box = &((*box)->Left);
    else if (x > (*box)->Data)
      box = &((*box)->Right);
    else
      break;
  }
  if (*box == NULL) {
    *box = new struct Vertex;
    (*box)->Data = x;
    (*box)->Right = NULL;
    (*box)->Left = NULL;
  }
}
struct Vertex *RBT_Double(int Z[], int size) {
  struct Vertex *Root = NULL;
  for (int i = 0; i < size; i++) {
    AddVertexDouble(Z[i], Root);
  }
  return Root;
}
void AddVertRec(int x, Vertex *&box) {
  if (box == NULL) {
    box = new struct Vertex;
    box->Data = x;
    box->Left = NULL;
    box->Right = NULL;
  } else if (x < box->Data)
    AddVertRec(x, box->Left);
  else if (x > box->Data)
    AddVertRec(x, box->Right);
}

struct Vertex *RecSDP(int Z[], int size) {
  struct Vertex *Root = NULL;
  for (int i = 0; i < size; i++) {
    AddVertRec(Z[i], Root);
  }
  return Root;
}

void Info(Vertex *Root) {
  cout << "Obhod dereva sleva-napravo: " << endl;
  Obh1(Root);
  cout << endl;
  cout << "Razmer dereva: ";
  cout << Razm(Root);
  cout << endl;
  cout << "Summa dereva: ";
  cout << Sum(Root) << endl;
  cout << "Summa dlin putey dereva: ";
  cout << SumDP(Root, 1) << endl;
  cout << "Visota dereva: ";
  cout << Vis(Root) << endl;
}

void DeleteVertex(int x, Vertex *&root) {
  Vertex **p = &root;
  // Движение по дереву 
  while (*p!=NULL) {
    if (x < (*p)->Data) {
      p = &((*p)->Left);
    } else if (x > (*p)->Data)
      p = &((*p)->Right);
     else break;
  }
  // Работа с адресом и с адресом адреса пока вершина не нулевая 
  if (*p!=NULL) {
    Vertex *q = *p;
    //нет поддеревьев
    if (!q->Left && !q->Right) *p = NULL;
    // Если одно поддерево есть 
    if (!q->Left)
      *p = q->Right;
    else if (!q->Right)
      *p = q->Left;
    // Когда есть два поддерева 
    else {
      Vertex *r = q->Left;
      Vertex *s = q;
      if (!r->Right) {
        r->Right = q->Right; //Если левое поддерево уже не имеет правого поддерева то просто подтягиваем левое поддерево
        *p = r;
      } else {
        while (r->Right) {
          s = r;
          r = r->Right;
        }
        s->Right = r->Left; //Подтягиваем левое поддерево к вершине s(хвост) чтобы не потерять не него ссылку
        r->Left = q->Left; //Вершине r присваиваются поддеревья вершины q
        r->Right = q->Right;
        *p = r; // Адрес адреса ссылаются на замещающую вершину 
      }
    }
    delete q;
  }
}

void LL(Vertex*& p) {
    Vertex* q = p->Left;
    p->bal = 0;
    q->bal = 0;
    p->Left = q->Right;
    q->Right = p;
    p = q;
}

void RR(Vertex*& p) {
    Vertex* q = p->Right;
    p->bal = 0;
    q->bal = 0;
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void LR(Vertex*& p) {
    Vertex* q = p->Left;
    Vertex* r = q->Right;
    if (r->bal < 0)
        p->bal = 1;
    else
        p->bal = 0;
    if
        (r->bal > 0) q->bal = -1;
    else
        q->bal = 0;
    r->bal = 0;
    q->Right = r->Left;
    p->Left = r->Right;
    r->Left = q;
    r->Right = p;
    p = r;
}

void RL(Vertex*& p) {
    Vertex* q = p->Right;
    Vertex* r = q->Left;
    if (r->bal > 0)
        p->bal = -1;
    else
        p->bal = 0;
    if (r->bal < 0)
        q->bal = 1;
    else
        q->bal = 0;
    r->bal = 0;
    q->Left = r->Right;
    p->Right = r->Left;
    r->Right = q;
    r->Left = p;
    p = r;
}

void Add_ABL(int X, Vertex*& p) {
    if (p == NULL) {
        p = new Vertex;
        p->Data = X;
        p->Left = NULL;
        p->Right = NULL;
        p->bal = 0;
        rost = 1;
    }
    else if (p->Data > X) {
        Add_ABL(X, p->Left);
        if (rost == 1) {
            if (p->bal > 0) {
                p->bal = 0;
                rost = 0;
            }
            else if (p->bal == 0) {
                p->bal = -1;
            }
            else {
                if (p->Left->bal < 0) {
                    cout << "LL" << endl;
                    LL(p);
                    rost = 0;
                }
                else {
                    cout << "LR" << endl;
                    LR(p);
                    rost = 0;
                }
            }
        }
    }
    else if (p->Data < X) {
        Add_ABL(X, p->Right);
        if (rost == 1) {
            if (p->bal < 0) {
                p->bal = 0;
                rost = 0;
            }
            else if (p->bal == 0) {
                p->bal = 1;
            }
            else {
                if (p->Right->bal > 0) {
                    cout << "RR" << endl;
                    RR(p);
                    rost = 0;
                }
                else {
                    cout << "RL" << endl;
                    RL(p);
                    rost = 0;
                }
            }
        }
    }
}
void LL1(Vertex*& p)
{
    Vertex* q = p->Left;
    if (q->bal == 0)
    {
        q->bal = 1;
        p->bal = -1;
        umen = false;
    }
    else
    {
        q->bal = 0;
        p->bal = 0;
    }
    p->Left = q->Right;
    q->Right = p;
    p = q;
}

void RR1(Vertex*& p)
{
    Vertex* q = p->Right;
    if (q->bal == 0)
    {
        q->bal = -1;
        p->bal = 1;
        umen = false;
    }
    else
    {
        q->bal = 0;
        p->bal = 0;
    }
    p->Right = q->Left;
    q->Left = p;
    p = q;
}

void BL(Vertex*& p)
{
    if (p->bal == -1)
    {
        p->bal = 0;
    }
    else if (p->bal == 0)
    {
        p->bal = 1;
        umen = false;
    }
    else if (p->bal == 1)
    {
        if (p->Right->bal >= 0)
        {
            cout << "RR1" << endl;
            RR1(p);
            kolpov++;
        }
        else
        {
            cout << "RL" << endl;
            RL(p);
            kolpov++;
        }
    }
}

void BR(Vertex*& p)
{
    if (p->bal == 1)
    {
        p->bal = 0;
    }
    else if (p->bal == 0)
    {
        p->bal = -1;
        umen = false;
    }
    else if (p->bal == -1)
    {
        if (p->Left->bal <= 0)
        {
            cout << "LL1" << endl;
            LL1(p);
            kolpov++;
        }
        else
        {
            cout << "LR" << endl;
            LR(p);
            kolpov++;
        }
    }
}


void DEL(Vertex*& r, Vertex*& q)
{
    if (r->Right!= NULL)
    {
        DEL(r->Right, q);
        if (umen)
        {
            BR(r);
        }
    }
    else
    {
        q->Data = r->Data;
        q = r;
        r = r->Left;
        umen = true;
    }
}

void DELETEAVL(int& x, Vertex*& p)
{
    if (p == NULL);
    else if (x < p->Data)
    {
        DELETEAVL(x, p->Left);
        if (umen == true)
        {
            BL(p);
        }
    }
    else if (x > p->Data)
    {
        DELETEAVL(x, p->Right);
        if (umen == true)
        {
            BR(p);
        }
    }
    else
    {
        Vertex* q = p;
        if (q->Left == NULL)
        {
            p = q->Right;
            umen = true;
        }
        else if (q->Right == NULL)
        {
            p = q->Left;
            umen = true;
        }
        else
        {
            DEL(q->Left, q);
            if (umen == true)
            {
                BL(p);
            }
        }
        delete q;
    }

}

void B2Insert(int d, Vertex*& p)
{
    Vertex* q = new Vertex;
    if (p == NULL)
    {
        p = new Vertex;
        p->Data = d;
        p->Left = NULL;
        p->Right = NULL;
        p->bal = 0;
        VR = 1;
    }
    else if (p->Data > d)
    {
        B2Insert(d, p->Left);
        if (VR == 1)
        {
            if (p->bal == 0)
            {
                q = p->Left;
                p->Left = q->Right;
                q->Right = p;
                p = q;
                q->bal = 1;
                VR = 0;
                HR = 1;

            }
            else
            {
                p->bal = 0;
                VR = 1;
                HR = 0;
            }
        }
        else
        {
            HR = 0;
        }
    }
    else if (p->Data < d)
    {
        B2Insert(d, p->Right);
        if (VR == 1)
        {
            p->bal = 1;
            HR = 1;
            VR = 0;
        }
        else if (HR == 1)
        {
            if (p->bal == 1)
            {
                q = p->Right;
                p->bal = 0;
                q->bal = 0;
                p->Right = q->Left;
                q->Left = p;
                p = q;
                VR = 1;
                HR = 0;
            }
            else
            {
                HR = 0;
            }

        }
    }
}


int main() {
  system("chcp 1251>nul");
  struct Vertex *Root;
  Root = RandomVertex();
  Root->Left = RandomVertex();
  Root->Right = RandomVertex();
  Root->Right->Left = RandomVertex();
  Root->Right->Left->Left = RandomVertex();
  Root->Right->Left->Right = RandomVertex();
  cout << endl;
  cout << endl;
  cout << "Sredniy razmer dereva = " << (float)SumDP(Root, 1) / Razm(Root);
  cout << endl;
  Info(Root);
  system("pause");
  return 0;
}