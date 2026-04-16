//------------------------------------------------------42-05.cpp
//--------------------------------------------------------
 int test(int a){
	  int n,k,i;
 for (n=a; n!=0; n/=10){
	  k=n%10;
      if (k==0) break;                                    // Цифра - 0
	  if (k==1) continue;                                 // Цифра - 1
      for (i=2; i<k; i++)
           if ( k%i==0) break;                     // Цифра не простая
      if (k!=i) break;                             // Цифра не простая
      }
 if (n==0) return 1;                     // Дошли до конца без break -
 return 0; }                                     // все цифры простые.

 #include <stdio.h>
 void main(){
 printf("test(1357)=%d\n",test(1357));
 printf("test(1457)=%d\n",test(1457)); }
