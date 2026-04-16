//------------------------------------------------------46-08.cpp
//----- Вставка погружением, подозрительно похожая на обмен
 void sort(int in[],int n) {
 for ( int i=1; i<n; i++)	// Пока не достигли " дна" или меньшего себя
	  for ( int k=i; k !=0 && in[k] < in[k-1]; k--){
      int c=in[k]; in[k]=in[k-1]; in[k-1]=c;
      }} 

#include <stdio.h>
void main(){
int a[]={4,7,3,4,8,2,3,6,6,4,9,2,3};
int n=sizeof(a)/sizeof(int);
sort(a,n);
for (int i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
