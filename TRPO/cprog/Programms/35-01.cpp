 #include <stdio.h>
//------------------------------------------------------35-01.cpp
//---------" √р€зна€" программа просмотр повтор€ющихс€ цепочек
 void proc(char c[]){
 for (int i=0; c[i]!=0; i++)         // 1 шаг - 1 символ или 1 цепочка
	  {
	  if (c[i]!=' ' && c[i]==c[i+1])
		   {                         // заглушка
		   putchar('*' );
		   while (c[i]==c[i+1]) i++;
		   }
	  else putchar(c[i]);
	  }}

 void main(){ proc("gfbvege aaaaaaaaa ffffffffff"); }
