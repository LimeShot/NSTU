#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<math.h>
#include <stdlib.h>
#include<graphics.h>
#define MLEFT 1
#define MRIGHT 2
#define N 50

// Построение графика функции
// Параметр - указатель на функцию (имя вычисляемой функции)
void graphic(double a, double b, double(*pf)(double),int color)
{
double dx=(b-a)/(0.8*getmaxx());
int n;
double y,x,min=pf(a),max=pf(a);

for (x=a; x<=b; x+=dx){
   y=pf(x);
   if (y<min) min=y;
   if (y>max) max=y;
	}
// Определение диапазонов и масштабов
double dy=(max-min)/(0.8*getmaxy());
int y0=0.9*getmaxy();
for (n=0.1*getmaxx(),x=a; x<=b; x+=dx,n++)
	{
   y=pf(x);
   int cy=y0-(int)((y-min)/dy);
   putpixel(n,cy,color);
	}
}

double myfun(double x){ return sin(x)*exp(-0.1*x); }

void main()
	{
   randomize();
	int gdriver=DETECT, gmode=VGAHI, errorcode;
	initgraph(&gdriver, &gmode, "e:\\bc31\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		return;
	}
   setfillstyle(1,BLACK);
	setcolor(YELLOW);
   bar(0,0,getmaxx()-1,getmaxy()-1);		// set background
   double db=0.1,b=10;
	while(!kbhit()){
	graphic(0,b,myfun,YELLOW);
	  long t=clock();
      while(clock()-t<10);
	   graphic(0,b,myfun,BLACK);
      b+=db;
      if (b<10 || b>20) db=-db;
      }
   getch();
	closegraph();
   }
