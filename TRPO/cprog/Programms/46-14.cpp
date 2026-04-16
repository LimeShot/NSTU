
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//-------------------------------------------------46-14.cpp
//---------  Сортировка подсчетом
void sort(int in[],int n){ 
	int i,j,cnt;
	int *out=new int[n];					// выходной массив
	for (i=0; i<n; i++){
		for ( cnt=0,j=0; j<n; j++)			// для in[i] подсчет
           if (in[j] < in[i]) cnt++;		// меньших его
      else									// а также равных ему 
           if (in[j]==in[i] && j<i) cnt++;	// стоящих слева
      out[cnt]=in[i];						// место в выходном
      } 
	for (i=0; i<n; i++) in[i]=out[i];		// определяется счетчиком
	delete []out;
}


void main(){
int i,n=1000,*a=new int[n];
srand(time(NULL));
for (i=0; i<n; i++) a[i]=rand()%1000;
sort(a,n);
for (i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}
