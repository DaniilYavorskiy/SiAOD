#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillInc(int arr[], int n);
void FillDec(int arr[], int n);
void FillRand(int arr[], int n);
void PrintMas(int arr[], int n);
void CheckSum(int arr[], int n);
void RunNumber(int arr[], int n);

//перечисление функций

void SelectSort(int arr[], int n)
{
	int i, g, C, j, k, min, index;
	g = 0; C = 0;
	for (i = 0; i < n-1; i++) //цикл для полной сортировки
	{
		min = arr[i]; g++;
		index = i;
		for (j = i+1; j < n; j++)
		{
			C++;
			if (arr[j] < min) 
			{
				min = arr[j]; g++;
				index = j;
			}
			
		}
		k = arr[i];
		g++;
		arr[i] = arr[index];
		g++;
		arr[index] = k;
		
	}
	printf("g = %d, C = %d\n", g, C);
	
}

main()
{
	int n, TrueM, M, TrueC, C;
	printf("Type array size: ");
	scanf("%d", &n);
	int arr[n];
	TrueM = 3 * (n-1);
	TrueC = (n * n - n) / 2;
	
	FillInc(arr, n);
	
	printf("Initial array: ");
	PrintMas(arr, n);
	CheckSum(arr, n);
	RunNumber(arr, n);
	printf("True M = %d, True C = %d\n", TrueM, TrueC);
	
	SelectSort(arr, n);
	printf("Sort array: ");
	PrintMas(arr, n);
	CheckSum(arr, n);
	RunNumber(arr, n);
}

void FillDec(int arr[], int n)
{
	int beginNum = 10;
	for (int i = 0; i < n; i++) 
	{
		arr[i] = beginNum - i;
	}
	
}

void FillInc(int arr[], int n)
{
	int beginNum;
	beginNum = 1;
	for (int i = 0; i < n; i++) 
	{
		arr[i] = beginNum + i;
	}
	
}

void FillRand(int arr[], int n)
{
	int limit = 20;
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % limit;
	}
	
}

void CheckSum(int arr[], int n)
{
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += arr[i];
	}
	
	printf("Summ: %d\n", sum);
}

void PrintMas(int arr[], int n)
{
	for (int i = 0; i < n; i++) 
	{
		printf("%d ", arr[i]);
	}
	
	printf("\n");
}

void RunNumber(int arr[], int n)
{
	int number = 1 ;
	for (int i = 0; i < n - 1; i++)
	{
		if (arr[i] > arr[i + 1]) number++;
	}

	printf("Amount of serias: %d\n", number);
	
	system("pause");
}