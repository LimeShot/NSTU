#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <math.h>
#include <graphics.h>
// Њлим Ї®¤ DOS
#define MLEFT 1
#define MRIGHT 2
int  MouseOn()
{ _AX=0; geninterrupt(0x33);
	if (_AX!=0xffff) return 0;
	_AX=0x12; geninterrupt(0x10);
	return 1; }

void MouseShow(){_AX=1; geninterrupt(0x33);}
void MouseHide(){_AX=2; geninterrupt(0x33);}
void MousePos(int &x,int &y){ _AX=3; geninterrupt(0x33); x=_CX; y=_DX;}
int  MouseBut() {_AX=3; geninterrupt(0x33); return _BX;}
void MouseOff(){_AX=0; geninterrupt(0x16);}


void main()
{
	int gdriver=DETECT, gmode=VGAHI, errorcode;
	initgraph(&gdriver, &gmode, "e:\\bc31\\bgi");
	errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));         //Ошибка инициализации графического модуля
		printf("Press any key to halt...");
		getch();
		return;
	}
   int maxx=getmaxx();
   int maxy=getmaxy();
   int maxcolor=getmaxcolor();
   setfillstyle(1,BLACK);
   setcolor(LIGHTGREEN);
   bar(0,0,maxx-1,maxy-1);		// ”®­
   MouseOn();
   int xm,ym,x0,y0;
   MousePos(x0,y0);
   xm=x0; ym=y0;
   putpixel(x0,y0,YELLOW);
   while(!kbhit())
		{
		MousePos(xm,ym);
		if (xm!=x0 || ym!=y0){
			putpixel(x0,y0,BLACK);
			x0=xm;y0=ym;
			putpixel(x0,y0,YELLOW);
			}
		int but=MouseBut();
		if (but==MLEFT) circle(x0,y0,20);
		if (but==MRIGHT) circle(x0,y0,30);
		delay(10);
		}
   getch();
   closegraph();
}
//---------------------------------------------------------------------------
