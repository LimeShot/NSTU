#include <stdio.h>
//------------------------------------------------82-01
#define N 100
void main(){
int A[N],n,k,j,v;
printf("v="); scanf("%d",&v);
k=1; A[0]=2;
for (n=3; n<v && k < N; n++)	// Внешний цикл перебора n
	{
	for (j=0; n%A[j]!=0;j++)	// Цикл перебора A[]
		if (j==k-1) {			// A[] закончился -
			A[k++]=n; break; }	// Добавить в A[]
	}							// Альтернативный выход по break
for (j=0;j<k;j++) printf("%d ",A[j]);
}