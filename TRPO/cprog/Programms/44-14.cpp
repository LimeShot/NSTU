//------------------------------------------------------44-14.cpp
//---------------------------------------------------
 int F(char c[]){
 int i,ns;
 for (i=0,ns=0; c[i]!=0; i++)
	  if (c[i]!=' ' && (c[i+1]==' ' || c[i+1]==0)) ns++;
 return ns;}
 #include <stdio.h>
 void main(){ printf("words=%d\n",F("aaaa bbb ccc dddd"));}   // Выведет - 4
