#include <stdio.h>
#include <stdlib.h>
// Поиск кратчайшего пути - ВОЛНОВОЙ АЛГОРИТМ

int N=20,**M,*D,*P,*Q,cnt=0,cnt2=0;
#include "randomatrix.cpp"

int fst=0,lst=0;

void put(int m)	{ Q[lst++]=m; if (lst==10*N) lst=0; }
int  get()		{ if (lst==fst) return -1; 
				int v=Q[fst++]; if (fst==10*N) fst=0; 
				return v;
				}

void main(){
	int i,k,j;
	cnt=0; cnt2=0;
	randomatrix(N,10,12);
	D=new int[N];
	Q=new int[10*N];
	for (i=0;i<N;i++) D[i]=100000;
	D[0]=0;
	put(0);
	while((k=get())!=-1){
		cnt++;
		printf("get=%d[%d]\n",k,D[k]);
		for (i=0;i<N;i++){
			cnt2++;
			if (M[k][i]==0) continue;	// Коррекция путей к соседям
			if (D[k] + M[k][i] < D[i])	// - если расстояние уменьшается
				{
				D[i] = D[k] + M[k][i];
				printf("put=%d(%d)\n",i,D[i]);
				put(i);
				}
			}
		}
	for (i=0;i<N;i++) printf("%d ",D[i]);
	printf("\nT=%d T2=%d\n",cnt,cnt2);
	}