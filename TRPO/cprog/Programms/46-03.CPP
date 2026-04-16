//------------------------------------------------------25-01.cpp
//------ Дилетантская сортировка
 void sort(int A[], int n){
 for (int i=0; i<n; i++)
	  for (int j=i; j<n; j++)
				if (A[i]>A[j]){
	  int c=A[i]; A[i]=A[j]; A[j]=c;}
 }

#include <stdio.h>
int main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,n);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
getchar();
}
