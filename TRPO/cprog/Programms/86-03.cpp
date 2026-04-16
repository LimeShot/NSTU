#include <stdio.h>
//------------------------------------------------------86-03.cpp
// Построение остового дерева  - алгоритм Прима-Ярвика
// Выбор мин. ребра "в облаке"-"вне облака"
#include "86-00.cpp"

void main(){
	int N,**M,*P;	int i,k,j;
	int cnt=0, cnt2=0, sum=0,sum0=0;
	if ((M=load_1("86-011.txt",N))==NULL) return;
	P=new int[N];
	for (i=0;i<N;i++) P[i]=0;
	for (i=0;i<N;i++) for (j=0;j<i;j++) sum0+=M[i][j];
	P[0]=1;
	while(1){
		cnt++;
		int i1=-1,j1=-1;			// Поиск кратчайшего ребра
		for (i=0;i<N;i++)
			for (j=i+1;j<N;j++){
				cnt2++;
				if (M[i][j]<=0 || P[i]==P[j]) continue;
				if (j1==-1 || M[i][j]<M[i1][j1])
					{ i1=i; j1=j; }
				}
		if (j1==-1) break;
		sum+=M[i1][j1];
		M[i1][j1]=-M[i1][j1];	// Отметить ребро
		M[j1][i1]=-M[j1][i1];
		if (P[i1]==1) P[j1]=1; else P[i1]=1;
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