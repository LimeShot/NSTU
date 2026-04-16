#include <stdio.h>
#include <stdlib.h>
//---------------------------------------------------------72-04.cpp
// —ортировка массива рекурсивным сли€нием
void sort(int A[], int a, int b){
if (a>=b) return;				// –азделение закончилось
int m=(a+b+1)/2,i,j,k;			// Ќет - вз€ть середину интервала
sort(A,a,m-1);					// –екурсивный вызов дл€ частей
sort(A,m,b);
int *tmp=new int[b-a+1];		// —ли€ние частей во временный массив
for (i=a,j=m,k=0; k<=b-a; k++)
	if (i==m || j!=b+1 && A[j]<A[i])
   		tmp[k]=A[j++];			// слить из второй части, если
	else						// перва€ кончилась или во второй меньше
		tmp[k]=A[i++];			// слить из первой части
for (i=a,j=0; i<=b; i++,j++) 
	A[i]=tmp[j];				// вернуть слитые части обратно в A
delete tmp;	}					// удалить временный массив

#define N 100
int main(){
int AA[N],i;
for (i=0; i<N; i++) AA[i]=rand();
printf("\n");
for (i=0; i<N; i++)
	printf("%d ",AA[i]);
sort(AA,0,N-1);
printf("\n");
for (i=0; i<N; i++)
	printf("%d ",AA[i]);
puts("");
}

