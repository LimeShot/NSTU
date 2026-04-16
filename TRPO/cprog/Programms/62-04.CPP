//------------------------------------------------------62-04.cpp
// Простое однократное слияние - массив указателей
// на линейные массивы (части линейного массива)
#include <math.h>
#include <stdio.h>
void sort(int a[], int n);				// любая сортировка одномерного массива

void big_sort(int A[], int N){
int max=A[0],i,j,k,n=sqrt((double)N);
int **B=new int*[n];
int *L=new int[n],*C=new int[N];		// массив размерностей частей
	for (i=0; i<n; i++) B[i]=&A[i*n];
	for (i=0; i<n-1; i++) L[i]=n;
	L[n-1]=N-n*(n-1);					// Размерность последнего массива - остаток
	for (i=0; i<n; i++) sort(B[i],L[i]);// Сортировка частей
	for (i=0; i<N; i++){                // Слияние
		for (k=-1, j=0; j<n; j++){		// k - индекс строки с минимальным начальным
			if (L[j]==0) continue;		// Пропуск слитых строк
			if (k==-1 || *B[j] < *B[k]) 
				k=j;					
			}
		C[i] = *B[k];					// Перенос элемента
		B[k]++;							// Сдвиг k-го указателя
		L[k]--;
		}
	for (i=0; i<N; i++) A[i]=C[i];		// Возвратить обратно
	delete []B;
	delete []C;
}

#include <stdlib.h>
#include <time.h>
void main(){
int n=1000,*a=new int[n],i;
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
