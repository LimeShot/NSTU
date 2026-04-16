/* (c) Written By Cazymyr Malevich */
/* Conceptual Art & Programming */
#include<conio.h>
#include<graphics.h>

void main (){
int gdriver = DETECT, gmode;
initgraph(&gdriver, &gmode, "e:\\bc31\\bgi");
setfillstyle(1,WHITE);
bar(1,1,getmaxx()-1,getmaxy()-1);
setfillstyle(1,BLACK);
int size=getmaxy()*0.8;
int x0=(getmaxx()-size)/2;
int y0=(getmaxy()-size)/2;
bar(x0,y0,x0+size,y0+size);
setcolor(8);
outtextxy(250,435,"(c) Kazymyr Malevych");
getch();
closegraph();
}




