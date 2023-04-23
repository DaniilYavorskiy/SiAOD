#include <iostream>
using namespace std;

class Stack {
public:
  Stack() { head = NULL; }

  void generate_rand(int n);
  void generate_inc(int n);
  void generate_dec(int n);
  void print();
  int control_sum();
  int run_number();
  void clear();
  struct Data {
    int num;
    Data *next = NULL;
  };
  Data *head;
  void print_node(Data *tmp);
};

void Stack::generate_rand(int n) {
  if (n <= 0)
    return;
  if (head)
    clear();
  head = new Data;
  Data *tmp2 = head;
  int i = 0;
  while (i < n) {
    Data *tmp = new Data;
    tmp->num = rand() % 100;
    Data *tmp2 = head->next;
    head->next = tmp;
    tmp->next = tmp2;
    i++;
  }
}

void Stack::generate_inc(int n) {
  if (n <= 0)
    return;
  if (head)
    clear();
  head = new Data;
  Data *tmp2 = head;
  int i = 0;
  while (i < n) {
    Data *tmp = new Data;
    tmp->num = n - i;
    Data *tmp2 = head->next;
    head->next = tmp;
    tmp->next = tmp2;
    i++;
  }
}

void Stack::generate_dec(int n) {
  if (n <= 0)
    return;
  if (head)
    clear();
  head = new Data;
  int i = 0;
  while (i < n) {
    Data *tmp = new Data;
    tmp->num = i + 1;
    Data *tmp2 = head->next;
    head->next = tmp;
    tmp->next = tmp2;
    i++;
  }
}

void Stack::print_node(Data *tmp) { cout << tmp->num << " "; }

void Stack::print() {
  if (head == NULL)
    return;
  if (head->next != NULL) {
    Data *tmp = head->next;
    while (tmp != NULL) {
      print_node(tmp);
      tmp = tmp->next;
    }
    cout << endl;
  }
}

int Stack::control_sum() {
  if (head == NULL)
    return 0;
  int sum = 0;
  if (head->next != NULL) {
    Data *tmp = head->next;
    while (tmp != NULL) {
      sum += tmp->num;
      tmp = tmp->next;
    }
  }
  return sum;
}

int Stack::run_number() {
  if (head == NULL)
    return 0;
  int k = 1;
  if (head->next != NULL) {
    Data *tmp = head->next;
    while (tmp->next != NULL) {
      if (tmp->num >= tmp->next->num)
        k++;
      tmp = tmp->next;
    }
  }
  return k;
}

void Stack::clear() {
  Data *tmp = head;
  Data *next;
  while (tmp != NULL) {
    next = tmp->next;
    delete tmp;
    tmp = next;
  }
  head = NULL;
}

int main() {
  int n = 5;

  Stack *list = new Stack;
  cout << "INC:" << endl;
  list->generate_inc(n);
  list->print();
  cout << "Control sum = " << list->control_sum() << endl;
  cout << "Number of series = " << list->run_number() << endl << endl;
  
  cout << "DEC:" << endl;
  list->generate_dec(n);
  list->print();
  cout << "Control sum = " << list->control_sum() << endl;
  cout << "Number of series = " << list->run_number() << endl << endl;

  cout << "RAND:" << endl;
  list->generate_rand(n);
  list->print();
  cout << "Control sum = " << list->control_sum() << endl;
  cout << "Number of series = " << list->run_number() << endl << endl;

  list->clear();
  delete list;
  list = NULL;
}
