//------------------------------------------------------46-04.cpp
//---- Проверка упорядоченности массива
 int is_sorted(int a[], int n){
 for (int i=0; i<n-1; i++)
      if (a[i]>a[i+1]) return 0;
 return 1;}

#include <stdio.h>
void main(){
int a[]={1,3,3,5,7,9,12,16,23,35};
int n=sizeof(a)/sizeof(int);
printf("v=%d\n",is_sorted(a,n));
getchar();
}
