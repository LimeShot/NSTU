//------------------------------------------77-03.cpp
// Преобразование строки - обратное накопление результата
// в структурированной переменной (объекте)
#include <stdio.h>
#include <string.h>
#include <math.h>
struct REZ{			// Структурированный тип - результат
	int k;			// Количество операций
	char s[100];	// Последовательность операций
	};
REZ F(char *A, char *B,int n,int &m){
	REZ V1,V2,V3;
	m++;
	if (*A==0 && *B==0) { V1.k=0; V1.s[n]=0; return V1; }
	if (*A==0) 
		{ V1=F(A,B+1,n+1,m); V1.s[n]='+'; V1.k++; return V1; }
	if (*B==0)
		{ V1=F(A+1,B,n+1,m); V1.s[n]='-'; V1.k++; return V1; }
	if (*A==*B) 
		{ V1=F(A+1,B+1,n+1,m); V1.s[n]='x'; }
	else
		{ V1=F(A+1,B+1,n+1,m); V1.s[n]='c'; V1.k++; }
	V2=F(A+1,B,n+1,m); V2.s[n]='-'; V2.k++; 
	V3=F(A,B+1,n+1,m); V3.s[n]='+'; V3.k++; 
	if (V2.k<V1.k) V1=V2;
	if (V3.k<V1.k) V1=V3;
	return V1;
	}

void main(){
	char c1[]="ptslddf",c2[]="tsgldds"; int n=0;
	REZ VV=F(c1,c2,0,n);
	printf("T=%d(%d) k=%d =>%s\n",n,(int)pow(4.0,(double)strlen(c1)+1),VV.k,VV.s);
	}