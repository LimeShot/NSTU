//------------------------------------------77-05.cpp
// Преобразование строки - обратное накопление результата
// в структурированном типе (объекте). Динамическое программирование
#include <stdio.h>
#include <string.h>
#include <math.h>
struct REZ{			// Структурированный тип - результат
	int k;			// Количество операиций
	char s[100];	// Последовательность операций
	REZ(){ k=-1; }
	};
#define N 6			// Массив промежуточных результатов
REZ D[N][N];		// для остатков строк размерности i,j

REZ F(char *A, char *B,int n,int &m, int s1, int s2){
	REZ V1,V2,V3;
	// Есть уже сохраненное решение для строк размерности s1,s2
	if (s1<N && s2<N && D[s1][s2].k!=-1) return D[s1][s2];
	m++;
	if (*A==0 && *B==0) { V1.k=0; V1.s[n]=0; return V1; }
	if (*A==0) 
		{ V1=F(A,B+1,n+1,m,s1,s2-1); V1.s[n]='+'; V1.k++; return V1; }
	if (*B==0)
		{ V1=F(A+1,B,n+1,m,s1-1,s2); V1.s[n]='-'; V1.k++; return V1; }
	if (*A==*B) 
		{ V1=F(A+1,B+1,n+1,m,s1-1,s2-1); V1.s[n]='x'; }
	else
		{ V1=F(A+1,B+1,n+1,m,s1-1,s2-1); V1.s[n]='c'; V1.k++; }
	V2=F(A+1,B,n+1,m,s1-1,s2); V2.s[n]='-'; V2.k++; 
	V3=F(A,B+1,n+1,m,s1,s2-1); V3.s[n]='+'; V3.k++; 
	if (V2.k<V1.k) V1=V2;
	if (V3.k<V1.k) V1=V3;
	// Найдено решение для строк размерности s1,s2 - сохранить
	if (s1<N && s2<N) D[s1][s2]=V1;	
	return V1;}

void main(){
	char c1[]="ptslddf",c2[]="tsgldds"; int n=0;
	REZ VV=F(c1,c2,0,n,strlen(c1),strlen(c2));
	printf("T=%d k=%d =>%s\n",n,VV.k,VV.s);
	}