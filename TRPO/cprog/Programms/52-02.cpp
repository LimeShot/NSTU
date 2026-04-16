#include <stdio.h>
//------------------------------------------------------52-02.cpp
//----- Функция возвращает ссылку на минимальный элемент массива
 int &ref_min(int A[], int n){
 int i,k;
 for (i=0,k=0; i<n; i++)
	  if (A[i]<A[k]) k=i;
 return A[k];}
 void main(){
 int B[5]={4,8,2,6,4};
 ref_min(B,5)++;
 for (int i=0; i<5; i++) printf("%d ",B[i]);
 }
