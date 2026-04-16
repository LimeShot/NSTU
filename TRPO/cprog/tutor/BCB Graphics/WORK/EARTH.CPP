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

int  MouseOn()
{ _AX=0; geninterrupt(0x33);
	if (_AX!=0xffff) return 0;
	_AX=0x12; geninterrupt(0x10);
	return 1;
}

void MouseShow(){_AX=1; geninterrupt(0x33);}

void MouseHide(){_AX=2; geninterrupt(0x33);}

void MousePos(int &x,int &y)
{ _AX=3; geninterrupt(0x33); x=_CX; y=_DX;}

int  MouseBut()
{_AX=3; geninterrupt(0x33); return _BX;}

void MouseOff(){_AX=0; geninterrupt(0x16);}

struct pusyr{
   double x,y,dy,r,dr;
   int color;
   double step;
	};

pusyr A={100,200,-5,20,0.5,YELLOW,0};
pusyr B[N];


void hide(pusyr &Z){
	setcolor(BLACK);
   circle(Z.x,Z.y,Z.r);
	}


#define	dd 4
void move(pusyr &Z){
	if (Z.y==-1) return;
   Z.step+=Z.dy;
   if (abs(Z.step)>dd)
		{
      hide(Z);
	   Z.r+=Z.dr;
      Z.y+=Z.step;
      Z.step=0;
      setcolor(Z.color);
	  circle(Z.x,Z.y,Z.r);
   	}
	}

void set(pusyr &Z){
	Z.step=0;
   Z.color=random(getmaxcolor());
   Z.r=5+random(10);
   Z.dy=-Z.r/2.0+0.1;
   Z.dr=random(10)/5.0;
   Z.y=getmaxy()-Z.r;
   Z.x=Z.r+random(getmaxx()-2*Z.r);
	}

int create(){
for (int i=0; i<N; i++)
	if (B[i].y==-1)
   	{
      set(B[i]);
      return i;
      }
return -1;
}


int point=0;

void score(){
char c[80];
sprintf(c,"points=%3d",point);
setcolor(YELLOW);
bar(10,getmaxy()-20,100,getmaxy()-1);
outtextxy(10,getmaxy()-20,c);
}




void oval(int x, int y, int r, int fc, int bc){
setfillstyle(SOLID_FILL,fc);
setcolor(fc);
pieslice(x,y,0,360,r);
//setcolor(bc);
//circle(x,y,r);
}


void main()
{
   MouseOn();
   MouseHide();
   randomize();
	int gdriver=DETECT, gmode=VGAHI, errorcode;
	gdriver=installuserdriver("svga256",NULL);
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
   settextstyle(2,0,5);			// font,vert,size
   setcolor(YELLOW);
   bar(0,0,getmaxx()-1,getmaxy()-1);		// set background
   int x0=getmaxx()/2;
   int y0=100;
   int x1=x0-60;
   int y1=y0+10;
   double vx=-0.2;
   double vy=0.2;
   double dx=0,dy=0;
   double ax,ay;
   double r;			// расстояние до спутника
   double K=5;			// коэффициент силы притяжения
   double POW=2;
   long t=clock();
   oval(x0,y0,10,MAGENTA,BLACK);
   while (!kbhit()){
//		setcolor(YELLOW);
//		circle(x1,y1,5);
		putpixel(x1,y1,YELLOW);
		delay(1);
//		setcolor(BLACK);
//		circle(x1,y1,5);
		int sx=(x1<x0 ? 1 : -1);
		int sy=(y1<y0 ? 1 : -1);
		r=sqrt(pow(x1-x0,2)+pow(y1-y0,2));
		double fi=asin(fabs(y1-y0)/r);
		double aa=K/(pow(r,POW));
		ax=sx*aa*cos(fi);
		ay=sy*aa*sin(fi);
		vx+=ax;
		vy+=ay;
		dx+=vx;
		dy+=vy;
		if ((int)dy!=0 || (int)dx!=0){
			x1+=(int)dx;
			y1+=(int)dy;
			dx-=(int)dx;
			dy-=(int)dy;
			}
//		printf("x=%d y=%d r=%5.3lf vx=%5.3lf vy=%5.3lf fi=%5.3lf\n",x1,y1,r,vx,vy,fi);

	  }
closegraph();
}
