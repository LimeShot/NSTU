#include<stdio.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<math.h>
#include <stdlib.h>
#include<graphics.h>
// Драйвер 256 цветов
// Моделирование движения в гравитационном поле
void main()
{
   randomize();
   int gdriver=DETECT, gmode=VGAHI, errorcode;
   gdriver=installuserdriver("svga256",NULL);	// драйвер 256 цветов
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
   bar(0,0,getmaxx()-1,getmaxy()-1); // Заливка фона
   int maxcolor=getmaxcolor();
   printf("max color=%d\n",maxcolor);
   int x0=getmaxx()/2;
   int y0=getmaxy()/2;
   double x1=x0-100;
   double y1=y0-10;
   double vx=-0.2;
   double vy=0.1;
   double dx=0,dy=0;
   double ax,ay;
   double r;			// расстояние до спутника
   double K=5;			// коэффициент силы притяжения
   double POW=1.75;     // Показатель степени закона всемирного тяготения
						// 2 - обычный, что будет при 1.5 1.75
   long t=clock();
   circle(x0,y0,10);
   while (!kbhit()){
		putpixel((int)x1,(int)y1,YELLOW);
		delay(1);
		int sx=(x1<x0 ? 1 : -1);		// Квадрант угла вектора силы
		int sy=(y1<y0 ? 1 : -1);        // Расстояние
		r=sqrt(pow(x1-x0,2)+pow(y1-y0,2));
		double fi=asin(fabs(y1-y0)/r);  // Угол вектора силы
		double aa=K/(pow(r,POW));       // Модуль ускорения силы притяжения
		ax=sx*aa*cos(fi);				// Составляющие по осям
		ay=sy*aa*sin(fi);
		vx+=ax;
		vy+=ay;
		x1+=vx;
		y1+=vy;
	  }
closegraph();
}
