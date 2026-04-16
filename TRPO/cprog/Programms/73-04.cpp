//------------------------------------------------------73-04.cpp
//------ Комната с зеркалами ("луч света в темном царстве")
#include <stdio.h>
#include <conio.h>
#define N 100
char LB[N][N];
// Рекурсиваная функция - текущие координаты (x,y) и приращения (dx,dy)
int step(int y,int x, int dy, int dx){
int c;
switch(LB[y][x]){						// поиск первого подходящего варианта
case 'O':	throw 1;		            // найден выход - прервать обход (исключение)
case ' ':	LB[y][x]='.';				// свободное пространство - двигаться в прежнем
			step(y+dy,x+dx,dy,dx);		// направлении с отметкой пройденного пути
			LB[y][x]=' ';				// если вернулись - очистить отмеченный путь
			break;
case '.':	LB[y][x]='+';				// пересечение с лучом (в перепендикулярном
			step(y+dy,x+dx,dy,dx);		// направлении - аналогично предыдущему
			LB[y][x]='.';
			break;
case '*':	LB[y][x]='\\';				// неориентированное зеркало - 
			c=dx; dx=dy; dy=c;			// два варианта ориентации с
			step(y+dy,x+dx,dy,dx);		// соответствующей сменой направления
			dx=-dx; dy=-dy;				// движения луча.
			LB[y][x]='/';
			step(y+dy,x+dx,dy,dx);		// если вернулись - восстановить 
			LB[y][x]='*';				// "неориентированное зеркало"
			break;
case '\\':	c=dx; dx=dy; dy=c;			// отражение от ориентированного зеркала
			step(y+dy,x+dx,dy,dx);		// (с обратной стороны)
			break;						// - один вариант распространения луча
case '/':	c=dx; dx=dy; dy=c;
			dx=-dx; dy=-dy;
			step(y+dy,x+dx,dy,dx);
			break;
	} return 0; }

void main(){
int i,j,k;
FILE *fd=fopen("73-04.txt","r");
if (fd==NULL) return;
for (k=0;k<N && fgets(LB[k],N,fd)!=NULL;k++);
for (i=0; i<k; i++) printf("%s",LB[i]);
for (j=0; j<k && LB[0][j]!='I'; j++);
if (j==N) return;
LB[0][j]=' ';
try	{
	step(0,j,1,0);
	}
catch(int n){
	for (i=0; i<k; i++) printf("%s",LB[i]);
	}
}
