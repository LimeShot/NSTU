#include <stdio.h>
 typedef unsigned char uchar;
//------------------------------------------------------39-10.cpp
//------Сдвиг целых произвольной разрядности
 void lshift(uchar in[], int n)
 { int carry;						// Разряд переноса
 int i,z;
 for (carry=0, i=0; i<n; i++){ 
      z=(in[i] & 0x80)>>7;          // Выделить старший разряд (перенос)
      in[i] <<= 1;                  // Сдвинуть влево и установить
      in[i] |=carry;                // старый перенос в младший разряд
      carry = z;                    // Запомнить новый перенос
      }}
 void rshift(uchar in[], int n)		// Сдвиг арифметический
 { int carry=((in[n-1]&0x80)!=0);    // Разряд переноса = копия знакового
 int i,z;
 for (i=n-1; i>=0; i--){ 
      z = in[i] & 1;                 // Выделить младший разряд (перенос)
      in[i] >>= 1;                   // Сдвинуть вправо и установить
      in[i] |= carry <<7;            // старый перенос в старший разряд
      carry = z;                     // Запомнить новый перенос
      }} 

void main(){
long c=125000, c2=-55;
lshift((uchar*)&c,sizeof(long));
lshift((uchar*)&c2,sizeof(long));
printf("c=%ld c2=%ld\n",c,c2);
rshift((uchar*)&c,sizeof(long));
rshift((uchar*)&c2,sizeof(long));
printf("c=%ld c2=%ld\n",c,c2);
}
