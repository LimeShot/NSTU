#include <stdio.h>
 typedef unsigned char uchar;
//------------------------------------------------------91-09.cpp
//------ ѕолучение отрицательного числа в дополнительном коде
 void neg(uchar in[], int n)
 {int i, carry;         // –азр€д переноса
 unsigned w;            // –абоча€ переменна€ дл€ сложени€ двух байтов
 for (i=0; i<n; i++) in[i]=~in[i];
      for (i=0, carry=1; i<n; i++){
      in [i] = w = in[i]+carry;
      carry = (w & 0x0100) >>8;
      }}

void main(){
long c=125000;
neg((uchar*)&c,sizeof(long));
printf("c=%ld\n",c);}
