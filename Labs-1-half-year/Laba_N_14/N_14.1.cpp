#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

struct List {

    List *next;
    int data;

};

struct Queue {

    List* head;

};

int FillHesh(Queue *Hesh, int n, int m) {

    srand(time(NULL));
    bool flag;
    int collisium = 0;
    int i, j, num;
    List *p, *q;
    for(i = 0; i < n; i++) {
        num = rand()%1000;
        j = num % m;
        p = new List;
        p->data = num;
        if(Hesh[j].head == NULL) {
            p->next = Hesh[j].head;
            Hesh[j].head = p;
            continue;
        }
        else {
            q = Hesh[j].head;
            flag = true;
            while(q) {
                if(q->data == num) {
                    flag = false;
                    break;
                }
                q = q->next;
            }
            if(flag == true) {
                collisium ++;
                p->next = Hesh[j].head;
                Hesh[j].head = p;
                continue;
            }
        }
    }
    return collisium;

}

void RunNumber (Queue *Hesh, int m) {

    int i;
    for (i = 0; i < m; i++) {
        List* p = Hesh[i].head;
        while (p != NULL) {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }

}

void Table(int m, int n, int col) {

    int i;
    std::string sm = to_string(m), sn = to_string(n), scol = to_string(col);
    cout << "+-----------------+\n";
    cout << "|  m  |  n  | col |\n";
    cout << "+-----------------+\n";
    cout << "|";
    for(i = 0; i < 3 - sm.length(); i++) 
        cout << " ";
    cout << m << "  |";
    for(i = 0; i < 3 - sn.length(); i++)
        cout << " ";
    cout << n << "  |";
    for(i = 0; i < 3 - scol.length(); i++)
        cout << " ";
    cout << col << "  |" << endl;
    cout << "+-----------------+\n";

}

int Search(Queue *Hesh, int m, int K) {

    int j = K % m;
    List* p;
    p = Hesh[j].head;
    while(p){
        if (p->data == K) return j;
        p = p->next;
    }
    return -1;

}

int main() {

    int i;
    int n = 60;
    int m = 11;

    Queue Hesh[m];
    List *p;
    List* head;
    for (i = 0; i < m; i++) {
        Hesh[i].head = NULL;
    }
    int collisium = FillHesh(Hesh, n, m);
    RunNumber(Hesh, m);
    cout << collisium << endl;
    Table(m, n, collisium);
    int K;
    cin >> K;
    cout << Search(Hesh, m, K);
    
    return 0;

}
 
