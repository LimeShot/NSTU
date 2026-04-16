#include <stdio.h>
#include <stdlib.h>
// Задача коммивояжера - СУБОПТИМАЛЬНЫЙ ЖАДНЫЙ АЛГОРИТМ
// Задача коммивояжера - ПОЛНЫЙ КОМБИНАТОРЫЙ ПЕРЕБОР

int N,**M,*D,*P,*Q;
int Lmin=-1,*Dmin;
int cnt1=0, cnt2=0;

#include "randomatrix.cpp"


void step(int i,int L, int m, int mode){
	if (i==0 && m==N){
		if (Lmin==-1 || L<Lmin){
			Lmin=L;
			for (int i=0;i<N;i++) Dmin[i]=D[i];
			}
		return;
		}
	if (D[i]!=-1) return;
	if (mode==1 && Lmin!=-1 && L>=Lmin) return;	// Хуже найденного
	D[i]=m;
	for (int j=0;j<N;j++,cnt2++){
		if (M[i][j]==0) continue;
		step(j,L+M[i][j],m+1,mode);
		}
	D[i]=-1;
	}

void main(){
	int i,k,j;
	randomatrix(10,8,12);
	//load("m2.txt");
	D=new int[N];
	for (i=0;i<N;i++) D[i]=-1;
	//-------------------------------------------------
	int m=0,L=0;
	D[0]=m;
	i=0;
	printf("\n0");
	while(1){
		for (k=-1,j=0;j<N;j++,cnt1++){
			if (M[i][j]==0) continue;	
			if (D[j]!=-1) continue;
			if (k==-1 || M[i][j]< M[i][k])
				k=j;
			}
		if (k==-1) break;
		L+=M[i][k];
		D[k]=++m;
		i=k;
		printf("->%d",i);
		}
	if (m!=N-1) printf("\n\n%d<%d no solution\n",m+1,N);
	else {
		if (M[0][i]==0)	printf("\nno cyclic path\n");
		else L+=M[0][i];
		}
	printf("\nL=%d cnt=%d\n\n",L,cnt1);
	for (i=0;i<N;i++) printf("%d ",D[i]);
	//--------------------------------------------------
	Dmin=new int[N];
	Lmin=-1;cnt2=0;
	for (i=0;i<N;i++) Dmin[i]=D[i]=-1;
	step(0,0,0,0);
	printf("\n\nL=%d cnt=%d\n0",Lmin,cnt2);
	for (i=1;i<N;i++) printf("->%d",Dmin[i]);
	//--------------------------------------------------
	Lmin=-1;cnt2=0;
	for (i=0;i<N;i++) Dmin[i]=D[i]=-1;
	step(0,0,0,1);
	printf("\n\nL=%d cnt=%d\n0",Lmin,cnt2);
	for (i=1;i<N;i++) printf("->%d",Dmin[i]);
	puts("");
	}