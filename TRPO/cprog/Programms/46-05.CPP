//------------------------------------------------------46-05.cpp
//---- Сортировка выбором
 void sort(int in[], int n){
	  int i,j,k; 
      for ( i=0; i < n-1; i++){				// Для очередного i
	  for ( j=i+1, k=i; j<n; j++)			// k - индекс минимального
		if (in[j] < in[k]) k=j;             // в диапазоне i..n-1
	  int c=in[k]; in[k] = in[i]; in[i] = c;// Три стакана для очередного
	  }}                                    // и минимального

#include <stdio.h>
void main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,n);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
