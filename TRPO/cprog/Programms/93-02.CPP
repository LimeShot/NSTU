#include <stdio.h>
#include <math.h>
#define PI 3.1415926
//------------------------------------------------------93-02.cpp
//------Численное интегрирование произвольной функции
// a,b - границы интегрирования, n - число точек
// pf - подынтегральная функция
 double INTEG(double a, double b, int n, double(*pf)(double))
 { double s,h,x;
 for (s=0., x=a, h = (b-a)/n; x <=b; x+=h) s += (*pf)(x) * h;
 return s; }
 extern double sin(double);
 void main() { printf("sin(0..pi/2)=%lf\n",INTEG(0.,PI/2,1000,sin)); }
