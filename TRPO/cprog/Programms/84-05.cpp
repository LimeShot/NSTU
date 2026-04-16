#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXINT 1000000
//----------------------------------------------84-05.cpp
// Пирамидальная сортировка - построение пирамиды

// Обход дерева предок N  - два потомка 2N 2N+1
void scan(int A[], int k, int n, int l){
if (k>n) return;
for (int i=0; i<l;i++) printf(" ");	// отступ-пропорционально глубине
printf("[%d]=%d\n",k,A[k]);
scan(A,2*k,n,l+1);
scan(A,2*k+1,n,l+1);
}

// Погружение в дерево путем обмена с предком
void set_tree(int A[],int n){
int l,i;
for (l=2;l<=n;l++){				// l - индекс погружаемой вершины
   for (i=l; i!=1;i=i/2){		// индекс предка = i/2
      if (A[i]>A[i/2]) break;	// предок меньше потомка - выйти
		int c=A[i];				// поменяться с предком
		A[i]=A[i/2];
		A[i/2]=c;
   		}}}

// Сортировка - n раз выбрать из дерева с замещением на минимального потомка
// Извлекаемые элементы в конце массива, не имеющие потомков,
// заменяются на  MAXINT. Значение MAXINT обозначает отсутствие вершины
void sort(int A[],int B[], int n){
for (int i=1; i<=n; i++){		// повторить n раз
	int j,k;
	B[i]=A[1];
	for (j=1;j<=n;j=k){									// j=k - переход к замещающему потомку
		k=2*j;											// k - левый потомок
		if (k>n)	{ A[j]=MAXINT; break; }				// нет потомков - MAXINT (затычка)
		if (k+1>n)	{ A[j]=A[k]; A[k]=MAXINT; break; }	// нет второго потомка - взять первого
		if (A[k+1]<A[k]) k++;							// иначе - выбрать минимального из них
   		A[j]=A[k];										// скопировать значение потомка в предка
   	}}}

void main(){
int i,N=20;
int *A=new int[N+1];
int *B=new int[N+1];
srand(time(NULL));
for (i=1; i<=N; i++) A[i]=rand()%N;
set_tree(A,N);
scan(A,1,N,0);
sort(A,B,N);
for (i=1; i<=N; i++)
	printf("%d ",B[i]);
puts("");
}
