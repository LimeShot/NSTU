//------------------------------------------------------72-02.cpp
//-------"Быстрая" сортировка
 void sort(int in[], int a, int b){
 int i,j,mode;
 if (a>=b) return;                                  // Размер части =0
 for (i=a, j=b, mode=1; i < j; mode >0 ? j-- : i++)
		   if (in[i] > in[j]){           // Перестановка концевой пары
	  int c = in[i]; in[i] = in[j]; in[j]=c;
	  mode = -mode;                    // со сменой сокращаемого конца
	  }
 sort(in,a,i-1); sort(in,i+1,b);}

#include <stdio.h>
void main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,0,n-1);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
