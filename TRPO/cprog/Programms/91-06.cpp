//------------------------------------------------------91-06.cpp
//----- ѕоразр€дна€ распредел€юща€ сортировка
 void sort(int in[], int n)
 {int m,i,max,i0,i1;
 int *v0=new int[n];				// —оздать 2 "кармана"
 int *v1=new int[n];
 for (i=0, max=0; i<n; i++)
      if (in[i] > max) max=in[i];	// ќпределение максимального
 for (m=1; m <=max; m <<=1);        // значащего разр€да
 for (m >>=1; m !=0; m >>=1){		// ѕо всем разр€дам от старшего
	for (i0=i1=0; i0+i1 < n; )      // –аспределение по значению
		if ((in[i0+i1] & m) ==0)    // очередного разр€да
			v0[i0] = in[i0+i1], i0++;
		else						// по карманам
			v1[i1] = in[i0+i1], i1++;
		v0[i0] = v1[i1] = max+1;	// ¬ каждый карман - "затычка"
 for (i0=i1=0; i0+i1 < n; )			// ќбычное сли€ние 
	if (v0[i0] < v1[i1])			// по сравнению значений 
		in[i0+i1] = v0[i0], i0++;	// в последовательности
    else
		in[i0+i1] = v1[i1], i1++;	// max+1 играет роль ограничител€
    } delete []v0; delete []v1;}

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

