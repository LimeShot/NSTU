#include <stdio.h>
//------------------------------------------------------91-08.cpp
//------Сложение целых произвольной разрядности
 typedef unsigned char uchar;
 void add(uchar out[], uchar in1[], uchar in2[], int n)
 {int i, carry;			// Разряд переноса переноса
 unsigned w;            // Рабочая переменная для сложения двух байтов
      for (i=0, carry=0; i<n; i++){
      out [i] = w = in1[i]+in2[i]+carry;
      carry = (w & 0x0100) >>8;
      }} 

void main(){
long a=125000, b=30000, c;
add((uchar*)&c, (uchar*)&a, (uchar*)&b,sizeof(long));
printf("c=%ld\n",c);}
