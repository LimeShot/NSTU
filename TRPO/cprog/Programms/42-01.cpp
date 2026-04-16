//------------------------------------------------------42-01.cpp
//------—частливые билеты
 long happy (){
 int m, B[6]; long v ,vv, n;
      for (n=0,v=0; v <= 999999; v++){
      for (vv = v, m=0; m<6; m++, vv /=10)
           B[m] = vv % 10;
      if (B[0]+B[1]+B[2]==B[3]+B[4]+B[5]) n++;
      }
 return n;} 

 #include <stdio.h>
 void main(){
 printf("happy=%ld\n",happy());}
