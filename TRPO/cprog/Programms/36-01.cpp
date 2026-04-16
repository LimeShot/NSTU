//------------------------------------------------------36-01.cpp
//---- Сортировка выбором. Окончательный вариант.
 void sort(int A[], int n){
 for(int i=0; i<n; i++){	// i длина отсортированной части 
      int k;                // k индекс минимального элемента 
      int v;                // v сохраненное выбранное значение
      int j;
      for(k=j=0; j<n-i; j++)		// Ф3
			if (A[j]>A[k]) k=j;		
      v=A[k];                       // Ф4 
      for(j=k; j<n-i-1; j++)        // Ф5 
			A[j]=A[j+1];
      A[n-i-1]=v;                   // Ф6
      }}
 
#include <stdio.h>
void main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,n);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
