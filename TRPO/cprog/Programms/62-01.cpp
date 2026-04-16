//------------------------------------------------------62-01.cpp
//--- Сортировка массива и массива указателей
#include <stdio.h>
 void sort1 (double d[],int sz)
 { int i,k;
	  do {
	  for ( k=0, i=0; i<sz-1; i++)
		   if (d[i] > d[i+1])
		   { double c; c = d[i];
		   d[i] = d[i+1]; d[i+1] = c; k=1;}
	  }while (k); }

 void sort2 (double *pd[])
 { int i,k;
	  do {
	  for ( k=0, i=0; pd[i+1]!=NULL;i++)
		   if (*pd[i] > *pd[i+1])		// Сравнение указуемых переменных
		   {double *c;                  // Перестановка указателей
		   c = pd[i];pd[i] = pd[i+1];pd[i+1] = c; k = 1; }
	  }while (k);}

void main(){ int i;
double dd1[5]={4,2,6,7,8};
double d1=5,d2=3,d3=6,d4=1, *dd2[]={&d1,&d2,&d3,&d4,NULL};
sort1(dd1,5); sort2(dd2);
puts("\nsorted dd1");
for (i=0; i<5; i++) printf("%2.0lf ",dd1[i]);
puts("\nsorted dd2");
for (i=0; dd2[i]!=NULL; i++) printf("%2.0lf ",*dd2[i]);
}
