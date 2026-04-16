//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <time.h>
#include <stdlib.h>
#include <math.h>
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//-------------Глобальнеы переменные - НЕ ПОЛОЖЕНО, но пусть пока так....
int ON=0,XM,YM,Y0,YG;
TCanvas *img;
double x1,y1,x0,y0,vx,vy,dx,dy,ax,ay,r;
double K;
double POW;
//---------------------------------------------------------------------------
 void IntToString(char c[], int n)
 { int nn,k;
 for (nn=n, k=0; nn!=0; k++, nn/=10); // Подсчет количества цифр числа
 c[k] = '\0';                         // Конец строки
 for (k--; k >=0; k--, n /= 10)       // Получение цифр числа
 c[k] = n % 10 + '0';                 // в обратном порядке
 }
//-----------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
//--------------------- Инициализирующий код---------------------------
        if (ON==1) { ON=0; return; }            // Работает - остановить
        char cc[20];
        img=pbx->Canvas;                        // TPaintBox *pbx
        XM=pbx->Width;                          // TCanvas *img
        IntToString(cc,XM);                     // Преобразование числа во внешнюю форму
        XX->Text=cc;
        YM=pbx->Height;
        IntToString(cc,YM);
        YY->Text=cc;
        img->Brush->Color=0xFFFFFF;             // Цвет 0xBBGGRR
        img->Rectangle(0,0,XM-1,YM-1);          // Прямоугольник
//---------------------------------------------------------------------
   x0=XM/2;
   y0=YM/2;
   x1=x0-100;
   y1=y0-50;
   vx=-0.2;
   vy=1;
   dx=0;
   dy=0;
   K=200;
   POW=1.75;
   img->Brush->Color=0xFFFF00;             // Цвет 0xBBGGRR
   img->Ellipse(x0-10,y0-10,x0+10,y0+10);
   ON=1;
   }
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        int cl,dd,xx,yy;
        if (ON==0) return;                              // Не нажата кнопка - выйти
        img->Pixels[x1][y1]=0xFF0000;
        int sx=(x1<x0 ? 1 : -1);
	int sy=(y1<y0 ? 1 : -1);
	r=sqrt(pow(x1-x0,2)+pow(y1-y0,2));
	double fi=asin(fabs(y1-y0)/r);
	double aa=K/(pow(r,POW));
	ax=sx*aa*cos(fi);
	ay=sy*aa*sin(fi);
	vx+=ax;
	vy+=ay;
	x1+=vx;
	y1+=vy;
        }
//---------------------------------------------------------------------------

