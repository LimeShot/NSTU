#include <stdio.h>
//------------------------------------------------------35-03.cpp
//----------- Сортировка выбором - восходящее программирование
void sort(int A[],int n){
// Шаг 1. 
 int j,k;
 for (k=0,j=1;j<n;j++)
	 if (A[j]<A[k]) k=j;
 int c=A[0]; A[0]=A[k]; A[k]=c;
}
void sort(int A[],int n){
// Шаг 2.
 int i,j,k;
 for (i=0;i<n-1;i++){
	int j,k;
	for (k=i,j=i+1;j<n;j++)
		if (A[j]<A[k]) k=j;
	int c=A[i]; A[i]=A[k]; A[k]=c;
	}
}
