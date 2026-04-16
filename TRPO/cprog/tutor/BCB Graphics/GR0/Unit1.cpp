//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#include <time.h>
#include <stdlib.h>
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//-------------Глобальнеы переменные - НЕ ПОЛОЖЕНО, но пусть пока так....
int ON=0,XM,YM;
TCanvas *img;
double x,y,dx,dy,ax=0,ay=0.5;
int  r,xold,yold;
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
        x=random(XM);
        y=random(YM);
        dx=random(10)-5;
        dy=random(10)-5;
        r=20;
        ON=1;
        }
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        int cl,dd,xx,yy;
        if (ON==0) return;                              // Не нажата кнопка - выйти
	x+=dx;
	y+=dy;
	dx+=ax;
	dy+=ay;
	if (dx<0 && x<=r) dx=-dx;
	if (dx>0 && x>XM-r) dx=-dx;
	if (dy<0 && y<=r) dy=-dy;
	if (dy>0 && y>YM-r) dy=-dy*0.9;
	if ((int)x!=xold || (int)y!=yold){
                img->Brush->Color=0xFFFFFF;
                img->Pen->Color=0xFFFFFF;
                img->Ellipse(xold-r,yold-r,xold+r,yold+r);
                xold=x;
		yold=y;
                img->Brush->Color=0xFF0000;
                img->Pen->Color=0xFF0000;
                img->Ellipse(xold-r,yold-r,xold+r,yold+r);	       
        }
}
//---------------------------------------------------------------------------

