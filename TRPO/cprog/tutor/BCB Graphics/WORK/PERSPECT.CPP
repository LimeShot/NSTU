#include<conio.h>
#include<graphics.h>
#include <dos.h>
#include <math.h>
#include <stdio.h>
// Перспектива
// x,y - координаты
// dx,dy - скорости по осям координат
// ax,ay - ускорение по осям координат
//
double K=0.01;
int XB=600,YB=400;		// Координаты бесконечности
int x0,y0;				// Размеры изображения
int getX(double x,double y, double z){
	return x + (XB-x)*(1.-exp(-K*y));
}
int getY(double x,double y, double z){
	return y0-z - (YB-z)*(1.-exp(-K*y));
}


void main (){
int gdriver = DETECT, gmode;
initgraph(&gdriver, &gmode, "d:\\bc31\\bgi");
setfillstyle(1,BLUE);
x0=getmaxx();
y0=getmaxy();
bar(1,1,x0-1,y0-1);
double sz=50;
for (double zz=10; zz<400; zz+=70)
for (double yy=0; yy<1000; yy+=20){
	int x11=getX(10,yy,zz);
	int x12=getX(10+sz,yy,zz);
	int x13=getX(10+sz,yy,zz+sz);
	int x14=getX(10,yy,zz+sz);
	int y11=getY(10,yy,zz);
	int y12=getY(10+sz,yy,zz);
	int y13=getY(10+sz,yy,zz+sz);
	int y14=getY(10,yy,zz+sz);
	setcolor(WHITE);
	line(x11,y11,x12,y12);
	line(x12,y12,x13,y13);
	line(x13,y13,x14,y14);
	line(x14,y14,x11,y11);

	}
getch();
closegraph();
}




