//------------------------------------------------------62-02.cpp
//-------- Динамический массив указателей 
// на упорядоченные положительные элементы исходного массива
#include <stdio.h>
void sort2 (double *pd[])
{ int i,k;
  do {
	 for ( k=0, i=0; pd[i+1]!=NULL;i++)
		if (*pd[i] > *pd[i+1])	
			{double *c;           
			c = pd[i];pd[i] = pd[i+1];pd[i+1] = c; k = 1; }
		}while (k);}

double **create( double in[], int n){
int i,j,m;
for (i=0,m=0; i<n; i++) if (in[i]>0) m++;
double **pp = new double *[m+1];	// Создать ДМУ
pp[m]=NULL;
for (i=0,j=0; i<n; i++)				// Запомнить указатель на 
	if (in[i]>0) pp[j++]=&in[i];	// положительный элемент
sort2(pp);
return pp;} 

void main(){
double dd1[5]={-4,2,-6,7,8};
double **pd=create(dd1,5);
for (int i=0; pd[i]!=NULL; i++) printf("%2.0lf ",*pd[i]);
puts("");
}
