//------------------------------------------------------75-01.cpp
//------ Поиск выхода в лабиринте - явный стек
#include <stdio.h>

template <class T, int sz>
class stack{
	T area[sz];
	int sp;
public:
	int size(){ return sp+1; }
	stack(){ sp=-1; }
	T pop(){
		static T null;
		if (sp==-1) return null;
		return area[sp--];
		}
	void push(T v){ area[++sp]=v; }
	};

int LB[10][10]={
{1,1,1,1,1,1,1,1,1,1},
{1,1,0,1,0,1,1,0,1,1},
{1,1,0,0,0,0,1,0,0,1},
{1,1,0,1,1,0,1,0,1,1},
{1,0,0,1,1,0,1,0,0,0},
{1,1,0,1,1,0,1,0,1,1},
{1,0,0,1,1,0,1,0,1,1},
{1,1,0,0,1,0,0,0,0,1},
{1,1,1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1,1,1}};

struct XY{ 
	int x,y,last; 
	XY(int x0,int y0,int last0=0) { x=x0,y=y0,last=last0; }
	XY(){ x=y=last=0; }
	};

stack<XY,100> S;				// Явный стек
XY	A(5,5);

void main(){
S.push(A);					// Поместить в стек
int found=0;				// Признак завершения
while(S.size()!=0){			// Цикл извлечения шагов из стека
	XY D=S.pop();			// Извлечь из стека данные нового шага
	if (D.last==1){
		LB[D.x][D.y]=0;     // "последний" вариант - снять отметку
		continue;
		}
	if (D.x<0 || D.x>9 || D.y<0 || D.y>9) 
		{found=1; break; }	// Достигли края - выйти из цикла
	if (LB[D.x][D.y]!=0) 
		continue;  		    // стенки и повторы - завершить шаг
	LB[D.x][D.y]=2;         // отметить точку
	S.push(XY(D.x,D.y,1));	// Вариант для "завершения" шага рекурсии
	S.push(XY(D.x+1,D.y));	// варианты для соседних точек
	S.push(XY(D.x,D.y+1));
	S.push(XY(D.x-1,D.y));
	S.push(XY(D.x,D.y-1));
	}
if (found)
	for (int i=0; i<10; i++,puts(""))
	for (int j=0; j<10; j++) printf("%d",LB[i][j]);
}
