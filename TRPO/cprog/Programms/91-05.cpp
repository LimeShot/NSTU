//------------------------------------------------------91-05.cpp
//----- Поразрядная лексикографическая сортировка
 void sort(int in[], int n)
 {int m,i,max,i0,i1;
 int *v0=new int[n];
 int *v1=new int[n];
 for (i=0, max=0; i<n; i++)
      if (in[i] > max) max=in[i];
 for (m=1; m<=max; m <<=1){		// для каждого разряда, начиная с младшего
	for (i=i0=i1=0;i<n;i++)		// распределить в 2 кармана по значению
		if ((in[i] & m)==0)
			v0[i0++]=in[i];		// разряда
		else v1[i1++]=in[i];
	for(i=0;i<i0;i++)			// соединить карманы первый - второй
		in[i]=v0[i];
	for(i0=0;i<n;i++,i0++)		// соединить карманы первый - второй
		in[i]=v1[i0];
	}
 delete []v0; delete []v1;}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void main(){
int i,n=100,*a=new int[n];
srand(time(NULL));
for (i=0; i<n; i++) a[i]=rand()%1000;
sort(a,n);
for (i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}

