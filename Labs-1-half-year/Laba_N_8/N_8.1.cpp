#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>

int random (int N) { return rand()%N; }
int mp=0, cp=0;

void Swap (int &x, int &y);
void TelSprav();
void SelectSort_Struct (int A[], int n, int z);

int Less (struct sprav x, struct sprav y, int z);

struct sprav {
	char fam[12];
	char name[12];
	char city[15];
	char index[10];
	char phone[16];
};

struct sprav abonent[5];


main() {
	TelSprav();
	system("PAUSE");
	return 0;
}


void Swap (int &x, int &y) {
	int t=x; x=y; y=t;
}

void zap () {
	strcpy (abonent[0].fam, "Fatyanova");
	strcpy (abonent[1].fam, "Olhovoy");
	strcpy (abonent[2].fam, "Budnikova");
	strcpy (abonent[3].fam, "Yavorskiy");
	strcpy (abonent[4].fam, "Baburin");
	strcpy (abonent[0].name, "Viktoriya");
	strcpy (abonent[1].name, "Nikita");
	strcpy (abonent[2].name, "Mariya");
	strcpy (abonent[3].name, "Daniill");
	strcpy (abonent[4].name, "Ivan");
	strcpy (abonent[0].city, "Chicago");
	strcpy (abonent[1].city, "Novosibirsk");
	strcpy (abonent[2].city, "New-York");
	strcpy (abonent[3].city, "Paris");
	strcpy (abonent[4].city, "Tomsk");
	strcpy (abonent[0].index, "894745");
	strcpy (abonent[1].index, "105745");
	strcpy (abonent[2].index, "236557");
	strcpy (abonent[3].index, "659812");
	strcpy (abonent[4].index, "965482");
	strcpy (abonent[0].phone, "7(913)889-12-99");
	strcpy (abonent[1].phone, "7(987)012-98-87");
	strcpy (abonent[2].phone, "7(913)393-15-15");
	strcpy (abonent[3].phone, "7(915)982-87-62");
	strcpy (abonent[4].phone, "7(878)010-32-88");
}

void TelSprav() {
	zap ();
	int i, n=5;
	int a[n], b[n];
	for (i=0; i<n; i++) a[i]=b[i]=i;
	SelectSort_Struct (a, n, 0);
	SelectSort_Struct (b, n, 1);
	for (i=0; i<n; i++) {
		printf ("%s ", abonent[i].fam);
		printf ("%s ", abonent[i].name);
		printf ("%s ", abonent[i].city);
		printf ("%s ", abonent[i].index);
		printf ("%s ", abonent[i].phone);
		printf("\n");
	}
	printf("\nSecond name\n\n");
	for (i=0; i<n; i++) {
		printf ("%s ", abonent[a[i]].fam);
		printf ("%s ", abonent[a[i]].name);
		printf ("%s ", abonent[a[i]].city);
		printf ("%s ", abonent[a[i]].index);
		printf ("%s ", abonent[a[i]].phone);
		printf("\n");
	}
	printf("\nCity\n\n");
	for (i=0; i<n; i++) {
		printf ("%s ", abonent[b[i]].city);
		printf ("%s ", abonent[b[i]].index);
		printf ("%s ", abonent[b[i]].fam);
		printf ("%s ", abonent[b[i]].name);
		printf ("%s ", abonent[b[i]].phone);
		printf("\n");
	}
}

void SelectSort_Struct (int A[], int n, int z) {
	int i, j ,k, t;
	for (i=0; i<(n-1); i++) {
		k=i;
		for (j=i+1; j<n; j++) {
			if (Less (abonent [A[j]], abonent [A[k]], z)) k=j;
		}
		if (k!=i) {
			Swap (A[i], A[k]);
		}
	}
}

int Less (struct sprav x, struct sprav y, int z) {
	int i;
	switch (z) {
		case 0: i=strcmp (x.fam, y.fam);
			if (i<0) return 1;
			else return 0;
			break;
		case 1: i=strcmp (x.city, y.city);
			if (i<0) return 1;
			else return 0;
			break;
	}
}