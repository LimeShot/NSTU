#include <stdio.h>
//------------------------------------------------------91-02.cpp
//----- Определение разрядности числа
 int wordlen(unsigned long vv){
 int i; for (i=0; vv!=0; i++, vv>>=1);
 return i;}

 void main(){
 printf("wordlen()=%d\n",wordlen(1025)); }
