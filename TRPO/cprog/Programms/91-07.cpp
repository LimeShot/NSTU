#include <stdio.h>
//------------------------------------------------------91-07.cpp
//-------- Извлечение и запись разряда (бита)
 long getbit(char c[], int &n) { //c[] - массив байтов, n - номер разряда
 int nb = n/8;                   // номер байта
 int ni = n%8;                   // номер разряда в байте
 n++;
 return (c[nb]>>ni) & 1; }       //сдвинуть к младшему и выделить
 void putbit(char c[], int &n, int v ){
 int nb = n/8;
 int ni = n%8;
 n++;
 c[nb] = c[nb] & ~(1<<ni) | ( (v&1) << ni);}
//------- Извлечение слова заданной размерности
unsigned long getword(char c[], int &n, int sz) {
unsigned long v = 0;			// int sz - количество разрядов
for(int i = 0; i<sz; i++) v |= getbit(c, n)<<i;
return v; }
void putword(char c[], int &n, int sz, long v){
while(sz--!=0)					
	  { putbit(c, n, v&1); v>>=1;}}
//---- Упаковка и распаковка переменных различной размерности
 void unpack(char c[]){
 int n=0; int vv;
      while(1){
      int mode=getword(c,n,2);			// Извлечение 2-разрядного кода
	   switch(mode){					// переключение по типу переменной
      case 0: return;
      case 1: vv=getword(c,n,8); break; // 01 извлечь 8-разрядное (байт)
      case 2: vv=getword(c,n,16);break;	// 10 извлечь 16-разрядное
      case 3: vv=getword(c,n,32);break;	// 11 извлечь 32-разрядное
	   } printf("%d\n",vv);
      }}
 void pack(char c[]){
 int n=0; int vv;
      do { scanf("%d",&vv);
      if(vv==0) putword(c,n,2,0);		// запись 2-разрядного кода 00
      else
      if (vv < 256) {
	   putword(c,n,2,1);				// запись 2-разрядного кода 01
	   putword(c,n,8,vv);}				// запись 8-разрядного кода числа
      else
      if (vv < 32768) {
	   putword(c,n,2,2);				// запись 2-разрядного кода 10
	   putword(c,n,16,vv);}				// запись 16-разрядного кода числа
	   else {
	   putword(c,n,2,3);				// запись 2-разрядного кода 11
	   putword(c,n,32,vv);}				// запись 32-разрядного кода числа
      } while (vv!=0); }

void main(){ char cc[100]; pack(cc); unpack(cc); }
