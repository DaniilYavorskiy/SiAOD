#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>

using namespace std;

int random (int N) {
	return rand()%N; 
}

void FillInc (int A[], int n); 
void FillDec (int A[], int n); 
void FillRand (int A[], int n); 
void CheckSum (int A[], int n); 
void RunNumber (int A[], int n); 
void PrintMas (int A[], int n); 
void BubbleSort (int A[], int n);
void ShakerSort (int A[], int n);
void TablResult (int A[], int n);

int Mprak = 0, Cprak = 0;

main() {
	int n = 500, A[n];
	
	FillRand (A, n);
	cout<<"FillRand"<<endl;
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	cout<<"M(teor(sr)) = "<<3*(n*n-n)/4<<", "<<"C(teor(max)) = "<<(n*n-n)/2<<endl;
	
	ShakerSort (A,n);
	cout<<endl<<"ShakerSort(Random)"<<endl;
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	cout<<"M(prak) = "<<Mprak<<", "<<"C(prak) = "<<Cprak<<endl;
	cout<<endl;
	
	cout<<"FillInc"<<endl;
	FillInc (A,n);
	PrintMas (A,n);
	CheckSum (A,n);
	RunNumber (A,n);
	cout<<"M(teor) = "<<0<<", "<<"C(teor(max)) = "<<(n*n-n)/2<<endl;
	
	ShakerSort (A,n);
	cout<<endl<<"ShakerSort(FillInc)"<<endl;
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	cout<<"M(prak) = "<<Mprak<<", "<<"C(prak) = "<<Cprak<<endl;
	cout<<endl;
	
	cout<<"FillDec"<<endl;
	FillDec (A,n);
	PrintMas (A,n);
	CheckSum (A,n);
	RunNumber (A,n);
	cout<<"M(teor) = "<<3*(n*n-n)/2<<", "<<"C(teor(max)) = "<<(n*n-n)/2<<endl;
	
	ShakerSort (A,n);
	cout<<endl<<"ShakerSort(FillDec)"<<endl;
	PrintMas (A, n);
	CheckSum (A, n);
	RunNumber (A, n);
	cout<<"M(prak) = "<<Mprak<<", "<<"C(prak) = "<<Cprak<<endl;
	cout<<endl;
	
	
	TablResult (A,100);
	printf ("\n\n");
	printf ("\n");
	system("PAUSE");
	return 0;
}

void FillInc (int A[], int n) {
	for (int i=0; i<n; i++){
		A[i]=i+1;
	}
}

void FillDec (int A[], int n) {
	for (int i=0; i<n; i++){
		 A[i] = n-i;
	}
}

void FillRand (int A[], int n) {
	int a=0,b=10;
	srand(time(NULL));
	for (int i=0; i<n; i++) {
		A[i] = random(b-a+1)+a;
	}
}

void CheckSum (int A[], int n) {
	int i, s;
	for (s=0, i=0; i < n; i++){ 
		s+=A[i];
	}
	cout<<endl<<"CheckSum = "<<s; 
}

void RunNumber (int A[], int n) {
	int i, c;
	for (c = 1, i = 1; i < n; i++){
		if (A[i-1]>A[i]){
			c++;
		}
	}
	cout<<endl<<"RunNumber = "<<c<<endl;
}

void PrintMas (int A[], int n) {
	for (int i=0; i<n; i++){
		cout<<A[i]<<" ";
	}
}

void BubbleSort (int A[], int n) {
	Mprak=0, Cprak=0;
	int i,j,t;
	for (i = 0; i < n-1; i++){
		for (j=n-1; j>i; j--){
			Cprak++;
			if (A[j]<A[j-1]){
				t=A[j];
				A[j]=A[j-1];
				A[j-1]=t;
				Mprak+=3;
			}
		}
	}
}

void TablResult(int A[], int n){
	cout<<"|     n    | FillDec(Bubble)|FillRand(Bubble)|FillInc(Bubble)|FillDec(Shaker)|FillRand(Shaker)|FillInc(Shaker)|";
	for (; n<600; n+=100){
		cout<<endl<<"|"<<"    "<<n<<"   "<<"|";
		FillDec(A,n);
		BubbleSort(A,n);
		cout<<"    "<<Mprak+Cprak<<"       |";
		FillRand(A,n);
		BubbleSort(A,n);
		cout<<"      "<<Mprak+Cprak<<"     |";
		FillInc(A,n);
		BubbleSort(A,n);
		cout<<"      "<<Mprak+Cprak<<"     |";
		FillDec(A,n);
		ShakerSort(A,n);
		cout<<"    "<<Mprak+Cprak<<"       |";
		FillRand(A,n);
		ShakerSort(A,n);
		cout<<"    "<<Mprak+Cprak<<"       |";
		FillInc(A,n);
		ShakerSort(A,n);
		cout<<"    "<<Mprak+Cprak<<"       |";
	}
}

void ShakerSort (int A[], int n) {
	Mprak=0, Cprak=0;
	int left,right,i,j,k,w;
	left=0;
	right=n-1;
	k=n-1;
	do {
		for(j=right; j>left; j-- ){ 
			Cprak++;
			if (A[j]<A[j-1]) { 
				w=A[j];
		  	 	A[j]=A[j-1];
			  	A[j-1]=w;
		  	 	k=j;
		  	 	Mprak+=3;
			}
		}
		left=k;
		for(j=left; j<right; j++ ){ 
			Cprak++;
	   		if(A[j]>A[j+1]){  
	   			w=A[j];
	  	 		A[j]=A[j+1];
	   			A[j+1]=w;
	   			k=j;
	   			Mprak+=3;
			}
		}
		right=k;
	}
	while( left<right );
}
