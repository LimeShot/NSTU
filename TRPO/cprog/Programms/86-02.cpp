#include <stdio.h>
//------------------------------------------86-02.cpp
// Поиск кратчайшего пути - алгоритм Дейкстры
#include "86-00.cpp"

void min_way(int N, int **M){
	int i,k,j;
	int *P=new int[N];
	int *D=new int[N];
	for (i=0;i<N;i++) P[i]=0,D[i]=100000;
	D[0]=0;
	while(1){
		for (k=-1,i=0;i<N;i++){
			if (P[i]==1) continue;		// В облаке
			if (k==-1 || D[i] < D[k]) 
				k=i;					// Ближайшая вне облака 
			}
		if (k==-1) break;
		P[k]=1;
		printf("put=%d[%d]\n",k,D[k]);
		for (i=0;i<N;i++){
			if (M[k][i]==0) continue;	// Коррекция путей к соседям
			if (D[k] + M[k][i] < D[i])	// - если расстояние уменьшается
				D[i] = D[k] + M[k][i];
			}
		}
	puts("-----------------------------------");
	for (i=0;i<N;i++) printf("%2d ",D[i]);
	printf("\n");
	}

void main(){
	int n,**MM=load_1("86-011.txt",n);
	min_way(n,MM);
	}