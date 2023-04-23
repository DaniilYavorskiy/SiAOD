#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

int random (int N) { return rand()%N; }
int mp=0, cp=0, rec=0;

void FillIncStack (struct stack **head, int n);
void FillIncQueue (struct stack **head, struct stack **tail, int n);
void FillDecStack (struct stack **head, int n);
void FillDecQueue (struct stack **head, struct stack **tail, int n);
void FillRandStack (struct stack **head, int n);
void FillRandQueue (struct stack **head, struct stack **tail, int n);
void DeleteStack (struct stack **head);
void DeleteQueue (struct stack **head, struct stack **tail);
void CheckSumStack (struct stack *head);
void RunNumberStack (struct stack *head);
void PrintStack (struct stack *head);
void Swap (int &x, int &y);
void ResultOld (int n);
void DigitalSort (stack **head, stack **tail);

struct stack 
{
	struct stack *next;
	union 
	{
		int data;
		unsigned char digit [sizeof(int)];
	};
};

struct Queue {
	stack *head;
	stack *tail;
};

main() {
	stack *head, *tail;
	head=NULL;
	tail=(stack*)&head;
	int n;
	printf ("Vvedite razmer steka: \n");
	scanf("%d", &n);
	///////////////////////////////////////////////////// прямой
	//FillRandQueue (&head, &tail, n);
	printf ("FillIncStack(ne otsortirovanniy):\n");
	FillIncQueue(&head, &tail, n);
	PrintStack (head);
	printf("\n");
	printf ("Summa: ");
	CheckSumStack (head);
	printf("\n");
	printf ("Kolichestvo seriy: ");
	RunNumberStack (head);
	
	printf ("\n");
	printf ("FillIncStack(sortirovanniy):\n");
	DigitalSort (&head, &tail);
	PrintStack (head);
	printf("\n");
	printf ("Summa: ");
	CheckSumStack (head);
	printf("\n");
	printf ("Kolichestvo seriy: ");
	RunNumberStack (head);
	ResultOld (n);
	DeleteQueue(&head, &tail);
	printf ("\n");
	printf ("\n");
	/////////////////////////////////////////////////
	printf ("FillDecStack(ne otsortirovanniy):\n");
	FillDecQueue(&head, &tail, n);
	PrintStack (head);
	printf("\n");
	printf ("Summa: ");
	CheckSumStack (head);
	printf("\n");
	printf ("Kolichestvo seriy: ");
	RunNumberStack (head);
	
	printf ("\n");
	printf ("FillDecStack(sortirovanniy):\n");
	DigitalSort (&head, &tail);
	PrintStack (head);
	printf("\n");
	printf ("Summa: ");
	CheckSumStack (head);
	printf("\n");
	printf ("Kolichestvo seriy: ");
	RunNumberStack (head);
	ResultOld (n);
	printf ("\n");
	printf ("\n");
	system("PAUSE");
	return 0;
}


void FillIncStack (struct stack **head, int n) {
	int i;
	struct stack *p;
	for (i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		p->next=*head;
		*head=p;
	}
}

void FillIncQueue (struct stack **head, struct stack **tail, int n) {
	int i;
	struct stack *p;
	for (i=1; i<=n; i++) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		(*tail)->next=p;
		*tail=p;
	}
	(*tail)->next=NULL;
}

void FillDecStack (struct stack **head, int n) {
	int i;
	struct stack *p;
	for (i=1; i<=n; i++) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		p->next=*head;
		*head=p;
	}
}

void FillDecQueue (struct stack **head, struct stack **tail, int n) {
	int i;
	struct stack *p;
	for (i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=i;
		(*tail)->next=p;
		*tail=p;
	}
	(*tail)->next=NULL;
}

void FillRandStack (struct stack **head, int n) {
	int i, a=0, b=1024;
	srand(time(NULL));
	struct stack *p;
	for (i=n; i>0; i--) {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=random(b-a+1)+a;
		p->next=*head;
		*head=p;
	}
}

void FillRandQueue (struct stack **head, struct stack **tail, int n) 
{
	int i, a=0, b=2*n;
	srand(time(NULL));
	struct stack *p;
	for (i=n; i>0; i--) 
    {
		p=(stack *)malloc(sizeof(struct stack));
		p->data=random(b-a+1)+a;;
		(*tail)->next=p;
		*tail=p;
	}
	(*tail)->next=NULL;
}

void DeleteStack (struct stack **head) 
{
	int i;
	struct stack *p=*head;
	while (p!=NULL) 
    {
		*head=p->next;
		free (p);
		p=*head;
	}
}

void DeleteQueue (struct stack **head, struct stack **tail) 
{
	DeleteStack (head);
	*tail=NULL;
	*tail=(stack*)&(*head);
}

void CheckSum (int A[], int n) 
{
	int i, s;
	for (s=0, i=0; i< n; i++) s+=A[i];
	printf ("\n%d", s);
}

void CheckSumStack (struct stack *head) 
{
	int s=0;
	struct stack *p=head;
	while (p!=NULL) 
    {
		s+=p->data;
		p=p->next;
	}
	printf ("\n%d", s);
}

void RunNumber (int A[], int n) 
{
	int i, c;
	for (c=1, i=1; i< n; i++) if (A[i-1]>A[i]) c++;
	printf ("\n%d\n", c);
}

void RunNumberStack (struct stack *head) 
{
	int c=1;
	if (head!=NULL) 
    {
		struct stack *p=head, *q=p->next;	
		while (q!=NULL) 
        {
			if (p->data>q->data) c++;
			p=p->next;
			q=p->next;
		}
		printf ("\n%d\n", c);
	}
	else printf ("\n%d\n", 0);
}

void PrintStack (struct stack *head) 
{
	struct stack *p=head;
	while (p!=NULL) 
    {
		printf ("%3d ", p->data);
		p=p->next;
	}
}

void ResultOld (int n) 
{
	printf ("\nC(t)=%f, M(t)=%f, T(t)=%f", n*log2(n), n*log2(n), 2*n*log2(n));
	//printf ("\nC(p)=%d, M(p)=%d, T(p)=%d", cp, mp, cp+mp);
}

void DigitalSort (stack **head, stack **tail) 
{
	int d, i, j, k, l=sizeof(int);
	stack *p;
	Queue q[256];
	for (j=l; j>0; j--) 
    {
		for (i=0; i<256; i++) q[i].tail=(stack*)&q[i].head;
		p=*head;
		k=sizeof(int)-1-j;
		while (p!=NULL) 
        {
			d=p->digit[k];
			q[d].tail->next=p;
			q[d].tail=p;
			p=p->next;
		}
		p=(stack*)&(*head);
		for (i=0; i<256; i++) 
        {
			if (q[i].tail!=(stack*)&q[i].head) 
            {
				p->next=q[i].head;
				p=q[i].tail;
			}
		}
		p->next=NULL;
	}
}