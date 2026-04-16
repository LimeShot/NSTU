#include <stdio.h>
#include <math.h>
#include <string.h>
#define PI 3.1415926
char	*names[] = { "sin","cos","tan",NULL};		// Массив имен (указатели на строки)
double	(*pf[])(double) = { sin, cos, tan};			// Массив функций (адреса функций)
//------------------------------------------------------93-01.cpp
//---- Вызов функции по имени из заданного списка
 double call_by_name(char *pn, double arg) {
 for ( int i=0; names[i]!=NULL; i++)
	   if (strcmp(names[i],pn) == 0) {	// Имя найдено -
      return ((*pf[i])(arg));           // вызов функции по i-му
      }                                 // указателю в массиве pf
 return 0.;}

 void main(){
 printf("cos(pi/4)=%lf\n",call_by_name("cos",3.1415926/4));}
