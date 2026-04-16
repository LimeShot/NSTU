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
int ON=0;
int XM,YM;
int cnt,R;
TCanvas *img;
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
        img->Pen->Color=0xC0A070;               // Цвет пера (линии)
        img->Pen->Width=2;                      // Ширина пера
        img->Ellipse(30,50,100,100);            // Эллипс (left,top,right,bottom)
                                                // с заливкой фоном
        img->Brush->Color=0xD0B080;             // Прямоугольник с заливкой
        img->Rectangle(100,20,130,70);          // Прямоугольник (left,top,right,bottom)
        img->MoveTo(10,10);                     // Устанавливает курсор
        img->LineTo(80,40);                     // Линия от курсора до точки
                                                // Точек на 1 БОЛЬШЕ (первая-последняя)
        TPoint a[]={TPoint(250,10),TPoint(260,20),TPoint(230,70),TPoint(250,10)};
        img->Polygon(a,3);
        img->Brush->Color=0xFFFFFF;
        img->TextHeight("20");
        img->Font->Color=0xFF0040;
        img->Font->Size=20;
        //Стиль шрифта
        TFontStyles tFontStyle;
        // Зачеркнутый, наклонный, жирный, подчеркнутый
        // tFontStyle << fsStrikeOut << fsItalic << fsBold << fsUnderline;
        tFontStyle << fsBold;
        img->Font->Style=tFontStyle;
        img->TextOutA(140,70,"Это строка");     // Вывод строки x,y,char[]
        img->Pen->Width=1;
        for (int i=0; i<256;i++){
                img->Pen->Color=i<<16;          // 256 полос голубого спектра
                img->MoveTo(20+i,120);          // Устанавливает курсор
                img->LineTo(20+i,140);          // Линия от курсора до точки
                }
        for (int x=0; x<256;x++)                // Формирование красно-зеленого спектра
        for (int y=0; y<256;y++)                // Двумерный массив пикселей
                img->Pixels[20+x][150+y]=x*256+y;
        ON=1;                                   // Таймер проверяет
        cnt=0;
        R=10;
        }
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
int cl,dd,xx,yy;
if (ON==0) return;                              // Не нажата кнопка - выйти
        cnt++;
        if (cnt%100==0) R++;                    // Через каждые 100 - +1 к радиусу
        xx=random(XM);                          // Случайные координаты
        yy=random(YM);
        if ((cl=img->Pixels[xx][yy])==0xFFFFFF) // Белая точка меняется на случайный цвет
                cl=random(0x1000000);
	dd=random(R);                           // Случайный радиус
        img->Brush->Color=cl;
        img->Pen->Color=cl;                     // Окружность цвета точки
        img->Ellipse(xx-dd,yy-dd,xx+dd,yy+dd);
}
//---------------------------------------------------------------------------

