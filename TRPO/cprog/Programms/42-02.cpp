//------------------------------------------------------42-02.cpp
//------Простые множители числа
 void calc(int val, int A[], int n){
 int m,i;
	  for (i=0; i<n-1 && val !=1; i++){
	  for (m=2; val % m !=0; m++);
	  val /= m; A[i] = m;
	  }
 A[i] = 0;}

 #include <stdio.h>
 void main(){
 int B[20],v=96; calc(v,B,20);
 for (int i=0; B[i]!=0; i++) printf("%d*",B[i]);
 printf("=%d\n",v);}
