#include <stdio.h>
void error(){ puts("error"); }
//------------------------------------------------------76-02.cpp
//---- Распознаватель правил F ::= i | i[E] | c | (E)
 char s[80];                             // входная цепочка терминалов
 int i;                                 // текущий терминальный символ
 extern void E();     // Объявление используемого распознавателя для E
 void F() {
	  switch(s[i]){
 case 'c' : i++; printf("F::=c\n"); break;
 case 'i' : i++;
		   if (s[i]=='['){
				printf("F::=i[E]\n");
		   i++; E();
		   if (s[i]==']') i++; else error();
		   }
 else printf("F::=i\n");
	  break;
 case '(' : i++;
	  printf("F::=(E)\n");
	  E();
	  if (s[i]==')') i++;
	  else error();
	  break;
 default: error();
	  }}

void T() {
puts("T::=F|T*F|T/F");
F(); while(s[i]=='*' || s[i]=='/') { i++; F(); }
}

void E() {
puts("E::=T|E+T|E-T");
T(); while(s[i]=='+' || s[i]=='-') { i++; T(); }
}

void main(){ gets(s); i=0; E(); }
