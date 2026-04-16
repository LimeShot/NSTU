#include <conio.h>
#include <stdio.h>
#include <dos.h>
//     -2
// -1 ..... 1  координаты меняются (по ссылке)
//      2
void move(int &x, int &y, int r, int v){
gotoxy(x,y);
cprintf("  ");
switch(r){
case -2: y--; break;
case -1: x--; break;
case 2:  y++; break;
case 1:  x++; break;
	}
gotoxy(x,y);
cprintf("%2d",v);
delay(100);
}

void drive(int x0, int y0, int x1, int y1, int vv){
int y2, dy, dx;
if (y1>y0) dy=1; else dy=-1;
if (x1>x0) dx=1; else dx=-1;
y2=y0+(y1-y0)/2;
//1 y0 y2
while (y0!=y2) move(x0,y0,dy*2,vv);
//2 x0 x1
while(x0!=x1) move(x0,y0,dx,vv);
//3 y2 y1
while (y0!=y1) move(x0,y0,dy*2,vv);
}

// выбор с переносом и сдвигом хвоста
void sort_show(int A[],int B[],int n)
{ clrscr();
#define X0 10
#define YA 5
#define YB 15
for (int i=0; i<n; i++) { gotoxy(X0+3*i,YA); cprintf("%2d",A[i]); }
for (i=0; i<n; i++){
	for (int j=0,k=0; j<n-i; j++)
		if (A[j]<A[k]) k=j;
	drive(X0+k*3,YA,X0+i*3,YB,A[k]);
	B[i]=A[k];
	for (j=k; j<n-i-1; j++) {
		drive(X0+(j+1)*3,YA,X0+j*3,YA,A[j+1]);
		A[j]=A[j+1];
		}
	}
}

void main(){
_setcursortype(_NOCURSOR);  /* сделать курсор невидимым */
textbackground(BLUE);
textcolor(WHITE);
clrscr();
int A[]={4,8,3,4,7,2,3,8,4,6,5,8,3,4},B[100];
int n=sizeof(A)/sizeof(int);
sort_show(A,B,n);
}