//----------------------------------------------------------91-04.cpp
//--------------- Поразрядная сортировка разделением
void	bitsort(int A[],int a,int b, unsigned m){
int i;
if (a   >= b) return; 		// Интервал сжался в точку
if (m   == 0) return; 		// Проверяемые разряды закончились
// Разделить массив на две части по значению разряда,
// установленного в маске m
int j,vv;		  			// Цикл разделения массива  
for (i=a, j=b; i<=j; ){	  	
	if ((A[i] & m) ==0)		// Слева с разрядом =0 
		{ i++; continue; }	// припустить
	if ((A[j] & m) !=0)		// Справа с разрядом =1 
		{ j--; continue; }	// пропустить
	vv = A[i]; A[i]=A[j]; A[j]=vv;
	i++, j--;				// Обмен и сдвиг границ
	}
bitsort(A,a,j,m >>1);		// Рекурсивный вызов	
bitsort(A,i,b,m >>1); }		// для следующего разряда

void mainsort(int B[], int n){
int max,i; unsigned m;
for(max = 0, i=0; i< n; i++)
	if (B[i] > max) max = B[i];
for (m=1; m < max; m <<= 1);
m >>=1;
bitsort(B,0,n-1,m); }

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main(){
int i,n=100,*a=new int[n];
srand(time(NULL));
for (i=0; i<n; i++) a[i]=rand()%1000;
mainsort(a,n);
for (i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}

