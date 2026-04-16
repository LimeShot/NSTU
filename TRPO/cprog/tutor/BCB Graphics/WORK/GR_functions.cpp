#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<dos.h>
#include<time.h>
#include<graphics.h>

void main()
{
	// int gdriver=DETECT, gmode=VGAHI, errorcode;
	// initgraph(&gdriver, &gmode, "e:\\bc31\\bgi");
	int GraphDriver=installuserdriver("svga256",NULL); //Драйвер 256 цветов
	int GraphMode=1,ErrorCode;
	initgraph( &GraphDriver, &GraphMode, "e:\\bc31\\bgi" );
	int errorcode = graphresult();
	if (errorcode != grOk)
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		return;
	}
   int maxx=getmaxx();        	// Размерность X
   int maxy=getmaxy();          // Размерность Y
   int maxcolor=getmaxcolor();  // Кол-во цветов
   setfillstyle(1,BLUE);   		// Стиль и цвет заливки
   setcolor(YELLOW);			// Цвет линий и прочего
   bar(0,0,maxx-1,maxy-1);		// Заливка фона
   settextstyle(2,0,5);			// Вид шрифта,,размер
   char cc[80];                 // Форматный вывод в строку
   sprintf(cc,"%dx%d %d colors",maxx,maxy,maxcolor);
   outtextxy(maxx*0.4,maxy/2,cc);// Вывод строки в графике
   for (int j=0;j<10;j++)
   for (int i=0;i<maxcolor;i++)
		putpixel(100+i,100+j,i); // Вывод точки - X,Y,цвет
   circle(200,200,10);  		 // Окружность - X,Y,R
   line (10,20,300,350);         // Линия - X1,Y1,X2,Y2
   setfillstyle(2,RED);   		 // Стиль и цвет заливки
   bar(200,300,250,360);		 // Заливка прямоугольника
   rectangle(210,310,260,370);	 // Прямоугольний цвета линии
   setfillstyle(1,130);   		 // Стиль и цвет заливки сектора
   setcolor(150);                // Цвет окантовки сектора
   pieslice(350,300,45,135,50);	 // Сектор - X,Y,нач и кон угол, R
   pieslice(500,300,0,360,50);	 // Сектор - X,Y,нач и кон угол, R
   setcolor(YELLOW);
   arc(400,300,45,135,70);		 // Дуга - X,Y центра, нач и кон угол, R
   int a[6]={400,20,450,70,430,90};
   fillpoly(3,a);				 // Массив точек (X,Y) и заливка полигона
   fillellipse(450,150,100,30);	 // Заливка эллипса X,Y,Dx,Dy
   delay(5000);
   randomize();
   while(!kbhit()){
		int x=random(maxx);
		int y=random(maxy);
		int cl;
		if ((cl=getpixel(x,y))==BLUE) putpixel(x,y,WHITE);
		else
			{
			int dx=(cl==WHITE ? 1 : 2);
			for (int i=-dx;i<=dx;i++)
			for (int j=-dx;j<=dx;j++)
				putpixel(x+i,y+j,cl);
			}
		}
   getch();
   closegraph();
}
