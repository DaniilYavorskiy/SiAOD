#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdlib.h>
#include <locale.h>
#include <locale.h>

const int n = 5;
int A[n];

int FillInc(){
	for (int i = 0; i < n; i++){
		A[i] = i + 1;
	printf("%d ",A[i]);
	}
}


int FillDec() {
	for (int i = 0; i < n; i++){
		A[i] = n - i;
	printf("%d ",A[i]);
	}
}

void FillRand(){
     for (int i = 0; i < n; i++){
         A[i]=rand() % 30;
printf("%d ",A[i]);
	}
}

int CheckSum(){
     int s = 0;
     for (int i = 0; i < n; i++){
         s+= A[i];
         }
     return s;
     }

int RunNumber(){
	 int count = 0;
	 int num = 1;
	 for (int i = 0; i < n - 1; i++){
	 	if (A[i] < A[i+1]){
		num++;
		} else if (num !=1) {
			num = 1;
			count++;
			}
		}
	 if (num > 1) count++;
	 return count;
}

void PrintMas (){
	 for (int i = 0; i < n; i++){
	 printf("%d ",A[i]);
		 }
	 }

int main(){
setlocale(LC_ALL, "Rus");

//Задание_№1

printf("FillInc\n");
FillInc();
printf("\n\n");
printf("FillDec\n");
FillDec();
printf("\n\n");
printf("FillRand\n");
FillRand();
printf("\n\n");
int sum = CheckSum();
printf("CheckSum %d\n\n",sum);
int x = RunNumber();
printf("RunNumber %d\n\n",x);
printf("PrintMas\n");
PrintMas();

//Задание_№2

printf("\n\n\n");
FillInc();
x = RunNumber();
printf("\Number of series - %d\n\n",x);
FillDec();
x = RunNumber();
printf("\Number of series - %d\n\n",x);
}
