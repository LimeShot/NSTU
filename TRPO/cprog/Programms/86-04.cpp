#include <stdio.h>
//-----------------------------------------------86-04.cpp
// Построение остового дерева  - алгоритм Крускала
// Слияние кластеров через минимальное ребро
#include "86-00.cpp"

void main(){
	int N,**M,*D;
	int i,k,j;
	int cnt=0, cnt2=0, sum=0,sum0=0;
	if ((M=load_1("86-011.txt",N))==NULL) return;
	D=new int[N];	
	for (i=0;i<N;i++) D[i]=i;	// Каждый сам себе кластер
	for (i=0;i<N;i++) for (j=0;j<i;j++) sum0+=M[i][j];
	while(1){
		cnt++;
		int i1=-1,j1=-1;			// Поиск кратчайшего ребра в разных кластерах
		for (i=0;i<N;i++)
			for (j=i+1;j<N;j++){
				cnt2++;
				if (M[i][j]<=0 || D[i]==D[j]) continue;
				if (j1==-1 || M[i][j]<M[i1][j1])
					{ i1=i; j1=j; }
				}
		if (j1==-1) break;
		sum+=M[i1][j1];
		M[i1][j1]=-M[i1][j1];	// Отметить ребро
		M[j1][i1]=-M[j1][i1];
		int P=D[j1];			// Слить кластеры
		for (j=0;j<N;j++) if (D[j]==P) D[j]=D[i1];
		printf("put=%d-%d[%d]\n",i1,j1,-M[i1][j1]);
		}
	puts("-----------------------------------");
	for (i=0;i<N;i++){ 
		for (j=0;j<N;j++) printf("%2d ",M[i][j]);
		puts("");
		}
	puts("-----------------------------------");
	printf("\nT=%d T2=%d sum0=%d sum=%d\n",cnt,cnt2,sum0, sum);
	}