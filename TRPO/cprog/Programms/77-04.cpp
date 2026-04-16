//------------------------------------------77-04.cpp
// Преобразование строки - динамическое программирование
#include <stdio.h>
#include <string.h>
#define N 4
int D[N][N];
int k=0;

int F(char *A, char *B,int s1, int s2){
	int k1,k2,k3;
	// Есть уже сохраненное решение для строк размерности s1,s2
	if (s1<N && s2<N && D[s1][s2]!=-1) return D[s1][s2];
	k++;
	if (*A==0 && *B==0) return 0;
	if (*A==0) return strlen(B);
	if (*B==0) return strlen(A);
	if (*A==*B)
		k1=F(A+1,B+1,s1-1,s2-1);
	else
		k1=F(A+1,B+1,s1-1,s2-1)+1;
	k2=F(A+1,B,s1-1,s2)+1;
	k3=F(A,B+1,s1,s2-1)+1;
	if (k2<k1) k1=k2;
	if (k3<k1) k1=k3;
	// Найдено решение для строк размерности s1,s2 - сохранить
	if (s1<N && s2<N) D[s1][s2]=k1;
	return k1;
	}

void main(){
	char c1[]="ptslddf",c2[]="tsgldds";
	for (int i=0;i<N;i++)
	for (int j=0;j<N;j++) D[i][j]=-1;
	printf("k=%d\n",F(c1,c2,strlen(c1),strlen(c2)));
	printf("T=%d\n",k);	
}