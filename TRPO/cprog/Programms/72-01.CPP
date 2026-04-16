//------------------------------------------------------72-01.cpp
//------- Сотрировка рекурсивным разделением массива
// В качестве медианы - среднее арифметическое
 void sort(int in[], int a, int b){
 int i,j,mode;
 double sr=0;
 if (a>=b) return;						// Размер части =0
 for (i=a; i<=b; i++) sr+=in[i];
 sr=sr/(b-a+1);
 for (i=a, j=b; i <= j;)
	{
	if (in[i]< sr) { i++; continue; }	// Слева - меньше, пропустить
	if (in[j]>=sr) { j--; continue; }	// Справа - больше, пропустить
	int c = in[i]; in[i] = in[j]; in[j]=c;
	i++,j--;							// Поменять местами и пропустить
	}
 if (i==a) return;						// все равны и в правой части
 sort(in,a,j); sort(in,i,b);}			// рекурсивный вызов для двух частей

#include <stdio.h>
void main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,0,n-1);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
