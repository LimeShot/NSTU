#include <stdio.h>
//------------------------------------------------------52-03.cpp
//----- Функция возвращает указатель на минимальный элемент массива
 int *ptr_min(int *p, int n){
 int *pmin;
 for (pmin=p; n>0; p++,n--)
	  if (*p < *pmin) pmin=p;
 return pmin;}
 void main(){
	  int B[5]={4,8,2,6,4};
 (*ptr_min(B,5))++;
 for (int i=0; i<5; i++) printf("%d ",B[i]); }
