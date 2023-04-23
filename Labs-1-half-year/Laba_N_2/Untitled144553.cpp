#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int fillinc(int n, int a[]){
	int i;
	 for (int i=0;i<n;i++){
	 a[i]=i;}
	/*int x,i,c;   случайный неубывающий массив
	c=0;
	for(i=0;i<n;){	
		x=rand()%100;
		if(x>=c){a[i]=x;i++;c=x;
		}
	}*/
}
int filldec(int n, int a[]){
     for (int i=0;i<n;i++){
         a[i]=n-i;
         }	        
		/*int x,i,c;  случайный невозрастающий массив
	c=100;
	for(i=0;i<n;){
		x=rand()%100;
		if(x<=c){a[i]=x;i++;c=x;
		}
	}*/
}
int fillrand(int n, int a[]){
		int x,i,c;
	x=0;
	for(i=0;i<n;i++){
		a[i]=rand()%100;
		}
}
int checksum(int n, int a[]){
int i,c;
c=0;
for(i=0;i<n;i++){
	c=c+a[i];
} printf("\nChecksum=%d",c);
return c;
}
int runnum(int n, int a[]){
     int series1=1;
     for (int i=0;i<n-1;i++){
         if (a[i+1]<a[i]) series1++;
         }
         printf("\nnum of series = %d",series1);
     return series1;
     }
int printmas(int n, int a[]){
	int i;
	printf("\n");
	for(i=0;i<n;i++){printf("%d ",a[i]);
	}
}
int selectsort(int n,int a[]){
	int min,k,i,j,m; float c;
	c=0;m=0;
	for(i=0;i<n-1;i++){ 
		min=i;m++;
		for(j=i+1;j<n;j++){
		c++;	if(a[min]>a[j]) {
		m++;min=j;}
		}
		m+=3;
		swap(a[i],a[min]);
	}
	printf("\nsravnenii=%.1f priasvaivanii=%d",c,m);
	c=(n*n-n)/2;
	m=3*(n-1);
	printf("\nTheoretical sravnenii=%.1f Theoretical priasvaivanii=%d",c,m);
}

	
int main(){
		const int n=50;
	int a[n]; int i; float avgs; int series1;
	srand(time(NULL));
	printf("\nIncreasing massive\n");
	fillinc(n,a);
	printmas(n,a);
	runnum(n,a);
	printf("\nDescreasing massive\n");
	filldec(n,a);
	printmas(n,a);
	runnum(n,a);
		printf("\nRandom massive\n");
	fillrand(n,a);
	printmas(n,a);
	avgs=runnum(n,a);
	avgs=n/avgs;
	printf("\n average = %f",avgs);
	printf("\nSelectSort");
	fillrand(n,a);
	checksum(n,a);
	printmas(n,a);
	selectsort(n,a);
	checksum(n,a);
	runnum(n,a);
	printmas(n,a);
	
}
