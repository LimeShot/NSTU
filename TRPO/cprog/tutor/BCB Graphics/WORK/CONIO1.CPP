#include <conio.h>
#include <math.h>
#include <time.h>
#define X0 5
#define Y0 10
#define Y1 20

void move(int &x, int &y,int r, int c){
gotoxy(x,y);
cprintf("  ");
if (abs(r)<2) x+=r; else y+=r/2;
gotoxy(x,y);
cprintf("%2d",c);
long t=clock();
while(clock()-t<5);
}

void drive(int x0, int y0, int x1, int y1, int c){
int dx=x1>x0?1:-1;
int dy=y1>y0?1:-1;
int y2=(y0+y1)/2;
while(y0!=y2) move(x0,y0,dy*2,c);
while(x0!=x1) move(x0,y0,dx,c);
while(y0!=y1) move(x0,y0,dy*2,c);
}

void change(int x0, int x1, int y0, int v0, int v1){
int dx=x1>x0?1:0;
int xx=x1, yy=y0;
move(x0,y0,0,v0);
move(xx,yy,0,v1);
move(x0,y0,2,v0);
move(xx,yy,-2,v1);
while(x0!=x1){
	move(x0,y0,dx,v0);
	move(xx,yy,-dx,v1);
	}
move(x0,y0,-2,v0);
move(xx,yy,2,v1);
}

//--------------------------------------------------------18
void F18(int c[], int n)
{ int i,j,k;
for (i=0,j=n-1; i < j; i++,j--)
     {
     change(X0+3*i,X0+3*j,Y0,c[i],c[j]);
     k = c[i]; c[i] = c[j]; c[j] = k;
     }
}

//------------------------------------------------- 2
 void F2(int in[],int out[],int n)
 { int i,j ,cnt;
      for (i=0; i< n; i++) {
      for ( cnt=0,j=0; j<n; j++) if (in[j]<in[i]) cnt++;
      else
           if (in[j]==in[i] && j>i) cnt++;
      drive(X0+3*i,Y0,X0+3*cnt,Y1,in[i]);
      out[cnt]=in[i];
      } }

void main(){
textcolor(YELLOW);
textbackground(LIGHTBLUE);
_setcursortype(_NOCURSOR);
clrscr();
//move(5,5,0,5);
//drive(5,5,36,12,5);
//change(5,55,10,33,77);
int b[10]={5,43,7,4,3,4,5,6,2,4},c[10];
for (int i=0; i<10; i++) move(X0+3*i,Y0,0,b[i]);
F18(b,10);
F2(b,c,10);
while(1);
}