//------------------------------------------------------73-03.cpp
//------ Поиск выхода в лабиринте
#include <stdio.h>
#include <conio.h>
#define N 100
char LB[N][N];

 int step(int y,int x){
 if (LB[y][x]=='O') return 1;         // выход найден
 if (LB[y][x]!=' ') return 0;  		  // стенки и циклы
 LB[y][x]='.';                        // отметить точку
 if (step(y+1,x)) return 1;
 if (step(y,x+1)) return 1;
 if (step(y-1,x)) return 1;
 if (step(y,x-1)) return 1;
 LB[y][x]=' ';                        // снять отметку
 return 0;}

void main(){
int i,j,k;
FILE *fd=fopen("73-03.txt","r");
if (fd==NULL) return;
for (k=0;k<N && fgets(LB[k],N,fd)!=NULL;k++);
for (i=0; i<k; i++) printf("%s",LB[i]);
for (i=0; i<k; i++)
for (j=0; j<N; j++) if (LB[i][j]=='I') goto mmm;
mmm: if (i==N) return;
LB[i][j]=' ';
if (step(i,j))
	for (i=0; i<k; i++) printf("%s",LB[i]);
}
