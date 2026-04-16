#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//----------------------------------------------83-04.cpp
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

void main(){
int i,N=20;
int *A=new int[N+1];
srand(time(NULL));
for (i=1; i<=N; i++) A[i]=rand()%N;
set_tree(A,N);
scan(A,1,N,0);
}

