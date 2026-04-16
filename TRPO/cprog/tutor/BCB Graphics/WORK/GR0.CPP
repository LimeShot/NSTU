#include<conio.h>
#include<graphics.h>
#include <dos.h>
// Равноускоренное движение (падение) шарика
// x,y - координаты
// dx,dy - скорости по осям координат
// ax,ay - ускорение по осям координат
// xold,yold - последние целочисленные координаты
void main (){
double x=100,y=5,dx=5,dy=0,ax=0,ay=0.1;
int xold=x,yold=y,r=25;
int gdriver = DETECT, gmode;
initgraph(&gdriver, &gmode, "e:\\bc31\\bgi");
setfillstyle(1,BLUE);
int x0=getmaxx();
int y0=getmaxy();
bar(1,1,x0-1,y0-1);
while (!kbhit()){	// пока нет нажатия клавиши
	delay(25);
	x+=dx;
	y+=dy;
	dx+=ax;
	dy+=ay;
	if (dx<0 && x<=r) dx=-dx;
	if (dx>0 && x>x0-r) dx=-dx;
	if (dy<0 && y<=r) dy=-dy;
	if (dy>0 && y>y0-r) dy=-dy*0.9;	// отскок с затуханием
	if ((int)x!=xold || (int)y!=yold){
		setcolor(BLUE);
		circle(xold,yold,r);
		xold=x;
		yold=y;
		setcolor(WHITE);
		circle(xold,yold,r);
		}
	}
getch();
getch();
closegraph();
}




