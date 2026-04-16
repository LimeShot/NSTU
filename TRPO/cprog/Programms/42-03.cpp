//------------------------------------------------------42-03.cpp
//-------Простые числа
 void calc(int val, int A[], int n){
 int i,m,k;
	  for (i=0, m=2; i < n-1 && m < val; m++) {
	  for (k=0; k < i; k++)
		   if (m % A[k]==0) break;
	  if (i==k)
		   A[i++] = m;
	  }
 A[i] = 0;}

 #include <stdio.h>
 void main(){
 int B[100],v=200; calc(v,B,100);
 for (int i=0; B[i]!=0; i++) printf("%d ",B[i]);
 puts("");}
