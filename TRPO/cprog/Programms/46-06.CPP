//------------------------------------------------------46-06.cpp
//---- "Законспирированная" сортировка выбором
 void sort(int in[], int n){ 
 for ( int i=0; i < n-1; i++)					// Для очередного i
 for ( int j=i+1, k=i; j<n; j++)				// Для всех оставшихся 
	  if (in[j] < in[ i]) {						// в диапазоне i..n-1
      int c=in[i]; in[i] = in[j]; in[j] = c; 
      }											// сразу же менять с очередным 
 }												// Выбор совмещен с обменом

#include <stdio.h>
void main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,n);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
