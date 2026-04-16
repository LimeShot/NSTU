#include <conio.h>
#include <stdio.h>
#include <dos.h>
#define X0 10
#define YC1 5
#define YC2 15
#define YCS 10

void move(int x, int y, int r, char cc)
{
gotoxy(x,y);
putch(' ');
switch(r){
case 0: y--; break;
case 1: x++; break;
case 2: y++; break;
case 3: x--; break;
	}
gotoxy(x,y);
putch(cc);
delay(50);
}

// 1 - нашла, 0 - нет
int F(char c1[], char c2[])   // Добавлять в c2[]
{
int x,y;
int s,i,j,k,m=-1;
//1----------------------------------
clrscr();
gotoxy(X0,YC1); cputs(c1);
gotoxy(X0,YC2); cputs(c2);
for (k=0,i=0; c1[i]!=0; i++)
	{
	if (c1[i]=='}') k--;
	if (c1[i]=='{') {
		k++;
		if (k>m) {
            delay(500);
			if (m!=-1){ gotoxy(X0+j,YC1); putch(c1[j]); }
			m=k;
			j=i;
			textcolor(YELLOW);
			gotoxy(X0+j,YC1); putch(c1[j]);
			textcolor(WHITE);
			}
		}
	}
//2----------------------------------
for (int l=0; c2[l]!=0; l++);
if (m==-1)
	{
	for (s=0; c1[s]!=0; s++, l++)
		{
		for (y=YC1; y!=YCS; y++) move(s+X0,y,2,c1[s]);
		if (s>l)
			for (x=s; x!=l; x--) move(x+X0,YCS,3,c1[s]);
		else
			for (x=s; x!=l; x++) move(x+X0,YCS,1,c1[s]);
		for (y=YCS; y!=YC2; y++) move(l+X0,y,2,c1[s]);
		c2[l]=c1[s];
		}
	c2[l]=0;
	c1[0]=0;
	return 0;
	}
for (s=j+1; c1[s]!='}' && c1[s]!=0; s++, l++)
	{
	for (y=YC1; y!=YCS; y++) move(s+X0,y,2,c1[s]);
	if (s>l)
		for (x=s; x!=l; x--) move(x+X0,YCS,3,c1[s]);
	else
		for (x=s; x!=l; x++) move(x+X0,YCS,1,c1[s]);
	for (y=YCS; y!=YC2; y++) move(l+X0,y,2,c1[s]);
	c2[l]=c1[s];
	}
c2[l++]=',';
c2[l]=0;
//3---------------------------------
if (c1[s]=='}') s++;
for (;c1[s]!=0; s++, j++)
	{
	for (x=s; x!=j; x--) move(x+X0,YC1,3,c1[s]);
	c1[j]=c1[s];
	}
c1[j]=0;
return 1;
}

void main()
{
char cc1[]="111{222{333}222{333{444}333}}111111";
char cc2[80]="";
_setcursortype(_NOCURSOR);  /* сделать курсор невидимым */
textbackground(BLUE);
textcolor(WHITE);
clrscr();
while( F(cc1,cc2) );
gotoxy(X0,YC1); cputs(cc1);
gotoxy(X0,YC2); cputs(cc2);
}
