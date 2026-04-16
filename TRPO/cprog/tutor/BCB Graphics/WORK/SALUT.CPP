#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include <math.h>
#include <graphics.h>

#define MLEFT 1
#define MRIGHT 2

//---------------------------------------------------------------------------

int  MouseOn()

{ _AX=0; geninterrupt(0x33);
	if (_AX!=0xffff) return 0;
	_AX=0x12; geninterrupt(0x10);
	return 1;
}

//---------------------------------------------------------------------------

void MouseShow(){_AX=1; geninterrupt(0x33);}

//---------------------------------------------------------------------------

void MouseHide(){_AX=2; geninterrupt(0x33);}

//---------------------------------------------------------------------------

void MousePos(int &x,int &y)
{ _AX=3; geninterrupt(0x33); x=_CX; y=_DX;}

//---------------------------------------------------------------------------

int  MouseBut()
{_AX=3; geninterrupt(0x33); return _BX;}

//---------------------------------------------------------------------------

void MouseOff(){_AX=0; geninterrupt(0x16);}

//---------------------------------------------------------------------------

int now;

//---------------------------------------------------------------------------

struct PUS
	{
   int x,y,r,color,lr,issalut,speed;         //Параметры шарика и его данные
   };

//---------------------------------------------------------------------------

PUS B,A[100];
int n=0;

//---------------------------------------------------------------------------

void set(PUS &B)
{
	//Инициализация шара со случайными данными

	B.y=getmaxy()-5;
   B.color=1+random(getmaxcolor()-1);
   B.r=0;
   B.x=5+random(getmaxx()-10);
   B.issalut = 1;
   B.speed = random(5)+10;
   B.lr = random(6);
   setcolor(B.color);
   circle(B.x,B.y,B.r);
}

//---------------------------------------------------------------------------

void deleteball(PUS &W)
	{
	setcolor(BLACK);                      //Задать цвет черным
	circle(W.x,W.y,W.r);						  //Нарисовать черный круг в x,y с радиусом r
   }

//---------------------------------------------------------------------------

int moveball(PUS &B)
{
setcolor(BLACK);
circle(B.x,B.y,B.r);
B.y-=B.speed;                             //Уменьшить ординату на 5
B.color++;                                //Сменить цвет
if (B.lr == 1) B.x++;
else if (B.lr == 2) {}					  		//В зависимости от параметра lr передвинуть шар
else if (B.lr == 3) B.x+=2;					//В зависимости от параметра lr передвинуть шар
else if (B.lr == 4) B.x-=2;					//В зависимости от параметра lr передвинуть шар
else B.x--;

if (B.y-B.r<=0) { return 1;}
setcolor(B.color);
circle(B.x,B.y,B.r);
return 0;
}

//---------------------------------------------------------------------------

void wzriw(PUS &E)
	{
	E.r = 10;
   deleteball(E);                        //Удалить шар E
   E.lr = 5;
   E.speed = 5;
   for (int j=0; j<5; j++)
      {
	   A[n].r=random(10)+2;
      A[n].x=E.x-100+random(200);        //Случайные координат шара
      A[n].y=E.y-100+random(200);
      A[n].lr = random(4);               //Случайное направление шара
      A[n].issalut = 0;
      A[n].speed = 5;
      setcolor(random(14)+1);            //Случайный цвет шара

   	circle(A[n].x,A[n].y,A[n].r);
      n++;
		}
   setcolor(LIGHTGREEN);
   outtextxy(getmaxx()/2,getmaxy()/2-40, "Salute demonstration");
   outtextxy(getmaxx()/2,getmaxy()/2, "by Tarkhov Dmitry");

   }

//---------------------------------------------------------------------------

int krit(PUS &C, PUS &D){
   return (C.r+D.r > sqrt(pow(fabs(C.x-D.x),2)+pow(fabs(C.y-D.y),2)));
	}

//---------------------------------------------------------------------------

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
   bar(0,0,maxx-1,maxy-1);		// Смена фона

   settextjustify(CENTER_TEXT, CENTER_TEXT);
   settextstyle(7, HORIZ_DIR, 2);
   outtextxy(getmaxx()/2,getmaxy()/2-40, "Salute demonstration");
   outtextxy(getmaxx()/2,getmaxy()/2, "by Tarkhov Dmitry"); //Отображение на экарен текста

	//Рабочее тело программы
   randomize();
   int i,l;
   int cnt=0;
   while(!kbhit())                         //Цикл совершается до нажатия клавиши
   {
   long t=clock();
   while(clock()-t<2);                    //Ожидание 20 мс
   cnt++;
   if (cnt==10) { cnt=0; set(A[n++]); }    //Добавление шарика
   for (l=0;l<n;l++)
	  if (A[l].y<100 && A[l].issalut == 1) //Если координата y шара <100 и шар является снарядом, то взорвать шарик
	  { deleteball (A[l]); wzriw(A[l]); break; } //Удаление шара и проектирование взрыва, а также выход из цикла
   for (l=0;l<n;l++)
	{
		if (moveball(A[l]))
		{
		  for (int k=l; k<n-1; k++) A[k]=A[k+1];
	   n--;
		l--;
		 }
	  }
   }

   getch();                                   //Программа ждет до нажатия клавиши
   closegraph();         							 //Закрытие графического модуля
}
//---------------------------------------------------------------------------
