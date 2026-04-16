#include <stdio.h>
#include <string.h>
//------------------------------------------------------52-05.cpp
//---- Поиск в строке заданного фрагмента
 char *find (char *p,char *q){
      int i;
	  for (; *p!='\0'; p++){ // Попарное сравнение до обнаружения расхождения
	  for ( i=0 ; q[i]!='\0' && q[i]==p[i]; i++);
	  if ( q[i] == '\0') return p;          // Конец подстроки - успех
	  }                                      // иначе продолжить поиск
 return NULL;}
//------------------------------------------------------26-07.cpp
//----- Поиск всех вхождений фрагмента в строке
 void main()
 { char c[80]="find first abc and next abc and last abc",*q="abc", *s;
 for (s=find(c,q); s!=NULL; s=find(s+strlen(q),q)) puts(s);
 } 
