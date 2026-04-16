//------------------------------------------------------46-15.cpp
//------- Простое однократное слияние
#include <math.h>
#include <stdio.h>
void sort(int a[], int n);		// любая сортировка одномерного массива

void big_sort(int A[], int N){
int max=A[0],i,j,k,n=sqrt((double)N);
	if (n*n!=N) n++;
int **B=new int*[n];
	for (i=0; i<n; i++) B[i]=new int[n];
	for (i=0; i<N; i++) {
		B[i/n][i%n]=A[i];
		if (A[i]>max) max=A[i];			// Распределение
		}
	for (j=N; j<n*n;j++)				// Заполнение "хвоста"
		B[j/n][j%n]=max+1;
	for (i=0; i<n; i++) sort(B[i],n);	// Сортировка частей
	for (i=0; i<N; i++){                // Слияние
	for (k=0, j=0; j<n; j++)			// Индекс строки с минимальным 
		if (B[j][0] < B[k][0]) k=j;     // начвальным B[k][0]
	A[i] = B[k][0];                     // Перенос элемента
	for (j=1; j<n; j++) 
		B[k][j-1]=B[k][j];				// Сдвиг сливаемой строки
	B[k][n-1]=max+1;                    // Запись ограничителя
	}
for (i=0; i<n; i++) delete []B[i];
delete []B;
}

#include <stdlib.h>
#include <time.h>
void main(){
int i,n=1000,*a=new int[n];
srand(time(NULL));
for (i=0; i<n; i++) a[i]=rand()%1000;
big_sort(a,n);
for (i=0; i<n; i++) printf("%d ",a[i]);
puts("");
}


//------Сортировка методом "пузырька"
 void sort(int A[], int n){
 int i,found;                                  // Количество сравнений
      do {                                    // Повторять просмотр...
      found =0;
      for (i=0; i<n-1; i++)
                if (A[i] > A[i+1]) {               // Сравнить соседей
           int cc = A[i]; A[i]=A[i+1]; A[i+1]=cc;
           found++;                            // Переставить соседей 
           }
      } while(found !=0); }               //...пока есть перестановки 
