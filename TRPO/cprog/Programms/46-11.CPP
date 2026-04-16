//------------------------------------------------------46-11.cpp
//------Обменная сортировка "пузырьком"
 void sort(int A[], int n){
 int i,found;				// Количество обменов
      do {                              // Повторять просмотр...
      found =0;
      for (i=0; i<n-1; i++)
                if (A[i] > A[i+1]) {    // Сравнить соседей
           int cc = A[i]; A[i]=A[i+1]; A[i+1]=cc;
           found++;                     // Переставить соседей 
           }
      } while(found !=0); }             //...пока есть перестановки 

#include <stdio.h>
void main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,n);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
