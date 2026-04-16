#include<conio.h>
#include<graphics.h>
#include <dos.h>
// Колебание груза на пружине
// Координаты скорости и ускорения - см. GR0.cpp
// YY - координата середины пружины
//
void main (){
double x=40,y=40,dx=3,dy=0,ax=0,ay=0;
int xold=x,yold=y,r=25;
int gdriver = DETECT, gmode;
initgraph(&gdriver, &gmode, "e:\\bc31\\bgi");
setfillstyle(1,BLUE);
int x0=getmaxx();
int y0=getmaxy(),YY=y0/2;
bar(1,1,x0-1,y0-1);
double K1=0.01,K2=0.03;
while (!kbhit()){
	delay(25);
	ay=-K1*(y-YY);
	// ay=-K1*(y-YY)-K2*dy*dy;
	// Силы упругости пружины и сопротивление - ускорение
	dx+=ax;
	dy+=ay;
	x+=dx;
	y+=dy;
	if (dx<0 && x<=r) dx=-dx;
	if (dx>0 && x>x0-r) dx=-dx;
	if (dy<0 && y<=r) dy=-dy;
	if (dy>0 && y>y0-r) dy=-dy;
	if ((int)x!=xold || (int)y!=yold){
		setcolor(BLUE);
		circle(xold,yold,r);
		line(xold,yold,x0/2,YY);
		xold=x;
		yold=y;
		setcolor(WHITE);
		circle(xold,yold,r);
		line(xold,yold,x0/2,YY);
		}
	}
getch();
getch();
closegraph();
}




