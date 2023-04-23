#include <iomanip>
#include <iostream>
#define m 11

int COL_COUNTER;

unsigned int hashFunction(char x) { return x % m; }

using namespace std;
class Node {
public:
  char data;
  Node *next;
};

class LinkedList {
public:
  LinkedList() { head = NULL; }
  ~LinkedList(){};
  void addNode(char val);
  void print();

  Node *head;
};

void LinkedList::addNode(char val) {
  Node *newnode = new Node();
  newnode->data = val;
  newnode->next = NULL;
  if (head == NULL) {
    head = newnode;
  } else {
    Node *temp = head;
    while (temp->next != NULL) {
      temp = temp->next;
    }
    temp->next = newnode;
  }
}

void LinkedList::print() {
  if (head == NULL) {
    return;
  } else {
    Node *temp = head;
    while (temp) {
      cout << temp->data << " -> ";
      temp = temp->next;
    }
    cout << endl;
  }
}

bool pryamSvyazSearch(char x, LinkedList *table) {
  Node *head = table[hashFunction(x)].head;
  if (head == NULL) {
    return false;
  }
  Node *temp = head;
  while (temp) {
    if (temp->data == x) {
      return true;
    }
    temp = temp->next;
  }
  return false;
}

LinkedList *pryamSvyaz(string str) {
  LinkedList *list = new LinkedList[m];
  for (auto chr : str) {
    unsigned int h = hashFunction(chr);
    if (!pryamSvyazSearch(chr, list))
      list[h].addNode(chr);
  }
  return list;
}

bool linearSearch(char x, char *a) {
  auto h = hashFunction(x);
  while (true) {
    if (a[h] == x) {
      return true;
    }
    if (a[h] == 0) {
      return false;
    };
    h++;
    if (h >= m) {
      h -= m;
    };
  }
}

bool quadraSearch(char x, char *a) {
  auto h = hashFunction(x);
  int d = 1;
  while (true) {
    if (a[h] == x) {
      return true;
    }
    if (a[h] == 0) {
      return false;
    };
    h += d;
    if (h >= m)
      h -= m;
    d += 2;
  }
}

char *linear(string str) {
  COL_COUNTER = 0;
  char *a = new char[m];
  for (int i = 0; i < m; i++) {
    a[i] = 0;
  }
  for (auto x : str) {
    bool counterFlag = false;
    auto h = hashFunction(x);
    int d = h;
    bool COL_COUNTER_CHECK = true;
    while (true) {
      if (a[h] == x) {
        break;
      }
      if (a[h] == 0) {
        a[h] = x;
        break;
      };
      if (d == h - 1 && counterFlag) {
        cerr << "ПЕРЕПОЛНЕНИЕ";
        return NULL;
      };
      if (COL_COUNTER_CHECK)
        COL_COUNTER++;
      COL_COUNTER_CHECK = false;
      h++;
      if (h >= m) {
        h -= m;
        counterFlag = true;
      };
    }
  }
  return a;
}

char *quadra(string str) {
  COL_COUNTER = 0;
  char *a = new char[m];
  for (int i = 0; i < m; i++) {
    a[i] = 0;
  }
  for (auto x : str) {
    auto h = hashFunction(x);
    int d = 1;
    bool COL_COUNTER_CHECK = true;
    while (true) {
      if (a[h] == x) {
        break;
      }
      if (a[h] == 0) {
        a[h] = x;
        break;
      };
      if (d >= m) {
        cerr << "ПЕРЕПОЛНЕНИЕ";
        return NULL;
      };

      if (COL_COUNTER_CHECK)
        COL_COUNTER++;
      COL_COUNTER_CHECK = false;

      h += d;
      if (h >= m)
        h -= m;
      d += 2;
    }
  }
  return a;
}

int main() {
  cout << endl;

  string myString = "johnclonnorfgsc";
  cout << "String : " << myString << endl << endl;

  LinkedList *svyazList = pryamSvyaz(myString);
  for (int i = 0; i < m; i++) {
    if (!svyazList[i].head)
      cout << i << " " << endl;
    else {
      cout << i << " ";
      svyazList[i].print();
    }
  }

  cout << endl << endl;

  cout << "linear" << endl;

  char *list = linear(myString);
  int COL1 = COL_COUNTER;
  for (int i = 0; i < m; i++) {
    cout << setw(3) << i;
  }
  cout << endl;
  for (int i = 0; i < m; i++) {
    if (list[i] == 0) {
      cout << setw(3) << " ";
      continue;
    }
    cout << setw(3) << (char)list[i];
  }
  cout << endl << endl << endl;

  cout << "quadra" << endl;

  list = quadra(myString);
  int COL2 = COL_COUNTER;
  for (int i = 0; i < m; i++) {
    cout << setw(3) << i;
  }
  cout << endl;
  for (int i = 0; i < m; i++) {
    if (list[i] == 0) {
      cout << setw(3) << " ";
      continue;
    }
    cout << setw(3) << (char)list[i];
  }

  cout << "\n\n\n";

  cout << "Razmer hesh-tablici       Kolichestvo ishodnih simvolov      "
          "Kolichestvo kolliziy\n";
  cout << "                                                         Lin.       "
          "Kvadr.    \n";
  cout << "   " << m << "                                 " << myString.length()
       << "                   " << COL1 << "          " << COL2 << endl
       << endl
       << endl;

  char toBeFound = 'c';

  cout << "Pryam Svyaz search of " << toBeFound << ": "
       << pryamSvyazSearch(toBeFound, svyazList) << endl;

  list = linear(myString);
  cout << "Linear search of " << toBeFound << ": "
       << linearSearch(toBeFound, list) << endl;

  list = quadra(myString);
  cout << "Quadra search of " << toBeFound << ": "
       << quadraSearch(toBeFound, list) << endl;
}